//
// Created by dhruva on 1/18/26.
//

#include "CommandProcessor.h"

namespace momodb {
    // commands list
    constexpr std::string_view command_exit("EXIT\n");

    CommandProcessor::CommandProcessor(WaLogger &logger, keystore &store) : logger(&logger), store(&store) {
        logger.addLogEntry(OpType::Internal, "CommandProcessor", "Initialized");
    }

    CommandProcessor::~CommandProcessor() {
        logger->addLogEntry(OpType::Internal, "CommandProcessor", "Destroyed");
    }

    int CommandProcessor::parse_and_execute_command(std::string_view command_view) const {
        logger->addLogEntry(OpType::Internal, "CommandProcessor", "Executing");
        if (command_view == command_exit) {
            logger->addLogEntry(OpType::Internal, "CommandProcessor", "Exited");
            return 1;
        }
        return 0;
    }
} // momodb
