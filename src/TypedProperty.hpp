/* MIT License. Copyright Mark Winter */

#ifndef TYPED_PROPERTY_H_
#define TYPED_PROPERTY_H_

#include "Property.hpp"

namespace tmxjson {

template<typename T>
class TypedProperty : public Property {
 public:
  TypedProperty(const std::string& name, const T& value, PropertyType type) : Property(name, type), value_(value) {}

  T GetValue() const { return value_; }

 private:
  T value_;
};
}  // namespace tmxjson

#endif
