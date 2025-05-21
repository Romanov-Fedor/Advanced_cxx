#pragma once

#include <memory>
#include <unordered_map>

#include "group.hpp"
#include "user.hpp"

class UserManager {
 public:
  bool createUser(int id, const std::string& user_name,
                  const std::string& email = "");
  bool deleteUser(int id);
  void printAllUsers() const;
  void printUser(int id) const;
  std::shared_ptr<User> getUser(int id) const;

 private:
  std::unordered_map<int, std::shared_ptr<User>> users_;
};