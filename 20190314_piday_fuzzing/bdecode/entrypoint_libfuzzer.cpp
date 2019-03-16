#include "bdecode.hpp"

// entry point for libFuzzer
extern "C" int
LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size)
{
  libtorrent::bdecode_node e;
  libtorrent::error_code ec;
  auto b = reinterpret_cast<const char*>(Data);
  int ret = libtorrent::bdecode(b, b + Size, e, ec);

  return 0;
}
