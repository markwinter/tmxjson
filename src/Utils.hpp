/* MIT License. Copyright Mark Winter */

#ifndef UTILS_H_
#define UTILS_H_

#include "thirdparty/json.hpp"
#include "Property.hpp"
#include "Tile.hpp"

using json = nlohmann::json;

namespace tmxjson {
bool check_json_var(const json& j, std::string&& key);
bool zlib_inflate(const char* src, std::size_t src_len, std::vector<unsigned char>& dst, std::size_t dst_len);
void parse_properties(std::vector<std::shared_ptr<Property>>& properties, const json& j);
std::vector<Tile> parse_tile_data(const std::vector<unsigned char>& data);
}  // namespace tmxjson

#endif
