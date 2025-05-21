#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "../task_2/type_list.hpp"

namespace type_list {

struct AnyValue {
  virtual ~AnyValue() = default;
};

template <typename T>
struct ValueHolder : AnyValue {
  T value;

  explicit ValueHolder(const T& val) : value(val) {}
  explicit ValueHolder(T&& val) : value(std::move(val)) {}
};

template <typename... Keys>
class TypeMap {
 private:
  std::unique_ptr<AnyValue> values[sizeof...(Keys)];

  template <typename Key>
  static constexpr std::size_t GetIndex() {
    constexpr std::size_t index = IndexOf<Key, TypeList<Keys...>>::value;
    static_assert(index < sizeof...(Keys), "Invalid key type");
    return index;
  }

 public:
  // Добавление значения по типу ключа
  template <typename Key>
  void AddValue(Key&& value) {
    constexpr std::size_t index = GetIndex<Key>();
    values[index] = std::make_unique<ValueHolder<std::decay_t<Key>>>(
        std::forward<Key>(value));
  }

  // Получение значения по типу ключа
  template <typename Key>
  auto& GetValue() {
    constexpr std::size_t index = GetIndex<Key>();
    if (!values[index]) {
      throw std::runtime_error("Value not set for this key");
    }
    return static_cast<ValueHolder<Key>*>(values[index].get())->value;
  }

  // Проверка наличия значения по типу ключа
  template <typename Key>
  bool Contains() const {
    constexpr std::size_t index = GetIndex<Key>();
    return values[index] != nullptr;
  }

  // Удаление значения по типу ключа
  template <typename Key>
  void RemoveValue() {
    constexpr std::size_t index = GetIndex<Key>();
    values[index].reset();
  }
};

}  // namespace type_list