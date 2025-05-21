#pragma once

#include <memory>
#include <vector>

#include "builder.hpp"

class CheckpointDirector {
 public:
  explicit CheckpointDirector(std::unique_ptr<CheckpointBuilder>&& b)
      : builder(std::move(b)) {}

  void SetBuilder(std::unique_ptr<CheckpointBuilder>&& b) {
    builder = std::move(b);
  }

  std::string Construct(const std::vector<Checkpoint>& checkpoints) {
    for (const auto& cp : checkpoints) builder->AddCheckpoint(cp);
    return builder->GetResult();
  }

 private:
  std::unique_ptr<CheckpointBuilder> builder;
};