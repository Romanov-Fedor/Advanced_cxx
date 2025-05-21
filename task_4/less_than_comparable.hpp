#pragma once

template <typename T>
class LessThanComparable {
 public:
  friend bool operator>(T const& lhs, T const& rhs) { return rhs < lhs; }

  friend bool operator<=(T const& lhs, T const& rhs) { return !(rhs < lhs); }

  friend bool operator>=(T const& lhs, T const& rhs) { return !(lhs < rhs); }

  friend bool operator==(T const& lhs, T const& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
  }

  friend bool operator!=(T const& lhs, T const& rhs) {
    return (lhs < rhs) || (rhs < lhs);
  }
};
