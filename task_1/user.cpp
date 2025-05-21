
#include "user.hpp"

#include <iostream>

#include "group.hpp"

User::User(int id, const std::string& name, const std::string& email)
    : id_(id), name_(name), email_(email) {}

int User::GetId() const { return id_; }
std::string User::GetUsername() const { return name_; }
std::string User::GetEmail() const { return email_; }
std::shared_ptr<Group> User::GetGroup() const { return group_.lock(); }

void User::SetUsername(const std::string& name) { name_ = name; }
void User::SetEmail(const std::string& email) { email_ = email; }
void User::SetGroup(std::weak_ptr<Group> group) { group_ = group; }

void User::RemoveFromGroup() { group_.reset(); }

void User::PrintInfo() const {
  std::cout << "User ID: " << id_ << std::endl;
  std::cout << "User name: " << name_ << std::endl;
  std::cout << "Email: " << email_ << std::endl;

  if (auto group = group_.lock())
    std::cout << "Group ID: " << group->GetId() << std::endl;
  else
    std::cout << "User aren`t in group" << std::endl;

  std::cout << std::endl;
}