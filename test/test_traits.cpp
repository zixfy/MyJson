//
// Created by wwww on 2023/8/28.
//

#include "../include/json/core.hpp"
using namespace MyJson;
struct J {
  static J from_json (const Json &) {return{};};
};
struct A {
  Json to_json () {return{};};
  static A from_json (const Json &) {return{};};
};
#include <string>
template <typename T>
class has_x
{
  template <typename U>
  static auto Test(const U* u) -> decltype((void)(u->is_reflectable_class), std::true_type());

  static auto Test(...) -> std::false_type;

public:
  static constexpr bool value = decltype(Test((T*)nullptr))::value;
};

template <typename T> void print(T&& obj) {
  if constexpr (has_x<std::decay_t<decltype(obj)>>::value) {
    std::cout << "{";
    reflect::for_each_meta_with_index(
        obj, [](auto &&name, auto &&value, size_t idx) {
          std::cout << "(" << typeid(value).name() << ")" << name << ":";
          print(value);
          std::cout << ",";
        });std::cout << "}";
  } else std::cout << obj;
}

DEF_DATA_CLASS(SomeNetClass, (int) aaasdsa, (long) sadas );
DEF_DATA_CLASS(SomeClass, (std::string) str_mem, (double) f_mem, (SomeNetClass) nested );
struct G {Json to_json() {return {};}};
int main() {
  SomeClass f{"nihao", 11.2, {2, 21312}};
  print(f);
  static_assert(is_json_convertible<G>);
  static_assert(is_native_json_value_type<Null>);
  static_assert(is_native_json_value_type<Integer>);
  static_assert(is_native_json_value_type<Bool>);
  static_assert(is_native_json_value_type<Float>);
  static_assert(is_native_json_value_type<String>);
  static_assert(is_native_json_value_type<Array>);
  static_assert(is_native_json_value_type<Object>);

  static_assert(!is_native_json_value_type<int>);
  static_assert(!is_native_json_value_type<char>);
  static_assert(!is_native_json_value_type<short>);
  static_assert(is_native_json_value_type<int64_t>);
  static_assert(!is_native_json_value_type<uint8_t>);
  static_assert(!is_native_json_value_type<uint16_t>);
  static_assert(!is_native_json_value_type<uint32_t>);
  static_assert(!is_native_json_value_type<uint64_t>);

  static_assert(!is_native_json_value_type<float>);
  static_assert(is_native_json_value_type<double>);
  static_assert(!is_native_json_value_type<long double>);

  static_assert(is_native_json_value_type<std::vector<Json>>);
  static_assert(!is_native_json_value_type<std::unordered_map<String, Json>>);

  static_assert(is_native_json_value_type<std::map<String, Json>>);
  static_assert(!is_native_json_value_type<std::set<String, Json>>);

  static_assert(is_stl_range<std::set<int>>);
  static_assert(is_stl_dict<std::map<std::string, Json>>);
  static_assert(std::is_null_pointer_v<decltype(nullptr)>);
  static_assert(is_stl_dict<std::map<std::string, Json>>);

//  static_assert(!is_json_constructible<int>);
//  static_assert(is_json_constructible<J>);
//  static_assert(is_json_constructible<std::multiset<Json>>);
}