/* MIT License. Copyright 2018 Mark Winter */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "Parsers.hpp"
#include "Map.hpp"

namespace tmxjson {
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
    tiled_version_(""),
    map_loaded_(false) {}

Map::Map(std::string file)
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
    tiled_version_(""),
    map_loaded_(false) {
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
