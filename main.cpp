#include <iostream>
#include "walogger.h"
int main() {
    std::cout << "Starting momoDB" << std::endl;

    WaLogger logger = WaLogger();
    logger.loadLogFile("./sample.log");

    logger.addLogEntry(OpType::Put, "userid", "42");
    logger.addLogEntry(OpType::Put, "userpassword", "secret password");

    logger.printLog();
    logger.saveLogFile();

    return 0;
}
