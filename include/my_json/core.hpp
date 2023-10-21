//
// Created by wwww on 2023/8/26.
//

#ifndef CPP_JSON_PARSER_CORE_HPP
#define CPP_JSON_PARSER_CORE_HPP

#include "reflect.hpp"
#include "traits.hpp"
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <optional>
#include <sstream>
#include <unordered_map>
#include <utility>
#include <variant>
#include <vector>

namespace fs = std::filesystem;

namespace MyJson {

class Json {
public:
  JsonNode m_value;

public:
  std::ostream &to_ostream(std::ostream &os) const;
  [[nodiscard]] std::string to_json_text() const;

  static std::optional<Json> from_json_text(std::string_view);
  static std::optional<Json> from_istream(std::istream &in);

  friend std::ostream &operator<<(std::ostream &out, const Json &j);
  static constexpr inline std::string_view LITERAL_NULL = "null",
                                           LITERAL_TRUE = "true",
                                           LITERAL_FALSE = "false";
  Json &operator=(const Json &v) {
    m_value = v.m_value;
    return *this;
  };

  Json &operator=(Json &&v) {
    m_value = std::move(v.m_value);
    return *this;
  };

  Json(const Json &v) : m_value{v.m_value} {};
  Json(Json &&v) : m_value{std::move(v.m_value)} {};
  Json(const JsonNode &v) : m_value{v} {};
  Json(JsonNode &&v) : m_value{std::move(v)} {};
  Json() : m_value{Null{}} {};

  template <typename T, typename std::enable_if_t<is_native_json_value_type<
                            std::decay_t<T>>> * = nullptr>
  Json(T &&t) : m_value{std::forward<T>(t)} {};

  template <typename T,
            typename std::enable_if_t<
                std::is_same_v<T, std::string_view> ||
                std::is_same_v<const char *, std::decay_t<T>>> * = nullptr>
  Json(T t) : m_value{String{t}} {};

  template <typename T, typename std::enable_if_t<
                            std::is_integral_v<T> && !std::is_same_v<T, Bool> &&
                            !std::is_same_v<T, Integer>> * = nullptr>
  Json(T t) : m_value{static_cast<Integer>(t)} {};
  template <typename T, typename std::enable_if_t<
                            std::is_floating_point_v<T> &&
                            !std::is_same_v<T, MyJson::Float>> * = nullptr>
  Json(T t) : m_value{static_cast<Float>(t)} {};
  template <typename T, typename std::enable_if_t<
                            std::is_same_v<T, std::nullptr_t> ||
                            std::is_same_v<T, std::nullopt_t>> * = nullptr>
  Json(T t) : m_value{Null{}} {};
  template <typename T,
            typename std::enable_if_t<is_stl_range<std::decay_t<T>> &&
                                      !std::is_same_v<Array, std::decay_t<T>>>
                * = nullptr>
  Json(T &&t) {
    Array a{};
    // lvalue overload
    if constexpr (std::is_lvalue_reference_v<decltype(t)>) {
      for (auto &e : t)
        a.emplace_back(Json(e));
    } else {
      for (auto &e : t)
        a.emplace_back(Json(std::move(e)));
    }
    m_value = std::move(a);
  };

  template <typename T,
            typename std::enable_if_t<is_stl_dict<std::decay_t<T>> &&
                                      !std::is_same_v<Object, std::decay_t<T>>>
                * = nullptr>
  Json(T &&t) {
    Object o{};
    if constexpr (std::is_lvalue_reference_v<decltype(t)>) {
      for (auto &v : t)
        o.emplace(v.first, Json{v.second});
    } else {
      for (auto &v : t)
        o.emplace(v.first, Json{std::move(v.second)});
    }
    m_value = std::move(o);
  };
  template <typename T, typename std::enable_if_t<
                            is_json_convertible<std::decay_t<T>>> * = nullptr>
  Json(T &&t) : m_value{std::forward<T>(t).to_json().m_value} {};

  // as_type:: try to get native underlying type of a Json object
  template <typename T> auto as_type() const & {
    static_assert(is_native_json_value_type<T>,
                  "only down cast Json to some native MyJson value type like "
                  "Array, String, Integer, etc.");
    auto p = std::get_if<T>(&m_value);
    if (p == nullptr)
      return std::optional<std::reference_wrapper<const T>>{};
    return std::optional<std::reference_wrapper<const T>>{*p};
  }

  template <typename T> auto as_type() & {
    static_assert(is_native_json_value_type<T>,
                  "only down cast Json to some native MyJson value type like "
                  "Array, String, Integer, etc.");
    auto p = std::get_if<T>(&m_value);
    if (p == nullptr)
      return std::optional<std::reference_wrapper<T>>{};
    return std::optional<std::reference_wrapper<T>>{*p};
  }

  template <typename T> auto as_type() && {
    static_assert(is_native_json_value_type<T>,
                  "only down cast Json to some native MyJson value type like "
                  "Array, String, Integer, etc.");
    auto p = std::get_if<T>(&m_value);
    if (p == nullptr)
      return std::optional<T>{};
    return std::optional<T>{std::move(*p)};
  }

