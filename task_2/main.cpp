#include <iostream>

#include "type_list.hpp"

using namespace type_list;
using namespace std;

using EmptyList = TypeList<>;
using SimpleList = TypeList<int, float, double>;
using ComplexList = TypeList<char, short, int, long>;

// 1. Тестирование Size
static_assert(Size<EmptyList>::value == 0, "Empty list with size 0");
static_assert(Size<SimpleList>::value == 3, "SimpleList with size  3");
static_assert(Size<ComplexList>::value == 4, "ComplexList with size 4");

// 2. Тестирование TypeAt
static_assert(is_same_v<TypeAt<0, SimpleList>::type, int>,
              "Simple 0 should be int");
static_assert(is_same_v<TypeAt<1, SimpleList>::type, float>,
              "Simple 1 should be float");
static_assert(is_same_v<TypeAt<2, SimpleList>::type, double>,
              "Simple 2 should be double");
static_assert(is_same_v<TypeAt<3, ComplexList>::type, long>,
              "Complex 3 should be long");

// Проверка выхода за границы (должно вызывать ошибку компиляции)
// static_assert(is_same_v<TypeAt<1, IntList>::type, float>, "This should
// fail"); static_assert(is_same_v<TypeAt<0, EmptyList>::type, void>, "This
// should fail");

// 3. Тестирование Contains
static_assert(!Contains<int, EmptyList>::value, "Empty should not contain int");
static_assert(Contains<int, SimpleList>::value, "Simple should contain int");
static_assert(Contains<float, SimpleList>::value,
              "Simple should contain float");
static_assert(!Contains<char, SimpleList>::value,
              "Simple should not contain char");
static_assert(Contains<short, ComplexList>::value,
              "Complex should contain short");

// 4. Тестирование IndexOf
static_assert(IndexOf<int, SimpleList>::value == 0,
              "int should be at 0 in Simple");
static_assert(IndexOf<float, SimpleList>::value == 1,
              "float should be at 1 in Simple");
static_assert(IndexOf<double, SimpleList>::value == 2,
              "double should be at 2 in Simple");
static_assert(IndexOf<long, ComplexList>::value == 3,
              "long should be at 3 in Complex");

// Проверка отсутствующего типа (должно вызывать ошибку компиляции)
// static_assert(IndexOf<char, IntList>::value == 0, "This should fail");

// 5. Тестирование Append
using AppendedEmpty = Append<int, EmptyList>::type;
static_assert(Size<AppendedEmpty>::value == 1,
              "AppendedEmpty size should be 1");
static_assert(is_same_v<TypeAt<0, AppendedEmpty>::type, int>,
              "AppendedEmpty 0  should be int");

using AppendedMyList = Append<char, SimpleList>::type;
static_assert(Size<AppendedMyList>::value == 4,
              "AppendedMyList size should be 4");
static_assert(is_same_v<TypeAt<3, AppendedMyList>::type, char>,
              "AppendedMyList 3 should be char");

// 6. Тестирование Prepend
using PrependedEmpty = Prepend<int, EmptyList>::type;
static_assert(Size<PrependedEmpty>::value == 1,
              "PrependedEmpty size should be 1");
static_assert(is_same_v<TypeAt<0, PrependedEmpty>::type, int>,
              "PrependedEmpty 0 should be int");

using PrependedMyList = Prepend<char, SimpleList>::type;
static_assert(Size<PrependedMyList>::value == 4,
              "PrependedMyList size should be 4");
static_assert(is_same_v<TypeAt<0, PrependedMyList>::type, char>,
              "PrependedMyList 0 should be char");
static_assert(is_same_v<TypeAt<1, PrependedMyList>::type, int>,
              "PrependedMyList 1 should be int");

int main() { return 0; }