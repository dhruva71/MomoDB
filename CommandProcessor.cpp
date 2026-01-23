//
// Created by dhruva on 1/18/26.
//

#include "CommandProcessor.h"

namespace momodb {
    // commands list
    constexpr std::string_view command_exit("EXIT");
    constexpr std::string_view command_set("SET");
    constexpr std::string_view command_get("GET");
    constexpr std::string_view command_del("DEL");

    CommandProcessor::CommandProcessor(WaLogger &logger, keystore &store) : logger(&logger), store(&store) {
        logger.addLogEntry(OpType::Internal, "CommandProcessor", "Initialized");
    }

    CommandProcessor::~CommandProcessor() {
        logger->addLogEntry(OpType::Internal, "CommandProcessor", "Destroyed");
    }

    std::string_view CommandProcessor::parse_and_execute_command(std::string_view command_view) const {
        logger->addLogEntry(OpType::Internal, "CommandProcessor", "Executing");

        // parsing by splitting based on space
        // our command syntax for now looks like
        // SET KEY VALUE
        // So we need to only look for the first two spaces
        const auto first_space_pos = command_view.find(' ');
        auto command_segment = command_view.substr(0, first_space_pos);
        const auto second_space_pos = command_view.find(' ', first_space_pos + 1);
        auto key_segment = command_view.substr(first_space_pos + 1, second_space_pos - first_space_pos - 1);
        auto value_segment = command_view.substr(second_space_pos + 1, command_view.length());

        // TODO add toggle for debug prints
        // auto debug_str = std::format("Command={}\n Key={}\n Value={}; First space at {}, second space at {}", command_segment, key_segment, value_segment, first_space_pos, second_space_pos);
        // std::cout << debug_str << std::endl;

        std::string_view execution_success;

        if (command_view == command_exit) {
            logger->addLogEntry(OpType::Internal, "CommandProcessor", "Exited");
            logger->saveLogFile();
            return {"EXIT"};
        }
        if (command_segment == command_set) {
            logger->addLogEntry(OpType::Internal, "CommandProcessor", "Set");
            auto return_value = store->set(std::string(key_segment), std::string(value_segment));
            logger->saveLogFile();
            if (return_value==0) {
                return {"OK"};
            } else {
                return {"ERROR"};
            }
        }
        if (command_segment == command_get) {
            logger->addLogEntry(OpType::Internal, "CommandProcessor", "Get");
            auto value = store->get(std::string(key_segment));
            logger->saveLogFile();

            // TODO inspect this
            return value;
        }
        if (command_segment == command_del) {
            logger->addLogEntry(OpType::Internal, "CommandProcessor", "Delete");
            auto return_value = store->del(std::string(key_segment));
            logger->saveLogFile();

            if (return_value==0) {
                return {"OK"};
            } else {
                return {"ERROR"};
            }
        }
        logger->addLogEntry(OpType::Internal, "CommandProcessor", std::format("Parsing failed for {}", command_view));
        logger->saveLogFile();
        return {"ERROR"};
    }
} // momodb
