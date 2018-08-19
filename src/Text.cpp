#include "Text.hpp"

namespace tmxjson {
Text::Text() : text_(""), wrap_(false) {}

Text::Text(const std::string& text, bool wrap) : text_(text), wrap_(wrap) {}

Text::Text(std::string&& text, bool wrap) : text_(std::move(text)), wrap_(wrap) {}

std::string Text::GetText() const {
  return text_;
}

bool Text::IsWrap() const {
  return wrap_;
}

void Text::SetText(const std::string& text) {
  text_ = text;
}

void Text::SetWrap(bool wrap) {
  wrap_ = wrap;
}
}  // namespace tmxjson
