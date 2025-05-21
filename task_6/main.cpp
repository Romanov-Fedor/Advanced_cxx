#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "builder.hpp"
#include "director.hpp"
#include "output_builder.hpp"

// #include "penalty_calculator.hpp"

int main() {
  std::vector<Checkpoint> checkpoints = {
      Checkpoint("Start", 55.7522, 37.6156),
      Checkpoint("Mountain Pass", 43.3564, 42.4455).SetPenalty(2.5),
      Checkpoint("River Crossing", 44.1234, 45.6789),
      Checkpoint("Finish", 55.7522, 37.6156),
      Checkpoint("Bonus Stage", 43.2567, 42.8765).SetPenalty(1.8)};

  CheckpointDirector director(std::make_unique<OutputBuilder>());
  std::cout << director.Construct(checkpoints);

  director.SetBuilder(std::make_unique<PenaltyCalculator>());
  std::cout << director.Construct(checkpoints);

  return 0;
}