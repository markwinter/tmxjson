/* MIT License. Copyright 2018 Mark Winter */

#ifndef LAYER_H_
#define LAYER_H_

#include "Object.hpp"
#include "Property.hpp"
#include "Tile.hpp"

namespace tmxjson {

enum class LayerType { kTileLayer, kObjectGroup, kImageLayer, kGroup };
enum class DrawOrder { kTopDown, kIndex };

class Layer {
 public:
  Layer();

  int GetHeight() const;
  int GetWidth() const;
  float GetX() const;
  float GetY() const;
  float GetOffsetX() const;
  float GetOffsetY() const;
  void SetHeight(int);
  void SetWidth(int);
  void SetX(float);
  void SetY(float);
  void SetOffsetX(float);
  void SetOffsetY(float);

  const std::vector<Tile>& GetData() const;
  const std::vector<Layer>& GetLayers() const;
  const std::vector<Object>& GetObjects() const;
  std::string GetImage() const;
  void SetData(std::vector<Tile>);
  void SetLayers(std::vector<Layer>);
  void SetObjects(std::vector<Object>);
  void SetImage(std::string);

  LayerType GetType() const;
  DrawOrder GetDrawOrder() const;
  void SetType(LayerType);
  void SetType(std::string);
  void SetDrawOrder(DrawOrder);

  std::string GetName() const;
  float GetOpacity() const;
  bool IsVisible() const;
  void SetName(std::string);
  void SetOpacity(float);
  void SetVisible(bool);

  std::vector<std::shared_ptr<Property>>& GetProperties();

 private:
  int height_;
  int width_;
  float x_;
  float y_;
  float offset_x_;
  float offset_y_;

  std::vector<Tile> data_;
  std::vector<Layer> layers_;
  std::vector<Object> objects_;
  std::string image_;
  std::vector<std::shared_ptr<Property>> properties_;

  LayerType type_;
  DrawOrder draw_order_;

  std::string name_;
  float opacity_;
  bool visible_;
};
}  // namespace tmxjson

#endif
