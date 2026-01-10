//
// Created by dhruva on 1/10/26.
//

#ifndef MOMODB_KEYSTORE_H
#define MOMODB_KEYSTORE_H

#include <map>
#include <string>

#include "walogger.h"

class keystore {
    std::map<std::string, std::string> store;
    WaLogger &logger;
public:
    explicit keystore(WaLogger &);
    ~keystore();

    int put(std::string key, std::string value);
    std::string get(const std::string &key);
    int del(const std::string& key);

    void printKeystore();
    int rebuildFromLog();
};


#endif //MOMODB_KEYSTORE_H