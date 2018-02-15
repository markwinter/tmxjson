/* MIT License. Copyright 2018 Mark Winter */

#ifndef TILE_SET_H_
#define TILE_SET_H_

#include <string>

namespace tmxjson {

enum class TileSetType { kTileSet };

class TileSet {
 public:
  int GetColumns() const;
  int GetFirstGid() const;
  void SetColumns(int);
  void SetFirstGid(int);

  std::string GetName() const;
  TileSetType GetType() const;
  void SetName(std::string);
  void SetType(TileSetType);

  std::string GetImage() const;
  int GetImageWidth() const;
  int GetImageHeight() const;
  void SetImage(std::string);
  void SetImageWidth(int);
  void SetImageHeight(int);

  int GetTileCount() const;
  int GetTileHeight() const;
  int GetTileWidth() const;
  int GetSpacing() const;
  int GetMargin() const;
  void SetTileCount(int);
  void SetTileHeight(int);
  void SetTileWidth(int);
  void SetSpacing(int);
  void SetMargin(int);

 private:
  int columns_;
  int first_gid_;

  std::string name_;
  TileSetType type_;

  std::string image_;
  int image_width_;
  int image_height_;

  int tile_count_;
  int tile_height_;
  int tile_width_;
  int spacing_;
  int margin_;
};
}  // namespace tmxjson

#endif
