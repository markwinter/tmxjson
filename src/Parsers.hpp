/* MIT License. Copyright Mark Winter */

#ifndef PARSERS_H_
#define PARSERS_H_

#include "thirdparty/json.hpp"
#include "Object.hpp"
#include "Layer.hpp"
#include "TileSet.hpp"

using json = nlohmann::json;

namespace tmxjson {
void from_json(const json& object_json, Object& object);
void from_json(const json& layer_json, Layer& layer);
void from_json(const json& tileset_json, TileSet& tileset);
}  // namespace tmxjson

#endif
