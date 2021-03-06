# tmxjson

tmxjson is a library for reading json formatted maps exported from the [Tiled Map Editor](http://www.mapeditor.org/).

Supported Tiled version: 1.1

### Using Tiled and tmxjson
- Available formats: `CSV` `Base64 (Uncompressed)` `Base64 (zlib compressed)`
- You must also embed your tilesets into the map.
- Export your map as json to be used by this library (File > Export As)

### How to use this library
You can either include the source in your project, or you can build it and link against it.

Then you will want to use an instance of the Map class to load and render your map.

```CPP
#include <Map.hpp>

tmxjson::Map map("mymap.json");
auto layers = map.GetLayers();
auto tile_sets = map.GetTileSets();

for (const auto& layer : layers)
  ParseLayer(layer);

void ParseLayer(tmxjson::Layer& layer) {
  if (layer.GetType() == tmxjson::LayerType::kGroup) {
    // Groups contain more embedded layers
    for (const auto& child_layer : layer.GetLayers())
      ParseLayer(child_layer);
  } else if (layer.GetType() == tmxjson::LayerType::kTileLayer) {
    for (const auto& tile : layer.GetData()) {
      ... // Render your tiles
    }
  } else if (layer.GetType() == tmxjson::LayerType::kObjectGroup) {
    for (const auto& object : layer.GetObjects()) {
      ... // Render your objects
    }
  } else if (layer.GetType() == tmxjson::LayerType::kImageLayer) {
    ... // Render your image
  }
}
```

### Working with custom properties

You must cast to `tmxjson::TypedProperty<TYPE>` in order to use the method `GetValue()`

```CPP
for (auto property : map.GetProperties()) {
  if (property->GetType() == tmxjson::PropertyType::kString)
    std::cout << "Property (" << property->GetName() << "): " <<
      dynamic_cast<tmxjson::TypedProperty<std::string>*>(property.get())->GetValue() << std::endl;
}
```

### Currently Not Supported
- Tilesets: `terrains`, `tiles`
- Wang sets

### Current work
- Finish implementing tmx 1.1 spec
