#include "log.hpp"

#include <iomanip>
#include <iostream>
#include <string>

Log* Log::instance = nullptr;

const std::unordered_map<LogLevel, const char*> Log::level_strings = {
    {LOG_NORMAL, "NORMAL: "},
    {LOG_WARNING, "WARNING: "},
    {LOG_ERROR, "ERROR: "}};

Log* Log::Instance() {
  if (!instance) instance = new Log();

  return instance;
}

void Log::Message(LogLevel level, const std::string& msg) {
  time_t now = time(nullptr);

  entries.emplace_back(now, level, msg);
  if (entries.size() > max_entries) entries.erase(entries.begin());
}

std::string Log::FormatTime(time_t timestamp) {
  char timeStr[20];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S",
           localtime(&timestamp));
  return std::string(timeStr);
}

void Log::Print() const {
  std::cout << "=== Last " << max_entries << " events ===" << std::endl;

  for (const auto& entry : entries) {
    std::cout << "[" << FormatTime(entry.timestamp) << "] "
              << level_strings.at(entry.level) << entry.message << std::endl;
  }

  std::cout << "======================" << std::endl;
}
