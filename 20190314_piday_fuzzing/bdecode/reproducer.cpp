#include "bdecode.hpp"
#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

// return data in a vector to make out of bound reads more likely to be detected
std::vector<char>
slurpFile(const char* filename)
{
  std::ifstream ifs(filename);
  assert(ifs);

  /* Read input data. */
  std::array<char, 8192> buf;
  ifs.read(buf.data(), buf.size());
  const auto nbytes = ifs.gcount();
  return { buf.data(), buf.data() + nbytes };
}

int
main(int argc, char* argv[])
{

  for (int i = 1; i < argc; ++i) {
    auto buf = slurpFile(argv[i]);
    //buf.reserve(buf.size()+10);
    libtorrent::bdecode_node e;
    libtorrent::error_code ec;
    const int ret =
      libtorrent::bdecode(buf.data(), buf.data() + buf.size(), e, ec);

    std::cout << "Got " << ret << " from parsing the " << buf.size()
              << "-byte file " << argv[i] << '\n';
  }
}
