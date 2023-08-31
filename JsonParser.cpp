//
// Created by wwww on 2023/8/28.
//
#include <json/core.hpp>
namespace json {
void raw_text_to_json_stream(std::ostream &os, std::string_view sv) {
  for (auto c : sv)
    switch (c) {
    case '\\': {
      os << "\\\\";
      break;
    }
    case '\"': {
      os << "\\\"";
      break;
    }
    case '/': {
      os << "\\/";
      break;
    }
    case '\b': {
      os << "\\b";
      break;
    }
    case '\f': {
      os << "\\f";
      break;
    }
    case '\n': {
      os << "\\n";
      break;
    }
    case '\r': {
      os << "\\r";
      break;
    }
    case '\t': {
      os << "\\t";
      break;
    }
    default: {
      os << c;
      break;
    }
    }
}
void raw_text_to_json_stream(std::ostream &os, const char *s) {
  raw_text_to_json_stream(os, std::string_view{s});
}
std::string raw_text_to_json_text(const std::string &s) {
  std::stringstream ss;
  raw_text_to_json_stream(ss, s);
  return ss.str();
}

bool json_text_to_raw_text_inplace(std::string &s) {
  if (s.empty())
    return true;
  if (s.back() == '\\' && s.size() > 1 && s[s.size() - 2] != '\\')
    return false;
  std::vector<std::size_t> to_converted_indexes{};
  for (size_t i = 0; i < s.size(); ++i)
    if (s[i] == '\\')
      to_converted_indexes.emplace_back(i++);
  to_converted_indexes.emplace_back(s.size());
  size_t pc = 0;
  auto p_nxt = to_converted_indexes[pc];
  auto p1 = p_nxt;
  auto p2 = p1;
  for (; p1 < s.size(); ++p1) {
    if (p1 == p_nxt) {
      switch (s[++p1]) {

      case '\\': {
        s[p2] = '\\';
        break;
      }
      case '\"': {
        s[p2] = '\"';
        break;
      }
      case '/': {

        s[p2] = '/';
        break;
      }
      case 'b': {
        s[p2] = '\b';
        break;
      }
      case 'f': {
        s[p2] = '\f';
        break;
      }
      case 'n': {
        s[p2] = '\n';
        break;
      }
      case 'r': {
        s[p2] = '\r';
        break;
      }
      case 't': {
        s[p2] = '\t';
        break;
      }
      default: {
        return false;
      }
      }
      p_nxt = to_converted_indexes[++pc];
      ++p2;
    } else {
      s[p2++] = s[p1];
    }
  }
  s.resize(p2);
  return true;
}

std::string json_text_to_raw_text(const std::string &s) {
  std::string s_copy{s};
  auto b = json_text_to_raw_text_inplace(s_copy);
  if (!b)
    throw std::runtime_error{"bad json_string_to_raw_string"};
  return s_copy;
}

auto JsonParser::skip_blank() -> void {
  while (m_pivot < m_text.size() && std::isspace(m_text[m_pivot]))
    ++m_pivot;
}

auto JsonParser::parse_null() -> std::optional<JsonNode> {
  static constexpr auto null_len = Json::LITERAL_NULL.size();
  if (m_pivot + null_len <= m_text.size() &&
      m_text.substr(m_pivot, null_len) == Json::LITERAL_NULL) {
    m_pivot += null_len;
    return Null{};
  }
  return {};
}

auto JsonParser::parse_true() -> std::optional<JsonNode> {
  static constexpr auto true_len = Json::LITERAL_TRUE.size();
  if (m_pivot + true_len <= m_text.size() &&
      m_text.substr(m_pivot, true_len) == Json::LITERAL_TRUE) {
    m_pivot += true_len;
    return true;
  }
  return {};
}

auto JsonParser::parse_false() -> std::optional<JsonNode> {
  static constexpr auto false_len = Json::LITERAL_FALSE.size();
  if (m_pivot + false_len <= m_text.size() &&
      m_text.substr(m_pivot, false_len) == Json::LITERAL_FALSE) {
    m_pivot += false_len;
    return false;
  }
  return {};
}

auto JsonParser::parse_string() -> std::optional<JsonNode> {
  m_pivot++; // "
  size_t nxt_pivot = m_pivot;
  while (nxt_pivot < m_text.size() &&
         (m_text[nxt_pivot] != '"' || m_text[nxt_pivot - 1] == '\\')) {
    nxt_pivot++;
  }
  if (nxt_pivot == m_text.size())
    return {};
  std::string s = std::string{m_text.substr(m_pivot, nxt_pivot - m_pivot)};
  m_pivot = nxt_pivot + 1; // "
  auto b = json_text_to_raw_text_inplace(s);
  if (!b)
    return {};
  return {std::move(s)};
}

auto JsonParser::parse_numeric() -> std::optional<JsonNode> {
  bool is_float = false;
  auto nxt_pivot = m_pivot;
  while (nxt_pivot < m_text.size()) {
    if (m_text[nxt_pivot] == 'e' || m_text[nxt_pivot] == '.')
      is_float = true;
    else if (!std::isdigit(m_text[nxt_pivot]))
      break;
    ++nxt_pivot;
  }
  auto number = std::string{m_text.substr(m_pivot, nxt_pivot - m_pivot)};
  m_pivot = nxt_pivot;
  if (is_float) {
    try {
      return std::stod(number);
    } catch (...) {
      return {};
    }
  } else {
    try {
      return std::stoll(number);
    } catch (...) {
      return {};
    }
  }
}

auto JsonParser::parse_array() -> std::optional<JsonNode> {
  m_pivot++; // [
  Array arr;
  while (m_pivot < m_text.size()) {
    skip_blank();
    // lacks ']'
    if (m_pivot >= m_text.size())
      return {};
    // okay ']'
    if (m_text[m_pivot] == ']') {
      m_pivot++;
      return {std::move(arr)};
    }
    // comma
    else if (m_text[m_pivot] == ',') {
      m_pivot++;
      continue;
    }
    // value
    auto &&node = parse_node();
    if (!node.has_value())
      return {};
    arr.emplace_back(std::move(node.value()));
  }
  return {};
}

auto JsonParser::parse_object() -> std::optional<JsonNode> {
  m_pivot++; // {
  Object obj;
  while (m_pivot < m_text.size()) {
    skip_blank();
    if (m_pivot >= m_text.size())
      return {};
    if (m_text[m_pivot] == '}') {
      m_pivot++;
      return {std::move(obj)};
    } else if (m_text[m_pivot] == ',') {
      m_pivot++;
      continue;
    }
    auto &&node = parse_string();
    if (!node.has_value())
      return {};
    auto &s = std::get<String>(node.value()); // "key"
    skip_blank();
    if (m_pivot == m_text.size() || m_text[m_pivot] != ':')
      return {};
    ++m_pivot;
    // "key" :
    skip_blank();
    if (m_pivot == m_text.size())
      return {};
    auto &&v_node = parse_node();
    if (!v_node.has_value())
      return {};
    obj.emplace(s, std::move(v_node.value()));
  }
  return {};
}

auto JsonParser::parse_node() -> std::optional<JsonNode> {
  if (m_pivot >= m_text.size())
    return {};
  switch (m_text[m_pivot]) {
  case 'n':
    return parse_null();
  case 't':
    return parse_true();
  case 'f':
    return parse_false();
  case '"':
    return parse_string();
  case '[':
    return parse_array();
  case '{':
    return parse_object();
  default:
    return parse_numeric();
  }
}

std::optional<Json> JsonParser::get() {
  skip_blank();
  auto node = parse_node();
  if (!node.has_value()) {
    return {};
  }
  return Json{std::move(node.value())};
}

} // namespace json