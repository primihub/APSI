// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license.

#pragma once

// STD
#include <cstdarg>
#include <sstream>
#include <string>
#include <glog/logging.h>
namespace apsi {
    /**
    Class that provides the logging interface.
    */
    class Log {
    public:
        /**
        Supported log levels
        */
        enum class Level : int { all, debug, info, warning, error, off };

        /**
        This class is only to be used through its static methods.
        */
        Log() = delete;

        static void SetLogLevel(Level level);

        static Level GetLogLevel();

        static void SetLogLevel(const std::string &level);

        static void SetLogFile(const std::string &file);

        static void SetConsoleDisabled(bool console_disabled);

        static void ConfigureIfNeeded();

        static void Terminate();

        static void DoLog(std::string msg, Level msg_level);

    private:
        static void Configure();

        static Level log_level_;
    }; // class Log
} // namespace apsi

#define APSI_INTERNAL_CHECK_LOG_LEVEL(log_level) \
    apsi::Log::ConfigureIfNeeded();              \
    if (apsi::Log::GetLogLevel() > log_level) {  \
        break;                                   \
    }


#define APSI_LOG_DEBUG(msg)                                     \
    VLOG(5) << msg;


#define APSI_LOG_INFO(msg)                                     \
    LOG(INFO) << msg;


#define APSI_LOG_WARNING(msg)                                     \
    LOG(WARNING) << msg;


#define APSI_LOG_ERROR(msg)                                     \
    LOG(ERROR) << msg;

