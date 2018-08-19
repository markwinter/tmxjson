/* MIT License. Copyright Mark Winter */

#ifndef PROPERTY_H_
#define PROPERTY_H_

namespace tmxjson {

enum class PropertyType { kBool, kString, kFloat, kInt };

class Property {
 public:
  Property() : name_("") {}
  Property(const std::string& name, PropertyType type) : name_(name), type_(type) {}
  virtual ~Property() {}

  std::string GetName() { return name_; }
  PropertyType GetType() { return type_; }

 private:
  std::string name_;
  PropertyType type_;
};
}  // namespace tmxjson

#endif
