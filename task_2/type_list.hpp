#pragma once

#include <type_traits>

namespace type_list {

template <typename... Types>
struct TypeList;

// Пустой TypeList
template <>
struct TypeList<> {
  static constexpr std::size_t size = 0;
};

// Непустой TypeList
template <typename T, typename... Rest>
struct TypeList<T, Rest...> {
  using Head = T;
  using Tail = TypeList<Rest...>;

  static constexpr std::size_t size = 1 + Tail::size;
};

// Получение элемента по индексу
template <std::size_t N, typename List>
struct TypeAt;

// Специализация для непустого списка и индекса 0
template <typename T, typename... Rest>
struct TypeAt<0, TypeList<T, Rest...>> {
  using type = T;
};

// Специализация для непустого списка и индекса N > 0
template <std::size_t N, typename T, typename... Rest>
struct TypeAt<N, TypeList<T, Rest...>> {
  static_assert(TypeList<T, Rest...>::size > N, "Index out of bounds");
  using type = typename TypeAt<N - 1, TypeList<Rest...>>::type;
};

// Получение размера списка
template <typename List>
struct Size {
  static constexpr std::size_t value = List::size;
};

// Проверка наличия типа в списке
template <typename T, typename List>
struct Contains;

// Специализация для пустого списка
template <typename T>
struct Contains<T, TypeList<>> {
  static constexpr bool value = false;
};

// Специализация для непустого списка
template <typename T, typename Head, typename... Rest>
struct Contains<T, TypeList<Head, Rest...>> {
  static constexpr bool value =
      std::is_same_v<T, Head> || Contains<T, TypeList<Rest...>>::value;
};

// Получение индекса типа в списке
template <typename T, typename List, std::size_t Index = 0>
struct IndexOf;

// Специализация для пустого списка
template <typename T, std::size_t Index>
struct IndexOf<T, TypeList<>, Index> {
  static_assert(false, "Type not found in TypeList");
};

// Специализация для непустого списка (нашли тип)
template <typename T, typename... Rest, std::size_t Index>
struct IndexOf<T, TypeList<T, Rest...>, Index> {
  static constexpr std::size_t value = Index;
};

// Специализация для непустого списка (тип не совпадает)
template <typename T, typename Head, typename... Rest, std::size_t Index>
struct IndexOf<T, TypeList<Head, Rest...>, Index> {
  static constexpr std::size_t value =
      IndexOf<T, TypeList<Rest...>, Index + 1>::value;
};

// Добавление типа в конец списка
template <typename T, typename List>
struct Append;

template <typename T, typename... Types>
struct Append<T, TypeList<Types...>> {
  using type = TypeList<Types..., T>;
};

// Добавление типа в начало списка
template <typename T, typename List>
struct Prepend;

template <typename T, typename... Types>
struct Prepend<T, TypeList<Types...>> {
  using type = TypeList<T, Types...>;
};

}  // namespace type_list