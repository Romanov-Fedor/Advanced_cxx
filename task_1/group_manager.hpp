#pragma once

#include <memory>
#include <unordered_map>

#include "group.hpp"
#include "user.hpp"

class GroupManager {
 public:
  bool CreateGroup(int id);
  bool DeleteGroup(int id);

  void PrintAllGroups() const;
  void PrintGroup(int id) const;

  std::shared_ptr<Group> GetGroup(int id) const;
  bool AddUserToGroup(std::shared_ptr<User> user, int group_id);

 private:
  std::unordered_map<int, std::shared_ptr<Group>> groups_;
};