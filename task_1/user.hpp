
#pragma once

#include <memory>
#include <string>

class Group;

class User {
 public:
  User(int id, const std::string& name, const std::string& email);

  int GetId() const;
  std::string GetUsername() const;
  std::string GetEmail() const;
  std::shared_ptr<Group> GetGroup() const;

  void SetUsername(const std::string& name);
  void SetEmail(const std::string& email);
  void SetGroup(std::weak_ptr<Group> group);

  void RemoveFromGroup();

  void PrintInfo() const;

 private:
  int id_;
  std::string name_;
  std::string email_;
  std::weak_ptr<Group> group_;
};
