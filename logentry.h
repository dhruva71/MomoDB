//
// Created by dhruva on 1/10/26.
//

#ifndef MOMODB_LOGENTRY_H
#define MOMODB_LOGENTRY_H
#include <chrono>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <ranges>
#include <format>

enum class OpType : uint8_t {
    Internal = 0,
    Put      = 1,
    Delete   = 2,
    Get      = 3,
};

constexpr OpType toOpType(const uint8_t v) {
    switch (v) {
        case 0: return OpType::Internal;
        case 1: return OpType::Put;
        case 2: return OpType::Delete;
        case 3: return OpType::Get;
        default: throw std::runtime_error("Invalid OpType");
    }
}

struct LogEntry {
    // Unix timestamp
    uint64_t timestamp;

    // Operation type
    // TODO finalize operations
    // 0 - internal operations
    OpType optype;

    // Key and value
    std::string key;
    std::string value;

    LogEntry(OpType optype, std::string key, std::string value) : optype(optype), key(std::move(key)),
                                                                   value(std::move(value)) {
        const auto now = std::chrono::system_clock::now();
        timestamp = now.time_since_epoch().count();
    }

    LogEntry(uint64_t timestamp, OpType optype, std::string key, std::string value) : timestamp(timestamp),
        optype(optype), key(std::move(key)), value(std::move(value)) {
    }

    explicit LogEntry(std::string logString) {
        // current format planned is
        // 123154:0:key:value
        auto segments_view = logString | std::views::split(':') | std::views::transform([](auto &&range) {
            return std::string{
                range.begin(), range.end()
            };
        });

        const std::vector segments(segments_view.begin(), segments_view.end());

        std::cout << "Length of segments: " << segments.size() << std::endl;
        if (segments.empty()) {
            std::cerr << "Empty segments!" << std::endl;
        } else if (segments.size() > 4) {
            std::cerr << "Too many segments! Expected 4, found " << segments.size() << std::endl;
        } else {
            // TODO remove this later
            std::cout << "Creating LogEntry object from <" << logString <<">"<< std::endl;
            timestamp = std::stoull(segments[0]);
            optype = static_cast<OpType>(std::stoi(segments[1]));
            key = segments[2];
            value = segments[3];
        }
    }

    [[nodiscard]] std::string toString() const {
        // Format: "timestamp:optype:key:value"
        return std::format("{}:{}:{}:{}", timestamp, static_cast<uint8_t>(optype), key, value);
    }
};

#endif //MOMODB_LOGENTRY_H
