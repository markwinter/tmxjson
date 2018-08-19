/* MIT License. Copyright Mark Winter */

#include "thirdparty/base64.hpp"
#include "Utils.hpp"
#include "Parsers.hpp"
#include "TypedProperty.hpp"

#include <string>
#include <iostream>

namespace tmxjson {
void from_json(const json& object_json, Object& object) {
  object.SetId(object_json["id"]);

  if (check_json_var(object_json, "gid"))
    object.SetGid(object_json["gid"]);

  object.SetObjectType(ObjectType::kRectangle);

  if (check_json_var(object_json, "ellipse"))
    object.SetObjectType(ObjectType::kEllipse);

  if (check_json_var(object_json, "point"))
    object.SetObjectType(ObjectType::kPoint);

  if (check_json_var(object_json, "polygon")) {
    object.SetObjectType(ObjectType::kPolygon);

    std::vector<std::pair<float, float>> data;
    for (auto& pair : object_json["polygon"])
      data.emplace_back(pair["x"], pair["y"]);

    object.SetDataPoints(data);
  }

  if (check_json_var(object_json, "polyline")) {
    object.SetObjectType(ObjectType::kPolyline);

    std::vector<std::pair<float, float>> data;
    for (auto& pair : object_json["polyline"])
      data.emplace_back(pair["x"], pair["y"]);

    object.SetDataPoints(data);
  }

  if (check_json_var(object_json, "text")) {
    object.SetObjectType(ObjectType::kText);
    object.SetTextObject(object_json["text"]["text"], object_json["text"]["wrap"]);
  }

  if (check_json_var(object_json, "properties"))
    parse_properties(object.GetProperties(), object_json["properties"]);

  object.SetName(object_json["name"]);
  object.SetType(object_json["type"]);
  object.SetRotation(object_json["rotation"]);
  object.SetVisible(object_json["visible"]);
  object.SetX(object_json["x"]);
  object.SetY(object_json["y"]);
  object.SetHeight(object_json["height"]);
  object.SetWidth(object_json["width"]);
}

void from_json(const json& layer_json, Layer& layer) {
  layer.SetType(layer_json["type"].get<std::string>());

  if (layer.GetType() == LayerType::kGroup) {
    layer.SetLayers(layer_json["layers"]);
  } else if (layer.GetType() == LayerType::kTileLayer) {
    layer.SetHeight(layer_json["height"]);
    layer.SetWidth(layer_json["width"]);
    try {
      std::string raw_data = layer_json["data"];

      if (layer_json.at("encoding") == "base64")
        raw_data = base64_decode(raw_data);
      std::vector<unsigned char> uncompressed_data;

      if (check_json_var(layer_json, "compression"))
        zlib_inflate(raw_data.c_str(), raw_data.length() * sizeof(unsigned char), uncompressed_data, raw_data.length() * 5);
      else
        uncompressed_data.insert(uncompressed_data.end(), raw_data.begin(), raw_data.end());

      std::vector<uint32_t> gids;
      for (auto i = 0u; i < uncompressed_data.size() - 3u; i += 4u) {
        uint32_t id = uncompressed_data[i] |
                      uncompressed_data[i + 1] << 8 |
                      uncompressed_data[i + 2] << 16 |
                      uncompressed_data[i + 3] << 24;
        // TODO(Mark): Tile-flipping (3 most significant bits)
        gids.push_back(id);
      }

      layer.SetData(gids);
    } catch (json::out_of_range& e) {
      // If no 'encoding' key then data is just plain int array
      layer.SetData(layer_json["data"]);
    }
  } else if (layer.GetType() == LayerType::kObjectGroup) {
    layer.SetObjects(layer_json["objects"]);

    if (layer_json["draworder"] == "topdown")
      layer.SetDrawOrder(DrawOrder::kTopDown);
    else if (layer_json["draworder"] == "index")
      layer.SetDrawOrder(DrawOrder::kIndex);
  } else if (layer.GetType() == LayerType::kImageLayer) {
    layer.SetImage(layer_json["image"]);
  }

  // All layers can optionally have offsets. Only appear in json if they are non-0
  if (check_json_var(layer_json, "offsetx"))
    layer.SetOffsetX(layer_json["offsetx"]);

  if (check_json_var(layer_json, "offsety"))
    layer.SetOffsetY(layer_json["offsety"]);

  if (check_json_var(layer_json, "properties"))
    parse_properties(layer.GetProperties(), layer_json["properties"]);

  layer.SetX(layer_json["x"]);
  layer.SetY(layer_json["y"]);
  layer.SetName(layer_json["name"]);
  layer.SetOpacity(layer_json["opacity"]);
  layer.SetVisible(layer_json["visible"]);
}

void from_json(const json& tileset_json, TileSet& tileset) {
  tileset.SetColumns(tileset_json["columns"]);
  tileset.SetFirstGid(tileset_json["firstgid"]);

  tileset.SetName(tileset_json["name"]);
  tileset.SetType(TileSetType::kTileSet);

  tileset.SetImage(tileset_json["image"]);
  tileset.SetImageWidth(tileset_json["imagewidth"]);
  tileset.SetImageHeight(tileset_json["imageheight"]);

  tileset.SetTileCount(tileset_json["tilecount"]);
  tileset.SetTileHeight(tileset_json["tileheight"]);
  tileset.SetTileWidth(tileset_json["tilewidth"]);
  tileset.SetSpacing(tileset_json["spacing"]);
  tileset.SetMargin(tileset_json["margin"]);

  if (check_json_var(tileset_json, "tileoffset"))
    tileset.SetOffset(tileset_json["tileoffset"]["x"], tileset_json["tileoffset"]["y"]);

  if (check_json_var(tileset_json, "grid")) {
    GridOrientation grid_orientation = GridOrientation::kOrthogonal;
    if (tileset_json["grid"]["orientation"] == "isometric")
      grid_orientation = GridOrientation::kIsometric;

    tileset.SetGrid(grid_orientation, tileset_json["grid"]["width"], tileset_json["grid"]["height"]);
  }

  if (check_json_var(tileset_json, "properties"))
    parse_properties(tileset.GetProperties(), tileset_json["properties"]);
}
}  // namespace tmxjson
