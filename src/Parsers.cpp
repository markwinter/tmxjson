/* MIT License. Copyright Mark Winter */

#include "thirdparty/base64.hpp"
#include "Parsers.hpp"

namespace tmxjson {
void from_json(const json& object_json, Object& object) {
  object.SetId(object_json["id"]);
  try {
    object.SetGid(object_json.at("gid"));
  } catch (json::out_of_range& e) {
    object.SetGid(0);
  }
  object.SetName(object_json["name"]);
  object.SetType(object_json["type"]);

  object.SetObjectType(ObjectType::kRectangle);

  try {
    if (object_json.at("ellipse"))
      object.SetObjectType(ObjectType::kEllipse);
  } catch (json::out_of_range& e) {}

  try {
    if (object_json.at("point"))
      object.SetObjectType(ObjectType::kPoint);
  } catch (json::out_of_range& e) {}

  try {
    if (object_json.at("polygon").size() >= 0)
      object.SetObjectType(ObjectType::kPolygon);

    std::vector<std::pair<float, float>> data;
    for (auto& pair : object_json["polygon"])
      data.emplace_back(pair["x"], pair["y"]);

    object.SetDataPoints(data);
  } catch (json::out_of_range& e) {}

  try {
    if (object_json.at("polyline").size() >= 0)
      object.SetObjectType(ObjectType::kPolyline);

    std::vector<std::pair<float, float>> data;
    for (auto& pair : object_json["polyline"])
      data.emplace_back(pair["x"], pair["y"]);

    object.SetDataPoints(data);
  } catch (json::out_of_range& e) {}

  object.SetRotation(object_json["rotation"]);
  object.SetVisible(object_json["visible"]);
  object.SetX(object_json["x"]);
  object.SetY(object_json["y"]);
  object.SetHeight(object_json["height"]);
  object.SetWidth(object_json["width"]);
}

void from_json(const json& layer_json, Layer& layer) {
  std::string type = layer_json["type"];
  if (type == "tilelayer")
    layer.SetType(LayerType::kTileLayer);
  else if (type == "objectgroup")
    layer.SetType(LayerType::kObjectGroup);
  else if (type == "imagelayer")
    layer.SetType(LayerType::kImageLayer);
  else if (type == "group")
    layer.SetType(LayerType::kGroup);

  if (layer.GetType() == LayerType::kGroup) {
    layer.SetLayers(layer_json["layers"]);
  } else if (layer.GetType() == LayerType::kTileLayer) {
    layer.SetHeight(layer_json["height"]);
    layer.SetWidth(layer_json["width"]);
    try {
      std::string data = layer_json["data"];

      if (layer_json.at("encoding") == "base64")
        data = base64_decode(data);

      //if (layer_json.at("compression"))
        //zlib_inflate(data.c_str(), data.length(), data, data.size());

      std::vector<unsigned char> byte_data;
      byte_data.insert(byte_data.end(), data.begin(), data.end());

      std::vector<uint32_t> gids;
      for (auto i = 0u; i < byte_data.size() - 3u; i += 4u) {
        uint32_t id = byte_data[i] |
                      byte_data[i + 1] << 8 |
                      byte_data[i + 2] << 16 |
                      byte_data[i + 3] << 24;
        gids.push_back(id);
      }

      // TODO(Mark): Tile-flipping

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
  try {
    layer.SetOffsetX(layer_json.at("offsetx"));
  } catch (json::out_of_range& e) {
    layer.SetOffsetX(0.0f);
  }
  try {
    layer.SetOffsetX(layer_json.at("offsety"));
  } catch (json::out_of_range& e) {
    layer.SetOffsetX(0.0f);
  }

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
}
}
