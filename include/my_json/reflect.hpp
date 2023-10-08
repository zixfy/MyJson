//
// Created by wwww on 2023/8/28.
//

#ifndef CPP_JSON_PARSER_REFLECT_HPP
#define CPP_JSON_PARSER_REFLECT_HPP
#include <functional>
#include <type_traits>
#include <iostream>
#include "traits.hpp"
#include "core.hpp"
namespace MyJson {
template <typename Meta, typename T, typename F>
void for_each_meta_impl2(T &&t, F &&f) {
  f(Meta::name(), Meta::get(std::forward<T>(t)));
}

template <typename T, typename F, size_t... N>
void for_each_meta_impl(T &&t, F &&f, std::integer_sequence<size_t, N...>) {
  using OT = std::decay_t<T>;
  (void(for_each_meta_impl2<typename OT::template MetaInfo<N>>(
       std::forward<T>(t), std::forward<F>(f))),
   ...);
};

template <typename T, typename F> void for_each_meta(T &&t, F &&f) {
  constexpr size_t field_counts = std::decay_t<T>::fields_count;
  for_each_meta_impl(std::forward<T>(t), std::forward<F>(f),
                     std::make_integer_sequence<size_t, field_counts>{});
}



template <typename Meta, typename T, typename F>
void for_each_meta_with_index_impl2(T &&t, F &&f, size_t N) {
  f(Meta::name(), Meta::get(std::forward<T>(t)), N);
}

template <typename T, typename F, size_t... N>
void for_each_meta_with_index_impl(T &&t, F &&f, std::integer_sequence<size_t, N...>) {
  using OT = std::decay_t<T>;
  (void(for_each_meta_with_index_impl2<typename OT::template MetaInfo<N>>(
       std::forward<T>(t), std::forward<F>(f), N)),
   ...);
};

template <typename T, typename F> void for_each_meta_with_index(T &&t, F &&f) {
  constexpr size_t field_counts = std::decay_t<T>::fields_count;
  for_each_meta_with_index_impl(std::forward<T>(t), std::forward<F>(f),
                     std::make_integer_sequence<size_t, field_counts>{});
}

template <typename Meta, size_t Cur, size_t Tot, typename T>
void print_impl2(T &&t) {
  std::cout << Meta::name() << "<" << typeid(typename Meta::type).name()
            << ">:";
    std::cout << Meta::get(t);
  if constexpr (Cur + 1 < Tot)
    std::cout << ",";
};

template <typename T, size_t... N>
void print_impl(T &&t, std::integer_sequence<size_t, N...>) {
  (print_impl2<typename std::remove_reference_t<T>::template MetaInfo<N>, N,
               sizeof...(N)>(std::forward<T>(t)),
   ...);
};

template <typename T> void json_print(T &&t) {
  constexpr size_t field_counts = std::decay_t<T>::fields_count;
  std::cout << "{";
  print_impl(std::forward<T>(t),
             std::make_integer_sequence<size_t, field_counts>{});
  std::cout << "}";
}
} // namespace reflect
#endif // CPP_JSON_PARSER_REFLECT_HPP
