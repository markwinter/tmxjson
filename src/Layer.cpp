/* MIT License. Copyright 2018 Mark Winter */

#include "Layer.hpp"

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

float Layer::GetX() const {
  return x_;
}

void Layer::SetX(float x) {
  x_ = x;
}

float Layer::GetY() const {
  return y_;
}

void Layer::SetY(float y) {
  y_ = y;
}

float Layer::GetOffsetX() const {
  return offset_x_;
}

void Layer::SetOffsetX(float x) {
  offset_x_ = x;
}

float Layer::GetOffsetY() const {
  return offset_y_;
}

void Layer::SetOffsetY(float y) {
  offset_y_ = y;
}

std::vector<uint32_t>& Layer::GetData() {
  return data_;
}

void Layer::SetData(std::vector<uint32_t> d) {
  data_ = d;
}

std::vector<Layer>& Layer::GetLayers() {
  return layers_;
}

void Layer::SetLayers(std::vector<Layer> l) {
  layers_ = l;
}

std::vector<Object>& Layer::GetObjects() {
  return objects_;
}

void Layer::SetObjects(std::vector<Object> objects) {
  objects_ = objects;
}

std::string Layer::GetImage() const {
  return image_;
}

void Layer::SetImage(std::string image) {
  image_ = image;
}

LayerType Layer::GetType() const {
  return type_;
}

void Layer::SetType(LayerType t) {
  type_ = t;
}

DrawOrder Layer::GetDrawOrder() const {
  return draw_order_;
}

void Layer::SetDrawOrder(DrawOrder order) {
  draw_order_ = order;
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
