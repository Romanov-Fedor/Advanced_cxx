#pragma once

#include <memory>
#include <string>
#include <vector>

class User;

class Group : public std::enable_shared_from_this<Group> {
 public:
  Group(int id);

  int GetId() const;
  const std::vector<std::weak_ptr<User>>& GetUsers() const;

  void AddUser(std::shared_ptr<User> user);
  void RemoveUser(std::shared_ptr<User> user);

  void PrintInfo() const;

 private:
  int id_;
  std::vector<std::weak_ptr<User>> users_;
};