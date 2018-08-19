/* MIT License. Copyright 2018 Mark Winter */

#ifndef TEXT_H_
#define TEXT_H_

#include <string>

namespace tmxjson {
class Text {
 public:
  Text();
  Text(const std::string& text, bool wrap);
  Text(std::string&& text, bool wrap);

  std::string GetText() const;
  bool IsWrap() const;

  void SetText(const std::string& text);
  void SetWrap(bool wrap);

 private:
  std::string text_;
  bool wrap_;
};
}  // namespace tmxjson

#endif
