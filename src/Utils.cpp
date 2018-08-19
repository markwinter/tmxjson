/* MIT License. Copyright Mark Winter */

#include <iostream>
#include <string>
#include <memory>

#include "thirdparty/miniz.hpp"
#include "Utils.hpp"
#include "TypedProperty.hpp"

// Bits on the far end of the 32-bit global tile ID are used for tile flags
const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

namespace tmxjson {
bool check_json_var(const json& j, std::string&& key) {
  try {
    j.at(key);
    return true;
  } catch (json::out_of_range& e) {
    return false;
  }

  return false;
}

bool zlib_inflate(const char* source, std::size_t inSize, std::vector<unsigned char>& dest, std::size_t expectedSize) {
  int current_size = static_cast<int>(expectedSize);

  std::vector<unsigned char> byte_array(expectedSize / sizeof(unsigned char));

  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  stream.next_in = (Byte*)(source);                             // Next byte to read from
  stream.avail_in = static_cast<unsigned int>(inSize);          // How many bytes available at next_in
  stream.next_out = (Byte*)(byte_array.data());                 // Next byte to write to
  stream.avail_out = static_cast<unsigned int>(expectedSize);   // How many bytes available at next_out

  if (inflateInit(&stream) != Z_OK)
    return false;

  int result = Z_OK;
  while (result != Z_STREAM_END) {
      result = inflate(&stream, Z_SYNC_FLUSH);

      // Handle the potential errors
      switch (result) {
        case Z_NEED_DICT:
        case Z_ERRNO:
        case Z_STREAM_ERROR:
        case Z_DATA_ERROR:
        case Z_MEM_ERROR:
        case Z_BUF_ERROR:
        case Z_VERSION_ERROR:
          inflateEnd(&stream);  // Call inflateEnd so all structures are free'd
          return false;
      }

      if (result != Z_STREAM_END && !stream.avail_out) {
          // Run out of space, so lets increase our space and continue
          int old_size = current_size;
          current_size *= 2;

          std::vector<unsigned char> new_data(current_size / sizeof(unsigned char));
          std::memcpy(new_data.data(), byte_array.data(), old_size);
          byte_array = std::move(new_data);

          stream.next_out = (Byte*)(byte_array.data() + old_size);
          stream.avail_out = old_size;
      }
  }

  // Calculate how much data we actually got
  const int out_size = current_size - stream.avail_out;

  if (inflateEnd(&stream) != Z_OK)
    return false;

  std::vector<unsigned char> new_array(out_size / sizeof(unsigned char));
  std::memcpy(new_array.data(), byte_array.data(), out_size);
  byte_array = std::move(new_array);

  dest.insert(dest.begin(), byte_array.begin(), byte_array.end());

  return true;
}

void parse_properties(std::vector<std::shared_ptr<Property>>& properties, const json& j) {
  for (auto itr = j.begin(); itr != j.end(); ++itr) {
    if (itr.value().type() == json::value_t::boolean)
      properties.push_back(std::make_shared<TypedProperty<bool>>(itr.key(), itr.value(), PropertyType::kBool));
    else if (itr.value().type() == json::value_t::number_integer || itr.value().type() == json::value_t::number_unsigned)
      properties.push_back(std::make_shared<TypedProperty<int>>(itr.key(), itr.value(), PropertyType::kInt));
    else if (itr.value().type() == json::value_t::number_float)
      properties.push_back(std::make_shared<TypedProperty<float>>(itr.key(), itr.value(), PropertyType::kFloat));
    else
      properties.push_back(std::make_shared<TypedProperty<std::string>>(itr.key(), itr.value(), PropertyType::kString));
  }
}

std::vector<Tile> parse_tile_data(const std::vector<unsigned char>& data) {
  std::vector<Tile> tiles;
  for (auto i = 0u; i < data.size() - 3u; i += 4u) {
    uint32_t id = data[i] |
                  data[i + 1] << 8 |
                  data[i + 2] << 16 |
                  data[i + 3] << 24;

    bool flipped_horizontally = (id & FLIPPED_HORIZONTALLY_FLAG);
    bool flipped_vertically = (id & FLIPPED_VERTICALLY_FLAG);
    bool flipped_diagonally = (id & FLIPPED_DIAGONALLY_FLAG);

    id &= ~(FLIPPED_HORIZONTALLY_FLAG |
                    FLIPPED_VERTICALLY_FLAG |
                    FLIPPED_DIAGONALLY_FLAG);

    tiles.emplace_back(id, flipped_horizontally, flipped_vertically, flipped_diagonally);
  }
  return tiles;
}
}  // namespace tmxjson
