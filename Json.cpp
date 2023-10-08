//
// Created by wwww on 2023/8/28.
//

#include <my_json/core.hpp>
#include <sstream>
namespace MyJson {

auto Json::to_ostream(std::ostream &os) const -> std::ostream & {
  std::visit(
      [&os](auto &&v) {
        using OT = std::decay_t<decltype(v)>;
        if constexpr (std::is_same_v<OT, Null>) {
          os << LITERAL_NULL;
        } else if constexpr (std::is_same_v<OT, Bool>) {
          os << (v ? LITERAL_TRUE : LITERAL_FALSE);
        } else if constexpr (std::is_same_v<OT, String>) {

          os << '\"';
          text_raw_to_ostream_json(os, v);
          os << '\"';
        } else if constexpr (std::is_same_v<OT, Array>) {
          os << "[";

          size_t idx = 0, sz = v.size();
          for (auto const &e : v) {
            e.to_ostream(os);
            if (++idx != sz)
              os << ",";
          }
          os << "]";
        } else if constexpr (std::is_same_v<OT, Object>) {
          os << "{";
          size_t idx = 0, sz = v.size();
          for (auto const &e : v) {

            os << '\"';
            text_raw_to_ostream_json(os, e.first);
            os << "\":";
            (e.second).to_ostream(os);
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

auto Json::to_json_text() const -> std::string {
  std::stringstream ss;
  //  std::streamsize old_pre = ss.precision();
  //  ss.precision(std::numeric_limits<Float>::max_digits10);
  to_ostream(ss);
  //  ss.precision(old_pre);
  return ss.str();
}
auto Json::from_istream(std::istream &in) -> std::optional<Json> {
  std::string s{std::istreambuf_iterator<char>(in), {}};
  JsonParser p{s};
  return p.get();
};
auto Json::from_json_text(std::string_view sv) -> std::optional<Json> {
  JsonParser p{sv};
  return p.get();
}

void text_raw_to_json_inplace(std::string &s) {
  std::stringstream ss;
  text_raw_to_ostream_json(ss, s);
  s = ss.str();
};

std::string text_raw_to_json(const std::string &s) {
  std::string s_copy{s};
  text_raw_to_json_inplace(s_copy);
  return s_copy;
};

std::optional<std::string> text_json_to_raw(const std::string &s) {
  std::string s_copy{s};
  auto b = text_json_to_raw_inplace(s_copy);
  if (!b)
    return {};
  return s_copy;
}

std::optional<std::string> istream_json_to_raw(std::istream &in) {
  std::string s{std::istreambuf_iterator<char>(in), {}};
  return text_json_to_raw(s);
}
std::ostream &operator<<(std::ostream &out, const Json &j) {
  return j.to_ostream(out);
};
} // namespace MyJson
