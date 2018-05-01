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
  int currentSize = static_cast<int>(expectedSize);
  std::vector<unsigned char> byteArray(expectedSize / sizeof(unsigned char));
  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree = Z_NULL;
  stream.opaque = Z_NULL;
  stream.next_in = (Bytef*)source;
  stream.avail_in = static_cast<unsigned int>(inSize);
  stream.next_out = (Bytef*)byteArray.data();
  stream.avail_out = static_cast<unsigned int>(expectedSize);

  inflateInit(&stream);
  int result = 0;
  do
  {
      result = inflate(&stream, Z_SYNC_FLUSH);

      switch (result)
      {
      case Z_NEED_DICT:
      case Z_STREAM_ERROR:
          result = Z_DATA_ERROR;
      case Z_DATA_ERROR:
      case Z_MEM_ERROR:
          inflateEnd(&stream);
          return false;
      }

      if (result != Z_STREAM_END)
      {
          int oldSize = currentSize;
          currentSize *= 2;
          std::vector<unsigned char> newArray(currentSize / sizeof(unsigned char));
          std::memcpy(newArray.data(), byteArray.data(), currentSize / 2);
          byteArray = std::move(newArray);

          stream.next_out = (Bytef*)(byteArray.data() + oldSize);
          stream.avail_out = oldSize;

      }
  } while (result != Z_STREAM_END);

  if (stream.avail_in != 0)
  {
      return false;
  }

  const int outSize = currentSize - stream.avail_out;
  inflateEnd(&stream);

  std::vector<unsigned char> newArray(outSize / sizeof(unsigned char));
  std::memcpy(newArray.data(), byteArray.data(), outSize);
  byteArray = std::move(newArray);

  //copy bytes to vector
  dest.insert(dest.begin(), byteArray.begin(), byteArray.end());

  return true;
}
}  // namespace tmxjson
