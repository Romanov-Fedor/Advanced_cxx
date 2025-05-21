#pragma once

#include <optional>
#include <string>

class Checkpoint {
 public:
  Checkpoint(std::string n, double lt, double lng)
      : name(std::move(n)), latitude(lt), longitude(lng) {}

  Checkpoint& SetPenalty(double p) {
    penalty = p;
    return *this;
  }

  const std::string& Name() const { return name; }
  double Latitude() const { return latitude; }
  double Longitude() const { return longitude; }
  bool IsMandatory() const { return !penalty.has_value(); }
  double Penalty() const { return penalty.value_or(0.0); }

 private:
  std::string name;
  double latitude;
  double longitude;
  std::optional<double> penalty;
};