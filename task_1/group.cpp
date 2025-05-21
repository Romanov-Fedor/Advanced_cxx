#include "group.hpp"

#include <algorithm>
#include <iostream>

#include "user.hpp"

Group::Group(int id) : id_(id) {}

int Group::GetId() const { return id_; }

const std::vector<std::weak_ptr<User>>& Group::GetUsers() const {
  return users_;
}

void Group::AddUser(std::shared_ptr<User> user) {
  if (user) {
    users_.push_back(user);
    user->SetGroup(shared_from_this());
  }
}

void Group::RemoveUser(std::shared_ptr<User> user) {
  if (!user) return;

  auto it = std::find_if(users_.begin(), users_.end(),
                         [&](const std::weak_ptr<User>& weak_user) {
                           if (auto shared_user = weak_user.lock()) {
                             return shared_user->GetId() == user->GetId();
                           }
                           return false;
                         });

  if (it != users_.end()) {
    users_.erase(it);
  }

  user->RemoveFromGroup();
}

void Group::PrintInfo() const {
  std::cout << "Group ID: " << id_ << std::endl;
  std::cout << "Members (" << users_.size() << "):" << std::endl;

  for (const auto& weak_user : users_)
    if (auto user = weak_user.lock())
      std::cout << "  - " << user->GetUsername() << " (ID: " << user->GetId()
                << ")" << std::endl;

  std::cout << std::endl;
}