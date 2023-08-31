//
// Created by wwww on 2023/8/28.
//

#include <json/core.hpp>
#include <sstream>
namespace json {

auto Json::to_json_stream(std::ostream &os) const -> std::ostream & {
  std::visit(
      [&os](auto &&v) {
        using OT = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<OT, Null>) {
          os << LITERAL_NULL;
        } else if constexpr (std::is_same_v<OT, Bool>) {
          os << (v ? LITERAL_TRUE : LITERAL_FALSE);
        } else if constexpr (std::is_same_v<OT, String>) {

          os << '\"';
          raw_text_to_json_stream(os, v);
          os << '\"';
        } else if constexpr (std::is_same_v<OT, Array>) {
          os << "[";

          size_t idx = 0, sz = v.size();
          for (auto const &e : v) {
            e.to_json_stream(os);
            if (++idx != sz)
              os << ",";
          }
          os << "]";
        } else if constexpr (std::is_same_v<OT, Object>) {
          os << "{";
          size_t idx = 0, sz = v.size();
          for (auto const &e : v) {

            os << '\"';
            raw_text_to_json_stream(os, e.first);
            os << "\":";
            (e.second).to_json_stream(os);
            if (++idx != sz)
              os << ",";
          }
          os << "}";
        } else {
          os << v;
        }
      },
      m_value);
  return os;
}

auto Json::to_json_text() -> std::string {
  std::stringstream ss;
  //  std::streamsize old_pre = ss.precision();
  //  ss.precision(std::numeric_limits<Float>::max_digits10);
  to_json_stream(ss);
  //  ss.precision(old_pre);
  return ss.str();
}

std::ostream &operator<<(std::ostream &os, const Json &j) {
  return j.to_json_stream(os);
}

auto  Json::from_json_text(std::string_view sv) -> std::optional<Json>  {
  JsonParser p{sv};
  return  p.get();
};

} // namespace json
