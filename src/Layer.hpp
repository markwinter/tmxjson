/* MIT License. Copyright 2018 Mark Winter */

#ifndef LAYER_H_
#define LAYER_H_

#include "Object.hpp"

namespace tmxjson {

enum class LayerType { kTileLayer, kObjectGroup, kImageLayer, kGroup };
enum class DrawOrder { kTopDown, kIndex };

class Layer {
 public:
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

  std::vector<uint32_t>& GetData();
  std::vector<Layer>& GetLayers();
  std::vector<Object>& GetObjects();
  std::string GetImage() const;
  void SetData(std::vector<uint32_t>);
  void SetLayers(std::vector<Layer>);
  void SetObjects(std::vector<Object>);
  void SetImage(std::string);

  LayerType GetType() const;
  DrawOrder GetDrawOrder() const;
  void SetType(LayerType);
  void SetDrawOrder(DrawOrder);

  std::string GetName() const;
  float GetOpacity() const;
  bool IsVisible() const;
  void SetName(std::string);
  void SetOpacity(float);
  void SetVisible(bool);

 private:
  int height_;
  int width_;
  float x_;
  float y_;
  float offset_x_;
  float offset_y_;

  std::vector<uint32_t> data_;
  std::vector<Layer> layers_;
  std::vector<Object> objects_;
  std::string image_;

  LayerType type_;
  DrawOrder draw_order_;

  std::string name_;
  float opacity_;
  bool visible_;
};
}  // namespace tmxjson

#endif
