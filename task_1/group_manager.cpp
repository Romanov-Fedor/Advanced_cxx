#include "group_manager.hpp"

#include <iostream>

#include "group.hpp"
#include "user.hpp"

bool GroupManager::CreateGroup(int id) {
  if (groups_.find(id) != groups_.end()) {
    std::cerr << "Group with ID " << id << " already exists" << std::endl;
    return false;
  }

  auto group = std::make_shared<Group>(id);
  groups_[id] = group;
  return true;
}

bool GroupManager::DeleteGroup(int id) {
  auto it = groups_.find(id);
  if (it == groups_.end()) {
    std::cerr << "Group with ID " << id << " not found" << std::endl;
    return false;
  }

  for (const auto& weak_user : it->second->GetUsers())
    if (auto user = weak_user.lock()) user->RemoveFromGroup();

  groups_.erase(it);
  return true;
}

void GroupManager::PrintAllGroups() const {
  if (groups_.empty()) {
    std::cout << "No groups found" << std::endl;
    return;
  }

  for (const auto& pair : groups_) pair.second->PrintInfo();
}

void GroupManager::PrintGroup(int id) const {
  auto it = groups_.find(id);
  if (it == groups_.end()) {
    std::cerr << "Group with ID " << id << " not found" << std::endl;
    return;
  }

  it->second->PrintInfo();
}

std::shared_ptr<Group> GroupManager::GetGroup(int id) const {
  auto it = groups_.find(id);
  if (it == groups_.end()) return nullptr;
  return it->second;
}

bool GroupManager::AddUserToGroup(std::shared_ptr<User> user, int group_id) {
  if (!user) return false;

  auto group = GetGroup(group_id);
  if (!group) {
    std::cerr << "Group with ID " << group_id << " not found" << std::endl;
    return false;
  }

  if (auto old_group = user->GetGroup()) old_group->RemoveUser(user);

  group->AddUser(user);
  return true;
}