#include "organization_manager.hpp"

#include <sstream>
#include <unordered_map>
#include <vector>

#include "group.hpp"
#include "group_manager.hpp"
#include "user.hpp"
#include "user_manager.hpp"

OrganizationManager::OrganizationManager(UserManager& userManager,
                                         GroupManager& groupManager)
    : userManager_(userManager), groupManager_(groupManager) {}

void OrganizationManager::PrintUsage(const std::string& command) const {
  auto it = usages.find(command);
  if (it != usages.end())
    std::cerr << "Usage: " << it->second << "\n";
  else
    PrintHelp();
}

void OrganizationManager::ProcessCommand(const std::string& command) {
  std::vector<std::string> tokens;
  std::istringstream iss(command);
  std::string token;

  while (iss >> token) tokens.push_back(token);

  if (tokens.empty()) return;

  auto it = commands.find(tokens[0]);
  if (it != commands.end())
    it->second(tokens);
  else
    std::cerr << "Unknown command\n";
}

void OrganizationManager::PrintHelp() const {
  std::cout << "Available commands:\n"
            << "  createUser {userId} {username} [email] - Create new user\n"
            << "  deleteUser {userId} - Delete user\n"
            << "  allUsers - List all users\n"
            << "  getUser {userId} - Show user info\n"
            << "  createGroup {groupId} - Create new group\n"
            << "  deleteGroup {groupId} - Delete group\n"
            << "  allGroups - List all groups\n"
            << "  getGroup {groupId} - Show group info\n"
            << "  addUserToGroup {userId} {groupId} - Add user to group\n";
}