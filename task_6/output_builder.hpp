#pragma once

#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "builder.hpp"

class OutputBuilder : public CheckpointBuilder {
 public:
  void AddCheckpoint(const Checkpoint& cp) override {
    checkpoints.push_back(cp);
  }

  std::string GetResult() const override {
    std::ostringstream oss;

    oss << "Checkpoint list:\n";
    int index = 1;
    for (const auto& cp : checkpoints) {
      oss << index++ << ". " << cp.Name() << " (" << cp.Latitude() << ", "
          << cp.Longitude() << ") - ";

      if (cp.IsMandatory())
        oss << "Stage DQ\n";
      else
        oss << std::setprecision(2) << std::fixed << cp.Penalty() << " hrs\n";
    }

    return oss.str();
  }

 private:
  std::vector<Checkpoint> checkpoints;
};