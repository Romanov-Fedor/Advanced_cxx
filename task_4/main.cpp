#include <cassert>
#include <iostream>

#include "counter.hpp"
#include "less_than_comparable.hpp"

class Number : public LessThanComparable<Number>, public Counter<Number> {
 public:
  Number(int value) : m_value{value} {}
  int Value() const { return m_value; }
  bool operator<(Number const& other) const { return m_value < other.m_value; }

 private:
  int m_value;
};

int main() {
  Number one{1};
  Number two{2};
  Number three{3};
  Number four{4};

  assert(one >= one);
  assert(three <= four);
  assert(two == two);
  assert(three > two);
  assert(one < two);

  std::cout << "Count: " << Counter<Number>::Count() << std::endl;

  return 0;
}