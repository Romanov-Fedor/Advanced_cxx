#pragma once

#include <iomanip>
#include <iostream>

#include "checkpoint.hpp"

class CheckpointBuilder {
 public:
  virtual ~CheckpointBuilder() = default;
  virtual void AddCheckpoint(const Checkpoint& cp) = 0;
  virtual std::string GetResult() const = 0;
};

class PenaltyCalculator : public CheckpointBuilder {
 public:
  void AddCheckpoint(const Checkpoint& cp) override {
    if (!cp.IsMandatory()) total_penalty += cp.Penalty();
  }

  std::string GetResult() const override {
    std::ostringstream oss;
    oss << "\nTotal penalty for skipped optional checkpoints: " << std::fixed
        << std::setprecision(2) << total_penalty << " hrs";
    return oss.str();
  }

 private:
  double total_penalty = 0.0;
};