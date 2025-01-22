#pragma once
#include "../include/parser.hpp"
#include <sstream>

namespace Generation_NS {
class Generation {
public:
  // temp for now
  Generation(const Node::Exit root);

  [[nodiscard]] std::string generate() const;

private:
  const Node::Exit m_root;
};
} // namespace Generation_NS
