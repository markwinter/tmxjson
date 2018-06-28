# tmxjson

tmxjson is a library for reading json formatted maps exported from the [Tiled Map Editor](http://www.mapeditor.org/).

### Using Tiled and tmxjson
- Available formats: `CSV` `Base64 (Uncompressed)` `Base64 (zlib compressed)`
- You must also embed your tilesets into the map.
- Export your map as json to be used by this library (File > Export As)

### How to use this library
You can either include the source in your project, or you can build it and link against it.

Then you will want to use an instance of the Map class to load and render your map.

```
#include <Map.hpp>

tmxjson::Map map("mymap.json");
auto layers = map.GetLayers();
auto tile_sets = map.GetTileSets();

for (auto layer : layers) {
  if (layer.GetType() == tmxjson::LayerType::kGroup) {
    for (auto layer : layer.GetLayers()) {
      std::vector<uint32_t> tiles = layer.GetData();
      ...
    }
  } else if (layer.GetType () tmxjson::LayerType::kObjectGroup) {
    for (auto object : layer.GetObjects()) {
      ...
    }
  }
  ...
}
```

### Currently Not Supported
- Objects: `text`
- Custom Properties
- Tilesets: `tileoffset`, `grid`, `terrains`
- Tile-flipping

### Current work
- Finish implementing tmx spec

### Todo
- Add "Tile" class which will have methods to simplify rendering
- Add method to only get tiles matching the rendering view size
- Improve performance e.g. move vectors instead of copying twice
- Add tests
- Add documentation (doxygen)
