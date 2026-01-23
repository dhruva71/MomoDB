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
    keystore& operator=(const keystore &);
    ~keystore();

    int set(const std::string &key, std::string value, bool shouldLog = true);
    std::string get(const std::string &key, bool shouldLog = true);
    int del(const std::string &key, bool shouldLog=true);

    void printKeystore();
    int rebuildFromLog();
};


#endif //MOMODB_KEYSTORE_H