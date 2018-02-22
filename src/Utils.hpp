/* MIT License. Copyright Mark Winter */

#ifndef UTILS_H_
#define UTILS_H_

#include "thirdparty/json.hpp"

using json = nlohmann::json;

namespace tmxjson {
bool check_json_var(const json& j, std::string&& key);
}  // namespace tmxjson

#endif
