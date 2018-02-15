/* MIT License. Copyright 2018 Mark Winter */

#ifndef LAYER_H_
#define LAYER_H_

namespace tmxjson {

enum class LayerType { kTileLayer, kObjectGroup, kImageLayer, kGroup };

class Layer {
 public:
  int GetHeight() const;
  int GetWidth() const;
  int GetX() const;
  int GetY() const;
  void SetHeight(int);
  void SetWidth(int);
  void SetX(int);
  void SetY(int);

  std::vector<int>& GetData();
  std::vector<Layer>& GetLayers();
  void SetData(std::vector<int>);
  void SetLayers(std::vector<Layer>);

  LayerType GetType() const;
  void SetType(LayerType);

  std::string GetName() const;
  float GetOpacity() const;
  bool IsVisible() const;
  void SetName(std::string);
  void SetOpacity(float);
  void SetVisible(bool);

 private:
  int height_;
  int width_;
  int x_;
  int y_;

  std::vector<int> data_;
  std::vector<Layer> layers_;

  LayerType type_;

  std::string name_;
  float opacity_;
  bool visible_;
};
}  // namespace tmxjson

#endif
