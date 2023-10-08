//
// Created by wwww on 2023/8/28.
//

#ifndef CPP_JSON_PARSER_TYPES_HPP
#define CPP_JSON_PARSER_TYPES_HPP
#include <map>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
namespace MyJson {
class Json;
class JsonParser;
using Null = std::monostate;
using Object = std::map<std::string, Json>;
using Bool = bool;
using String = std::string;
using Float = double;
using Integer = int64_t;
using Array = std::vector<Json>;
template<typename T> using ArrayFor = std::vector<T>;
template<typename T> using MapFor = std::map<std::string, T>;
using JsonNode =
    std::variant<Null, Bool, Float, Integer, String, Array, Object>;
}
#endif // CPP_JSON_PARSER_TYPES_HPP
