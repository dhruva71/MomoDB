#include <iostream>

#include "keystore.h"
#include "walogger.h"
int main() {
    std::cout << "Starting momoDB" << std::endl;

    WaLogger logger = WaLogger();
    logger.loadLogFile("./sample.log");
    keystore keystore(logger);

    keystore.put("secret", "41");
    keystore.put("secret2", "42");
    auto value = keystore.get("secret");
    std::cout << value << std::endl;
    keystore.del("secret");
    keystore.put("secret", "42");

    logger.printLog();
    keystore.printKeystore();
    logger.saveLogFile();

    return 0;
}
