//
// Created by dhruva on 1/10/26.
//

#include "keystore.h"

#include <format>
#include <iostream>

keystore::keystore(WaLogger &logger) : logger(logger) {
    logger.addLogEntry(OpType::Internal, "keystore", "created");
}

keystore &keystore::operator=(const keystore &other) {
    if (this == &other) {
        return *this;
    }
    logger = other.logger;
    return *this;
}

keystore::~keystore() {
    store.clear();
    logger.addLogEntry(OpType::Delete, "keystore", "deleted");
}

int keystore::set(const std::string &key, std::string value) {
    logger.addLogEntry(OpType::Set, key, value);
    // return type of store.insert_or_assign should look like (source: https://en.cppreference.com/w/cpp/container/map.html)
    // {
    //     Iter     position;
    //     bool     inserted;
    //     NodeType node;
    // };
    auto insert_return = store.insert_or_assign(key, value);
    if (insert_return.second) {
        logger.addLogEntry(OpType::Internal, "Put", "Success");
    }
    return 0;
}

std::string keystore::get(const std::string &key) {
    auto value = store.at(key);
    logger.addLogEntry(OpType::Get, key, value);
    return value;
}

// returns 0 for success
int keystore::del(const std::string &key) {
    // const auto value = store.at(key);
    // overwrite the value
    auto value = "<deleted>";
    auto insert_return = store.insert_or_assign(key, value);
    logger.addLogEntry(OpType::Delete, key, value);
    return 0;
}

void keystore::printKeystore() {
    std::cout << "\n Printing keystore:" << std::endl;
    for (const auto &[key, value]: store) {
        auto display_string = std::format("{}:{}", key, value);
        std::cout << display_string << std::endl;
    }
}

int keystore::rebuildFromLog() {
    auto logEntries = logger.getLogEntries();
    for (const auto &entry: logEntries) {
        auto optype = entry.optype;
        switch (optype) {
            case OpType::Set: {
                auto key = entry.key;
                auto value = entry.value;
                store.insert({key, value});
                break;
            }
            case OpType::Internal:
                break;
            case OpType::Delete:
                store.erase(entry.key);
                break;
            case OpType::Get:
                break;
        }
    }
    return 0;
}
