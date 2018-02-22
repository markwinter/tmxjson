/* MIT License. Copyright Mark Winter */

#include "Utils.hpp"

namespace tmxjson {
bool check_json_var(const json& j, std::string&& key) {
  try {
    j.at(key);
    return true;
  } catch (json::out_of_range& e) {
    return false;
  }

  return false;
}
}  // namespace tmxjson
