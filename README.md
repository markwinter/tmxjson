# tmxjson

tmxjson is a library for reading json formatted maps from the [Tiled tool](http://www.mapeditor.org/).

### Using Tiled and tmxjson
Make sure your `Tile Layer Format` is set to `CSV`. You must also embed your tilesets into the map. Then you can export
your map as json to be used by this library (File > Export As)

### How to use this library
You can either include this source in your project, or you can build it and link against it.

### Currently Not Supported
- Base64 and/or compressed layer data. For now your `tile layer format` must be `CSV`
- Objects
- Custom Properties
- Tilesets: `tileoffset`, `grid`, `terrains`
