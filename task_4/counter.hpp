#pragma once

// Класс для подсчета экземпляров производных классов (CRTP)
template <typename Derived>
class Counter {
 public:
  Counter() { count_++; }
  Counter(const Derived&) { count_++; }

  ~Counter() { count_--; }

  static int Count() { return count_; }

 private:
  inline static int count_ = 0;
};