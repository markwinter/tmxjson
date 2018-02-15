/* MIT License. Copyright 2018 Mark Winter */

#include <string>
#include <iostream>
#include "Map.hpp"

int main() {
  std::string file = "test.json";
  tmxjson::Map map(file);

  for (auto layer : map.GetLayers())
    std::cout << "Layer name: " << layer.GetName() << '\n';

  for (auto tileset : map.GetTileSets())
    std::cout << "Tileset name: " << tileset.GetName() << '\n';

  return 0;
}
