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

int keystore::set(const std::string &key, std::string value, bool shouldLog) {
    if (shouldLog) {
        logger.addLogEntry(OpType::Set, key, value);
    }
    // return type of store.insert_or_assign should look like (source: https://en.cppreference.com/w/cpp/container/map.html)
    // {
    //     Iter     position;
    //     bool     inserted;
    //     NodeType node;
    // };
    auto insert_return = store.insert_or_assign(key, value);
    if (insert_return.second) {
        if (shouldLog) {
            logger.addLogEntry(OpType::Internal, "Put", "Success");
        }
    }
    return 0;
}

std::string keystore::get(const std::string &key, bool shouldLog) {
    try {
        auto value = store.at(key);
        if (shouldLog) {
            logger.addLogEntry(OpType::Get, key, value);
        }
        return value;
    } catch (const std::out_of_range &e) {
        return "";
    }
}

// returns 0 for success
int keystore::del(const std::string &key, bool shouldLog) {
    // const auto value = store.at(key);
    // overwrite the value
    auto value = "";
    auto insert_return = store.insert_or_assign(key, value);
    if (shouldLog) {
        logger.addLogEntry(OpType::Delete, key, value);
    }
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
                this->set(key, value, false);
                break;
            }
            case OpType::Internal:
                break;
            case OpType::Delete:
                this->del(entry.key, false);
                break;
            case OpType::Get:
                break;
        }
    }
    logger.addLogEntry(OpType::Internal, "keystore", "rebuilt");
    return 0;
}
