/* MIT License. Copyright Mark Winter */

#ifndef TILE_H_
#define TILE_H_

namespace tmxjson {
class Tile {
 public:
  Tile() : gid_(0), horizontal_(false), vertical_(false), diagonal_(false) {}
  Tile(uint32_t gid, bool h, bool v, bool d) : gid_(gid), horizontal_(h), vertical_(v), diagonal_(d) {}

  uint32_t GetGid() const { return gid_; }
  bool IsHorizontal() const { return horizontal_; }
  bool IsVertical() const { return vertical_; }
  bool IsDiagonal() const { return diagonal_; }

 private:
  uint32_t gid_;
  bool horizontal_;
  bool vertical_;
  bool diagonal_;
};
}  // namespace tmxjson

#endif
