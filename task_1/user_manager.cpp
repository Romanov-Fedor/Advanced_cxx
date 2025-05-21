#include "user_manager.hpp"

#include <iostream>

#include "user.hpp"

bool UserManager::createUser(int id, const std::string& user_name,
                             const std::string& email) {
  if (users_.find(id) != users_.end()) {
    std::cerr << "User with ID " << id << " already exists" << std::endl;
    return false;
  }

  auto user = std::make_shared<User>(id, user_name, email);
  users_[id] = user;
  return true;
}

bool UserManager::deleteUser(int id) {
  auto it = users_.find(id);
  if (it == users_.end()) {
    std::cerr << "User with ID " << id << " not found" << std::endl;
    return false;
  }

  if (auto group = it->second->GetGroup()) group->RemoveUser(it->second);

  users_.erase(it);
  return true;
}

void UserManager::printAllUsers() const {
  if (users_.empty()) {
    std::cout << "No users found" << std::endl;
    return;
  }

  for (const auto& pair : users_) pair.second->PrintInfo();
}

void UserManager::printUser(int id) const {
  auto it = users_.find(id);
  if (it == users_.end()) {
    std::cerr << "User with ID " << id << " not found." << std::endl;
    return;
  }

  it->second->PrintInfo();
}

std::shared_ptr<User> UserManager::getUser(int id) const {
  auto it = users_.find(id);
  if (it == users_.end()) return nullptr;
  return it->second;
}