#include "log.hpp"

int main() {
  Log* log = Log::Instance();

  log->Message(LOG_NORMAL, "Program loaded");
  log->Message(LOG_WARNING, "Configuration file not found, using defaults");
  log->Message(LOG_NORMAL, "Initialization complete");
  log->Message(LOG_ERROR, "Error happens! Help me!");

  log->Print();

  return 0;
}