/* MIT License. Copyright Mark Winter */

#include "thirdparty/miniz.hpp"
#include "Utils.hpp"
#include <iostream>
#include <string>

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
  stream.next_in = (Byte*)(source);             // Next byte to read from
  stream.avail_in = static_cast<unsigned int>(inSize);          // How many bytes available at next_in
  stream.next_out = (Byte*)(byte_array.data());  // Next byte to write to
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

  if (inflateEnd(&stream) != Z_OK)
    return false;

  dest.insert(dest.begin(), byte_array.begin(), byte_array.end());

  return true;
}
}  // namespace tmxjson
