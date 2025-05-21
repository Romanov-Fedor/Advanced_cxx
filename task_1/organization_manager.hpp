#pragma once

#include <functional>
#include <iostream>
#include <string>

#include "group_manager.hpp"
#include "user_manager.hpp"

class OrganizationManager {
 public:
  OrganizationManager(UserManager& user_manager, GroupManager& group_manager);

  void PrintUsage(const std::string& command) const;
  void ProcessCommand(const std::string& command);
  void PrintHelp() const;

 private:
  UserManager& userManager_;
  GroupManager& groupManager_;

  const std::unordered_map<std::string, std::string> usages = {
      {"createUser", "createUser {userId} {username} [email]"},
      {"deleteUser", "deleteUser {userId}"},
      {"allUsers", "allUsers"},
      {"getUser", "getUser {userId}"},
      {"createGroup", "createGroup {groupId}"},
      {"deleteGroup", "deleteGroup {groupId}"},
      {"allGroups", "allGroups"},
      {"getGroup", "getGroup {groupId}"},
      {"addUserToGroup", "addUserToGroup {userId} {groupId}"}};

  const std::unordered_map<std::string,
                           std::function<void(const std::vector<std::string>&)>>
      commands = {{"createUser",
                   [this](const auto& args) {
                     if (args.size() < 2 || args.size() > 4) {
                       PrintUsage("createUser");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       std::string username = args[2];
                       std::string email = args.size() > 3 ? args[3] : "";
                       userManager_.createUser(id, username, email);
                       std::cout << "User created" << std::endl;
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("createUser");
                     }
                   }},
                  {"deleteUser",
                   [this](const auto& args) {
                     if (args.size() != 2) {
                       PrintUsage("deleteUser");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       userManager_.deleteUser(id);
                       std::cout << "User deleted" << std::endl;
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("deleteUser");
                     }
                   }},
                  {"allUsers",
                   [this](const auto& args) {
                     if (args.size() != 1) {
                       PrintUsage("allUsers");
                       return;
                     }
                     userManager_.printAllUsers();
                   }},
                  {"getUser",
                   [this](const auto& args) {
                     if (args.size() != 2) {
                       PrintUsage("getUser");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       userManager_.printUser(id);
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("getUser");
                     }
                   }},
                  {"createGroup",
                   [this](const auto& args) {
                     if (args.size() != 2) {
                       PrintUsage("createGroup");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       groupManager_.CreateGroup(id);
                       std::cout << "Group created" << std::endl;
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("createGroup");
                     }
                   }},
                  {"deleteGroup",
                   [this](const auto& args) {
                     if (args.size() != 2) {
                       PrintUsage("deleteGroup");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       groupManager_.DeleteGroup(id);
                       std::cout << "Group dleted" << std::endl;
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("deleteGroup");
                     }
                   }},
                  {"allGroups",
                   [this](const auto& args) {
                     if (args.size() != 1) {
                       PrintUsage("allGroups");
                       return;
                     }
                     groupManager_.PrintAllGroups();
                   }},
                  {"getGroup",
                   [this](const auto& args) {
                     if (args.size() != 2) {
                       PrintUsage("getGroup");
                       return;
                     }
                     try {
                       int id = std::stoi(args[1]);
                       groupManager_.PrintGroup(id);
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("getGroup");
                     }
                   }},
                  {"addUserToGroup", [this](const auto& args) {
                     if (args.size() != 3) {
                       PrintUsage("addUserToGroup");
                       return;
                     }
                     try {
                       int userId = std::stoi(args[1]);
                       int groupId = std::stoi(args[2]);
                       auto user = userManager_.getUser(userId);
                       if (user) {
                         groupManager_.AddUserToGroup(user, groupId);
                         std::cout << "User added to group" << std::endl;
                       } else {
                         std::cerr << "User with ID " << userId
                                   << " not found.\n";
                       }
                     } catch (const std::exception& e) {
                       std::cerr << "Error: " << e.what() << "\n";
                       PrintUsage("addUserToGroup");
                     }
                   }}};
};