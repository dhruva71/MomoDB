//
// Created by dhruva on 1/10/26.
//
#include <chrono>
#include <fstream>
#include "logentry.h"
#include "walogger.h"
#include <iostream>

WaLogger::WaLogger() {
    logEntries = std::vector<LogEntry>();
    logEntries.push_back(std::move(LogEntry(OpType::Internal, "Created", "WaLogger")));
}

WaLogger::~WaLogger() {
    logEntries.push_back(std::move(LogEntry(OpType::Internal, "Destroyed", "WaLogger")));
    this->saveLogFile(this->logFileName);
}

int WaLogger::loadLogFile(const std::string &logFilePath) {
    std::ifstream fileStream(logFilePath);
    if (!fileStream.is_open()) {
        std::cerr << "Error opening log file " << logFilePath << std::endl;
        return 1;
    }

    // update logger's logFileName, since we have a successful load now
    logFileName = logFilePath;

    while (!fileStream.eof()) {
        std::string line;
        std::getline(fileStream, line);
        logEntries.push_back(std::move(LogEntry(line)));
    }
    fileStream.close();

    // display log entries
    for (auto &entry : logEntries) {
        std::cout<<entry.toString()<<std::endl;
    }

    return 0;
}

void WaLogger::saveLogFile() const {
    std::ofstream fileStream(logFileName);
    if (!fileStream.is_open()) {
        std::cerr << "Error opening log file " << logFileName << std::endl;
    }
    for (auto &entry : logEntries) {
        fileStream << entry.toString() << std::endl;
    }
    fileStream.close();
    std::cout<<"Saved log file"<<std::endl;
}

void WaLogger::saveLogFile(const std::string &logFilePath) {
    if (!logFilePath.empty()) {
        logFileName = logFilePath;
    } else {
        std::cerr << "Error opening log file " << logFilePath << std::endl;
        return;
    }
    std::ofstream fileStream(logFileName);
    if (!fileStream.is_open()) {
        std::cerr << "Error opening log file " << logFilePath << std::endl;
    }
    for (auto &entry : logEntries) {
        fileStream << entry.toString() << std::endl;
    }
    fileStream.close();
    std::cout<<"Saved log file"<<std::endl;
}

void WaLogger::printLog() const {
    std::cout<<"Printing log entries from memory:"<<std::endl;
    for (auto &entry : logEntries) {
        std::cout<<entry.toString()<<std::endl;
    }
}

int WaLogger::addLogEntry(OpType optype, const std::string &key, const std::string &value) {
    LogEntry log_entry = LogEntry(optype, key, value);
    logEntries.push_back(log_entry);
    return 0;
}
