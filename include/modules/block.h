#pragma once
#include <iostream>
#include <vector>

namespace block {
struct Block {
  bool enable;
  std::vector<std::string> domains;
};
} // namespace block
