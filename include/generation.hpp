#pragma once
#include "../include/parser.hpp"
#include <sstream>

namespace Generation_NS {
class Generation {
public:
  // temp for now
  Generation(const Node::Prog root);

  [[nodiscard]] std::string gen_stmt() const;
  [[nodiscard]] std::string gen_prog() const;

private:
  const Node::Prog m_program;
};
} // namespace Generation_NS
