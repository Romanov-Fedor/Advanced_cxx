#include <iostream>
#include <string>

#include "group_manager.hpp"
#include "organization_manager.hpp"
#include "user_manager.hpp"

int main() {
  UserManager userManager;
  GroupManager groupManager;
  OrganizationManager processor(userManager, groupManager);

  std::cout << "User and Group Management System\n";
  std::cout << "Type 'help' for list of commands or 'exit' to quit\n";

  std::string command;
  while (true) {
    std::cout << "> ";
    std::getline(std::cin, command);

    if (command == "exit")
      break;
    else if (command == "help")
      processor.PrintHelp();
    else
      processor.ProcessCommand(command);
  }

  return 0;
}