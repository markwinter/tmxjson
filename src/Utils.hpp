/* MIT License. Copyright Mark Winter */

#ifndef UTILS_H_
#define UTILS_H_

#include "thirdparty/json.hpp"

using json = nlohmann::json;

namespace tmxjson {
bool check_json_var(const json& j, std::string&& key);
bool zlib_inflate(const char* src, std::size_t src_len, std::vector<unsigned char>& dst, std::size_t dst_len);
}  // namespace tmxjson

#endif
