//
// Created by dhruva on 1/10/26.
//

#ifndef MOMODB_WALOGGER_H
#define MOMODB_WALOGGER_H
#include <string>
#include <vector>

#include "logentry.h"

class WaLogger {
    std::vector<LogEntry> logEntries;
    std::string logFileName;
public:
    WaLogger();
    ~WaLogger();

    int loadLogFile(const std::string &logFilePath);
    void saveLogFile() const;
    void saveLogFile(const std::string &logFilePath);
    void printLog() const;
    int addLogEntry(OpType optype, const std::string &key, const std::string &value);
    std::vector<LogEntry> getLogEntries();
};

#endif //MOMODB_WALOGGER_H