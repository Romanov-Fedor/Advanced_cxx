#pragma once

#include <ctime>
#include <iostream>
#include <unordered_map>
#include <vector>

enum LogLevel { LOG_NORMAL, LOG_WARNING, LOG_ERROR };

class Log {
 public:
  Log(const Log&) = delete;
  Log& operator=(const Log&) = delete;

  static Log* Instance();

  void Message(LogLevel level, const std::string& msg);

  void Print() const;

 private:
  Log() = default;
  ~Log() = default;

  static std::string FormatTime(time_t timestamp);

  struct LogEntry {
    LogEntry(time_t ts, LogLevel lvl, const std::string& msg)
        : timestamp(ts), level(lvl), message(msg) {}

    time_t timestamp;
    LogLevel level;
    std::string message;
  };

  std::vector<LogEntry> entries;
  static Log* instance;

  static constexpr int max_entries = 10;
  static const std::unordered_map<LogLevel, const char*> level_strings;
};