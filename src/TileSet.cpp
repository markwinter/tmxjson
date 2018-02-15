/* MIT License. Copyright 2018 Mark Winter */

#include "TileSet.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace tmxjson {
int TileSet::GetColumns() const {
  return columns_;
}

void TileSet::SetColumns(int c) {
  columns_ = c;
}

int TileSet::GetFirstGid() const {
  return first_gid_;
}

void TileSet::SetFirstGid(int f) {
  first_gid_ = f;
}

std::string TileSet::GetName() const {
  return name_;
}

void TileSet::SetName(std::string n) {
  name_ = n;
}

TileSetType TileSet::GetType() const {
  return type_;
}

void TileSet::SetType(TileSetType t) {
  type_ = t;
}

std::string TileSet::GetImage() const {
  return image_;
}

void TileSet::SetImage(std::string i) {
  image_ = i;
}

int TileSet::GetImageWidth() const {
  return image_width_;
}

void TileSet::SetImageWidth(int w) {
  image_width_ = w;
}

int TileSet::GetImageHeight() const {
  return image_height_;
}

void TileSet::SetImageHeight(int h) {
  image_height_ = h;
}

int TileSet::GetTileCount() const {
  return tile_count_;
}

void TileSet::SetTileCount(int c) {
  tile_count_ = c;
}

int TileSet::GetTileHeight() const {
  return tile_height_;
}

void TileSet::SetTileHeight(int h) {
  tile_height_ = h;
}

int TileSet::GetTileWidth() const {
  return tile_width_;
}

void TileSet::SetTileWidth(int w) {
  tile_width_ = w;
}

int TileSet::GetSpacing() const {
  return spacing_;
}

void TileSet::SetSpacing(int s) {
  spacing_ = s;
}

int TileSet::GetMargin() const {
  return margin_;
}

void TileSet::SetMargin(int m) {
  margin_ = m;
}
}  // namespace tmxjson
