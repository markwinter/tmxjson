/* MIT License. Copyright 2018 Mark Winter */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "base64.hpp"
#include "json.hpp"
#include "Map.hpp"

using json = nlohmann::json;

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
      if (layer_json.at("encoding") == "base64")
        layer.SetData(base64_decode(layer_json["data"]));
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

Map::Map()
  : background_color_(""),
    infinite_(false),
    next_object_id_(0),
    orientation_(Orientation::kNone),
    render_order_(RenderOrder::kNone),
    tile_width_(0),
    tile_height_(0),
    height_(0),
    width_(0),
    type_(""),
    version_(0),
    tiled_version_(0),
    map_loaded_(false) {}

Map::Map(std::string file) {
  std::ifstream ifs(file);
  json map_json;
  ifs >> map_json;

  type_ = map_json["type"];
  version_ = map_json["version"];
  tiled_version_ = map_json["tiledversion"];

  try {
    background_color_ = map_json.at("backgroundcolor");
  } catch (json::out_of_range& e) {
    background_color_ = "";
  }
  infinite_ = map_json["infinite"];
  next_object_id_ = map_json["nextobjectid"];

  tile_width_ = map_json["tilewidth"];
  tile_height_ = map_json["tileheight"];
  width_ = map_json["width"];
  height_ = map_json["height"];

  std::string orientation = map_json["orientation"];
  if (orientation == "orthogonal")
    orientation_ = Orientation::kOrthogonal;
  else if (orientation == "isometric")
    orientation_ = Orientation::kIsometric;
  else if (orientation == "staggered")
    orientation_ = Orientation::kStaggered;
  else if (orientation == "hexagonal")
    orientation_ = Orientation::kHexagonal;

  // If orientation is orthogonal it has a rendering order too
  if (orientation_ == Orientation::kOrthogonal) {
    std::string render_order = map_json["renderorder"];
    if (render_order == "right-down")
      render_order_ = RenderOrder::kRightDown;
    else if (render_order == "right-up")
      render_order_ = RenderOrder::kRightUp;
    else if (render_order == "left-down")
      render_order_ = RenderOrder::kLeftDown;
    else if (render_order == "left-up")
      render_order_ = RenderOrder::kLeftUp;
  }

  for (auto& layer : map_json["layers"])
    layers_.push_back(layer);

  for (auto& tile_set : map_json["tilesets"])
    tile_sets_.push_back(tile_set);

  map_loaded_ = true;
}

bool Map::IsMapLoaded() const {
  return map_loaded_;
}

std::string Map::GetBackgroundColor() const {
  return background_color_;
}

bool Map::IsInfinite() const {
  return infinite_;
}

int Map::GetNextObjectId() const {
  return next_object_id_;
}

std::vector<Layer>& Map::GetLayers() {
  return layers_;
}

std::vector<TileSet>& Map::GetTileSets() {
  return tile_sets_;
}

Orientation Map::GetOrientation() const {
  return orientation_;
}

RenderOrder Map::GetRenderOrder() const {
  return render_order_;
}

int Map::GetTileWidth() const {
  return tile_width_;
}

int Map::GetTileHeight() const {
  return tile_height_;
}

int Map::GetHeight() const {
  return height_;
}

int Map::GetWidth() const {
  return width_;
}

std::string Map::GetType() const {
  return type_;
}

int Map::GetVersion() const {
  return version_;
}

std::string Map::GetTiledVersion() const {
  return tiled_version_;
}
}  // namespace tmxjson
