/* MIT License. Copyright 2018 Mark Winter */

#include "json.hpp"
#include "Layer.hpp"

using json = nlohmann::json;

namespace tmxjson {
int Layer::GetHeight() const {
  return height_;
}

void Layer::SetHeight(int h) {
  height_ = h;
}

int Layer::GetWidth() const {
  return width_;
}

void Layer::SetWidth(int w) {
  width_ = w;
}

int Layer::GetX() const {
  return x_;
}

void Layer::SetX(int x) {
  x_ = x;
}

int Layer::GetY() const {
  return y_;
}

void Layer::SetY(int y) {
  y_ = y;
}

std::vector<int>& Layer::GetData() {
  return data_;
}

void Layer::SetData(std::vector<int> d) {
  data_ = d;
}

std::vector<Layer>& Layer::GetLayers() {
  return layers_;
}

void Layer::SetLayers(std::vector<Layer> l) {
  layers_ = l;
}

LayerType Layer::GetType() const {
  return type_;
}

void Layer::SetType(LayerType t) {
  type_ = t;
}

std::string Layer::GetName() const {
  return name_;
}

void Layer::SetName(std::string n) {
  name_ = n;
}

float Layer::GetOpacity() const {
  return opacity_;
}

void Layer::SetOpacity(float o) {
  opacity_ = o;
}

bool Layer::IsVisible() const {
  return visible_;
}

void Layer::SetVisible(bool v) {
  visible_ = v;
}
}  // namespace tmxjson