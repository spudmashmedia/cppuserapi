#pragma once
#include "crow.h"
#include <iostream>
#include <mutex>
#include <string>

namespace com_spudmash_cppuserapi::utils::logger
{

inline thread_local std::string current_correlation_id = "NO_ID";

class AppLogger : public crow::ILogHandler
{
  public:
    void log(const std::string &message, crow::LogLevel level) override
    {
        std::lock_guard<std::mutex> lock(log_mutex);

        std::cout << "[" << level_to_string(level) << "]"
                  << "[" << current_correlation_id << "] " << message
                  << std::endl;
    }

  private:
    std::mutex log_mutex;

    std::string level_to_string(crow::LogLevel level)
    {
        switch (level)
        {
        case crow::LogLevel::Debug:
            return "DEBUG";
        case crow::LogLevel::Info:
            return "INFO";
        case crow::LogLevel::Warning:
            return "WARNING";
        case crow::LogLevel::Error:
            return "ERROR";
        case crow::LogLevel::Critical:
            return "CRITICAL";
        default:
            return "LOG";
        }
    }
};
} // namespace com_spudmash_cppuserapi::utils::logger
