//
// Created by wwww on 2023/8/28.
//

#ifndef CPP_JSON_PARSER_TRAITS_HPP
#define CPP_JSON_PARSER_TRAITS_HPP
#include "types.hpp"
namespace MyJson::detail {
template <typename T, typename = void>
struct is_json_convertible_impl : std::false_type {};

template <typename T>
struct is_json_convertible_impl<
    T, std::void_t<decltype(std::declval<T>().to_json())>> : std::true_type {

  static_assert(
      std::is_same_v<MyJson::Json, decltype(std::declval<T>().to_json())>,
      "oops, T::to_json() must return Json here");
};

template <typename T, typename = void>
struct is_json_constructible_impl : std::false_type {};

template <typename T>
struct is_json_constructible_impl<
    T, std::void_t<decltype(T::from_json(std::declval<MyJson::Json>()))>>
    : std::true_type {
  static_assert(
      std::is_same_v<T, decltype(T::from_json(std::declval<MyJson::Json>()))>,
      "oops, T::from_json() must return T here");
};

template <typename, typename> struct is_native_json_value_type_impl {};
template <typename T, size_t... N>
struct is_native_json_value_type_impl<T, std::integer_sequence<size_t, N...>> {
  constexpr static inline bool value =
      (std::is_same_v<T, std::variant_alternative_t<N, MyJson::JsonNode>> || ...);
};

} // namespace MyJson::detail
namespace MyJson {

template <typename T> constexpr static inline bool is_stl_sequence = false;
template <typename T>
constexpr static inline bool is_stl_sequence<std::list<T>> = true;
template <typename T>
constexpr static inline bool is_stl_sequence<std::vector<T>> = true;

template <typename T> constexpr static inline bool is_stl_set = false;
template <typename T>
constexpr static inline bool is_stl_set<std::set<T>> = true;
template <typename T>
constexpr static inline bool is_stl_set<std::multiset<T>> = true;
template <typename T>
constexpr static inline bool is_stl_set<std::unordered_set<T>> = true;
template <typename T>
constexpr static inline bool is_stl_set<std::unordered_multiset<T>> = true;

template <typename T>
constexpr static inline bool is_stl_range = is_stl_set<T> || is_stl_sequence<T>;

template <typename T> constexpr static inline bool is_stl_dict = false;
template <typename K, typename V>
constexpr static inline bool is_stl_dict<std::map<K, V>> = true;
template <typename K, typename V>
constexpr static inline bool is_stl_dict<std::multimap<K, V>> = true;
template <typename K, typename V>
constexpr static inline bool is_stl_dict<std::unordered_map<K, V>> = true;
template <typename K, typename V>
constexpr static inline bool is_stl_dict<std::unordered_multimap<K, V>> = true;

template <typename T> constexpr static inline bool is_std_optional = false;
template <typename T>
constexpr static inline bool is_std_optional<std::optional<T>> = true;

template <typename T>
constexpr static inline bool is_json_convertible =
    detail::is_json_convertible_impl<T>::value;

template <typename T>
constexpr static inline bool is_json_constructible =
    detail::is_json_constructible_impl<T>::value;

template <typename T>
constexpr static inline bool is_native_json_value_type =
    detail::is_native_json_value_type_impl<
        T, std::make_integer_sequence<size_t,
                                      std::variant_size_v<JsonNode>>>::value;

} // namespace MyJson
#endif // CPP_JSON_PARSER_TRAITS_HPP
