#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include "Colours.h"
#include "LogLevels.h"

#define CURRENT_LOG_LEVEL LOG_LEVEL_TRACE

inline std::string currentTimeFormatted() {
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(
                      now.time_since_epoch()) %
                  1000;

    std::tm local_tm = *std::localtime(&now_c);

    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%H:%M:%S") << "." << std::setfill('0')
        << std::setw(3) << millis.count();
    return oss.str();
}

#define LOG(level, color, levelStr, tag, message)                            \
    do {                                                                     \
        if (level >= CURRENT_LOG_LEVEL) {                                    \
            std::cerr << WHITE << currentTimeFormatted() << " > " << color \
                      << "[" << levelStr << ": " << tag << "] " << message   \
                      << RESET << std::endl;                                 \
        }                                                                    \
    } while (0)

#define LOG_TRACE(tag, message) \
    LOG(LOG_LEVEL_TRACE, CYAN, "TRACE", tag, message)
#define LOG_DEBUG(tag, message) \
    LOG(LOG_LEVEL_DEBUG, MAGENTA, "DEBUG", tag, message)
#define LOG_INFO(tag, message) LOG(LOG_LEVEL_INFO, WHITE, "INFO", tag, message)
#define LOG_WARN(tag, message) LOG(LOG_LEVEL_WARN, YELLOW, "WARN", tag, message)
#define LOG_ERROR(tag, message) LOG(LOG_LEVEL_ERROR, RED, "ERROR", tag, message)

#endif  // LOG_H
