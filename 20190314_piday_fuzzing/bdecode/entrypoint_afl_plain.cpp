#include "bdecode.hpp"
#include <array>
#include <cassert>
#include <fstream>

int
main(int argc, char* argv[])
{

  assert(argc >= 2);
  std::ifstream ifs(argv[1]);
  assert(ifs);

  /* Read input data. */
  std::array<char, 8192> buf;
  buf.fill('\0');
  // auto nbytes=read(0,buf.data(),buf.size());

  ifs.read(buf.data(), buf.size());
  auto nbytes = ifs.gcount();

  /* Call library code to be fuzzed. */
  libtorrent::bdecode_node e;
  libtorrent::error_code ec;
  int ret = libtorrent::bdecode(buf.begin(), buf.begin() + nbytes, e, ec);
}
