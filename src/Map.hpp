/* MIT License. Copyright 2018 Mark Winter */

#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include <string>

#include "json.hpp"
#include "Layer.hpp"
#include "TileSet.hpp"

using json = nlohmann::json;

namespace tmxjson {

enum class Orientation { kOrthogonal, kIsometric, kStaggered, kHexagonal };
enum class RenderOrder { kRightDown, kRightUp, kLeftDown, kLeftUp };

class Map {
 public:
  Map(std::string file);

  std::string GetBackgroundColor() const;
  bool IsInfinite() const;
  int GetNextObjectId() const;

  std::vector<Layer>& GetLayers();
  std::vector<TileSet>& GetTileSets();

  Orientation GetOrientation() const;
  RenderOrder GetRenderOrder() const;

  int GetTileWidth() const;
  int GetTileHeight() const;
  int GetHeight() const;
  int GetWidth() const;

  std::string GetType() const;
  int GetVersion() const;
  std::string GetTiledVersion() const;

 private:
  std::vector<Layer> layers_;
  std::vector<TileSet> tile_sets_;

  std::string background_color_;
  bool infinite_;
  int next_object_id_;

  Orientation orientation_;
  RenderOrder render_order_;

  int tile_width_;
  int tile_height_;
  int height_;
  int width_;

  std::string type_;
  int version_;
  std::string tiled_version_;
};
}  // namespace tmxjson

#endif
