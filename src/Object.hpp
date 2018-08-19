/* MIT License. Copyright 2018 Mark Winter */

#ifndef OBJECT_H_
#define OBJECT_H_

#include <vector>
#include <utility>
#include <string>

#include "Property.hpp"
#include "Text.hpp"

namespace tmxjson {

enum class ObjectType { kRectangle, kPoint, kEllipse, kPolygon, kPolyline, kText };

class Object {
 public:
  Object();

  int GetId() const;
  int GetGid() const;
  std::string GetName() const;
  std::string GetType() const;
  Text GetTextObject() const;
  void SetTextObject(const Text&);
  void SetTextObject(const std::string& text, bool wrap);
  void SetId(int);
  void SetGid(int);
  void SetName(std::string);
  void SetType(std::string);

  ObjectType GetObjectType() const;
  const std::vector<std::pair<float, float>>& GetDataPoints();
  void SetObjectType(ObjectType);
  void SetDataPoints(std::vector<std::pair<float, float>>);

  float GetRotation() const;
  bool IsVisible() const;
  int GetX() const;
  int GetY() const;
  int GetHeight() const;
  int GetWidth() const;
  void SetRotation(float);
  void SetVisible(bool);
  void SetX(int);
  void SetY(int);
  void SetHeight(int);
  void SetWidth(int);

  std::vector<std::shared_ptr<Property>>& GetProperties();

 private:
  int id_;
  int gid_;
  std::string name_;
  std::string type_;
  Text text_;

  ObjectType object_type_;
  std::vector<std::pair<float, float>> data_points_;
  std::vector<std::shared_ptr<Property>> properties_;

  float rotation_;
  bool visible_;
  int x_;
  int y_;
  int height_;
  int width_;
};
}  // namespace tmxjson

#endif
