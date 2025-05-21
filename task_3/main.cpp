#include "type_map.hpp"

struct A {
  std::string value;
};

struct B {
  int value;
};

int main() {
  using namespace type_list;

  TypeMap<int, A, double, B> type_map;

  type_map.AddValue<int>(42);
  type_map.AddValue<double>(3.14);
  type_map.AddValue<A>({"abc"});
  type_map.AddValue<B>({10});

  std::cout << "Value for int: " << type_map.GetValue<int>() << std::endl;
  std::cout << "Value for double: " << type_map.GetValue<double>() << std::endl;
  std::cout << "Value for A: " << type_map.GetValue<A>().value << std::endl;
  std::cout << "Value for B: " << type_map.GetValue<B>().value << std::endl;

  std::cout << "Contains int? " << (type_map.Contains<int>() ? "Yes" : "No")
            << std::endl;

  std::cout << "Value for double before removal: "
            << type_map.GetValue<double>() << std::endl;

  // type_map.RemoveValue<double>();

  std::cout << "Value for double after removal: " << type_map.GetValue<double>()
            << std::endl;
  return 0;
}