  // to_type: MyJson some non-native
  template <typename T> std::optional<T> to_type() const & {
    static_assert(std::is_same_v<T, std::remove_reference_t<T>>,
                  "cant convert Json class into some reference, use as_type if "
                  "u want ot get a optional reference wrapper of underlying "
                  "native MyJson value type");
    if constexpr (std::is_same_v<T, JsonNode>) {
      return this->m_value;
    } else if constexpr (std::is_same_v<T, Json>) {
      return *this;
    } else if constexpr (is_native_json_value_type<T>) {
      auto p = std::get_if<T>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return *p;
    } else if constexpr (is_stl_range<T>) {
      auto p = std::get_if<Array>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      T ret{};
      using ET = typename T::value_type;
      for (const auto &e : *p) {
        auto &&maye = e.to_type<ET>();
        if (!maye.has_value())
          return std::nullopt;
        if constexpr (is_stl_set<T>)
          ret.insert(maye.value());
        else
          ret.emplace_back(maye.value());
      }
      return std::optional{std::move(ret)};
    } else if constexpr (is_stl_dict<T>) {
      auto p = std::get_if<Object>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      T ret{};
      for (auto const &e : *p) {
        auto &&maye = e.second.to_type<typename T::mapped_type>();
        if (!maye.has_value())
          return std::nullopt;
        ret.emplace(e.first, maye.value());
      }
      return std::optional{std::move(ret)};
    } else if constexpr (std::is_null_pointer_v<T> ||
                         std::is_same_v<T, std::nullopt_t>) {
      auto p = std::get_if<Null>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return std::optional{T{}};

    } else if constexpr (std::is_integral_v<T>) {
      auto p = std::get_if<Integer>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return static_cast<T>(*p);
    } else if constexpr (std::is_floating_point_v<T>) { 
      auto p = std::get_if<Float>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return static_cast<T>(*p);
    }
    else {
        return T::from_json(*this);
    }
  }

  // use to_type instead if u want to down cast, which will yield a
  // reference_wrapper if MyJson object itself is a lvalue
  //  template <typename T> static auto to_type(Json &j) = delete;

  template <typename T> std::optional<T> to_type() && {
    static_assert(std::is_same_v<T, std::remove_reference_t<T>>,
                  "u are trying to get a ref on prvalue MyJson::Json, and cant "
                  "convert Json class into some reference, use as_type if "
                  "u want ot get a optional reference wrapper of underlying "
                  "native MyJson value type");
    if constexpr (std::is_same_v<T, JsonNode>) {
      return std::optional {std::move(this->m_value)};
    } else if constexpr (std::is_same_v<T, Json>) {
      return std::optional {std::move(*this)};
    } else if constexpr (is_native_json_value_type<T>) {
      auto p = std::get_if<T>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return std::optional {std::move(*p)};
    } else if constexpr (is_stl_range<T>) {
      auto p = std::get_if<Array>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      T ret{};
      using ET = typename T::value_type;
      for (auto &e : *p) {
        auto &&maye = std::move(e).to_type<ET>();
        if (!maye.has_value())
          return std::nullopt;
        if constexpr (is_stl_set<T>)
          ret.insert(std::move(maye.value()));
        else
          ret.emplace_back(std::move(maye.value()));
      }
      return std::optional {std::move(ret)};
    } else if constexpr (is_stl_dict<T>) {
      auto p = std::get_if<Object>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      T ret{};
      using ET = typename T::mapped_type;
      for (auto &e : *p) {
        auto &&maye = std::move(e.second).to_type<ET>();
        if (!maye.has_value())
          return std::nullopt;
        ret.emplace(e.first, std::move(maye.value()));
      }
      return std::optional {std::move(ret)};
    } else if constexpr (std::is_null_pointer_v<T> ||
                         std::is_same_v<T, std::nullopt_t>) {
      auto p = std::get_if<Null>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return std::optional {T{}};

    } else if constexpr (std::is_integral_v<T>) {
      auto p = std::get_if<Integer>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return static_cast<T>(*p);
    } else if constexpr (std::is_floating_point_v<T>) {
      auto p = std::get_if<Float>(&(this->m_value));
      if (p == nullptr)
        return std::nullopt;
      return static_cast<T>(*p);
    } else {
        return T::from_json(std::move(*this));
    }
  }
};

class JsonParser {
public:
  std::optional<JsonNode> parse_array();
  std::optional<JsonNode> parse_object();
  std::optional<JsonNode> parse_string();
  std::optional<JsonNode> parse_numeric();
  std::optional<JsonNode> parse_null();
  std::optional<JsonNode> parse_true();
  std::optional<JsonNode> parse_false();
  std::optional<JsonNode> parse_node();
  void skip_blank();
  std::string_view m_text;
  std::size_t m_pivot;

public:
  // avoid dangling string_view
  explicit JsonParser(std::string_view sv) : m_text{sv}, m_pivot{0} {};
  std::optional<Json> get();
};

// JsonParser
void text_raw_to_ostream_json(std::ostream &os, std::string_view sv);
bool text_json_to_raw_inplace(std::string &);

// Json
std::string text_raw_to_json(const std::string &s);
void text_raw_to_json_inplace(std::string &s);
std::optional<std::string> text_json_to_raw(const std::string &s);
std::optional<std::string> istream_json_to_raw(std::istream &in);
} // namespace MyJson

#include "macro_util.hpp"
#endif // CPP_JSON_PARSER_CORE_HPP
