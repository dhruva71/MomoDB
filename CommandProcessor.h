//
// Created by dhruva on 1/18/26.
//

#ifndef MOMODB_COMMANDPROCESSOR_H
#define MOMODB_COMMANDPROCESSOR_H
#include <string_view>

#include "keystore.h"
#include "walogger.h"

namespace momodb {
    // Takes a string, parses it, logs it in the WAL and executes it on the keystore
    class CommandProcessor {
        WaLogger* logger;
        keystore* store;

    public:
        CommandProcessor(WaLogger&, keystore&);

        ~CommandProcessor();

        std::string_view parse_and_execute_command(std::string_view command) const;
    };
} // momodb

#endif //MOMODB_COMMANDPROCESSOR_H
