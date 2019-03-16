#include "bdecode.hpp"

#include <array>
#include <iostream>

// entry point for afl fast
int
main(int, char* argv[])
{

  while (__AFL_LOOP(1000)) {
    std::array<char, 8192> buf;
    buf.fill('\0');
    /* Read input data. */
    // auto nbytes=read(0,buf.data(),buf.size());
    std::cin.read(buf.data(), buf.size());
    auto nbytes = std::cin.gcount();

    /* Call library code to be fuzzed. */
    libtorrent::bdecode_node e;
    libtorrent::error_code ec;
    int ret = libtorrent::bdecode(buf.begin(), buf.begin() + nbytes, e, ec);

    /* Reset state. */
  }
}
