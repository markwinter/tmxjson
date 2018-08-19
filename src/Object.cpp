/* Copyright 2018 Mark Winter */

#include "Object.hpp"

namespace tmxjson {
Object::Object() : gid_(0) {}

int Object::GetId() const {
  return id_;
}

void Object::SetId(int id) {
  id_ = id;
}

int Object::GetGid() const {
  return gid_;
}

void Object::SetGid(int gid) {
  gid_ = gid;
}

std::string Object::GetName() const {
  return name_;
}

void Object::SetName(std::string name) {
  name_ = name;
}

std::string Object::GetType() const {
  return type_;
}

void Object::SetType(std::string type) {
  type_ = type;
}

ObjectType Object::GetObjectType() const {
  return object_type_;
}

void Object::SetObjectType(ObjectType type) {
  object_type_ = type;
}

const std::vector<std::pair<float, float>>& Object::GetDataPoints() {
  return data_points_;
}

void Object::SetDataPoints(std::vector<std::pair<float, float>> data) {
  data_points_ = data;
}

float Object::GetRotation() const {
  return rotation_;
}

void Object::SetRotation(float rotation) {
  rotation_ = rotation;
}

bool Object::IsVisible() const {
  return visible_;
}

void Object::SetVisible(bool visible) {
  visible_ = visible;
}

int Object::GetX() const {
  return x_;
}

void Object::SetX(int x) {
  x_ = x;
}

int Object::GetY() const {
  return y_;
}

void Object::SetY(int y) {
  y_ = y;
}

int Object::GetHeight() const {
  return height_;
}

void Object::SetHeight(int height) {
  height_ = height;
}

int Object::GetWidth() const {
  return width_;
}

void Object::SetWidth(int width) {
  width_ = width;
}

void Object::SetTextObject(const Text& text) {
  text_ = text;
}

void Object::SetTextObject(const std::string& text, bool wrap) {
  text_ = Text(text, wrap);
}

Text Object::GetTextObject() const {
  return text_;
}
}  // namespace tmxjson
