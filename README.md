# tmxjson

tmxjson is a library for reading json formatted maps exported from the [Tiled Map Editor](http://www.mapeditor.org/).

### Using Tiled and tmxjson
Make sure your `Tile Layer Format` is set to `CSV` or `Base64 (uncompressed)`. You must also embed your tilesets into the map. Then you can export
your map as json to be used by this library (File > Export As)

### How to use this library
You can either include this source in your project, or you can build it and link against it.

Then you will want to use an instance of the Map class to load and render your map.

```
#include <Map.hpp>

tmxjson::Map map("mymap.json");
auto layers = map.GetLayers();
auto tile_sets = map.GetTileSets();

for (auto layer : layers) {
  std::vector<uint32_t> tiles = layer.GetData();
  ...
}
```

### Currently Not Supported
- Compressed layer data. For now your `tile layer format` must be `CSV` or `Base64 (uncompressed)`
- Objects: `text`
- Custom Properties
- Tilesets: `tileoffset`, `grid`, `terrains`
- ImageLayer
