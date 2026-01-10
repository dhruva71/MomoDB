//
// Created by dhruva on 1/10/26.
//

#include "keystore.h"

#include <format>
#include <iostream>

keystore::keystore(WaLogger &logger) : logger(logger) {
    logger.addLogEntry(OpType::Internal, "keystore", "created");
}

keystore::~keystore() {
    store.clear();
    logger.addLogEntry(OpType::Delete, "keystore", "deleted");
}

int keystore::put(std::string key, std::string value) {
    logger.addLogEntry(OpType::Put, key, value);
    store.insert({key, value});

    const auto display_string = std::format("Inserted {}:{} in store", key, value);
    std::cout << display_string;
    return 0;
}

std::string keystore::get(const std::string &key) {
    auto value = store.at(key);
    logger.addLogEntry(OpType::Get, key, value);
    return value;
}

int keystore::del(const std::string &key) {
    auto value = store.at(key);
    logger.addLogEntry(OpType::Delete, key, value);
    return store.erase(key);
}

void keystore::printKeystore() {
    std::cout << "\n Printing keystore:" << std::endl;
    for (const auto &[key, value]: store) {
        auto display_string = std::format("{}:{}", key, value);
        std::cout << display_string << std::endl;
    }
}
