#pragma once
#include "../include/parser.hpp"
#include "parser.hpp"
#include <sstream>

namespace Generation_NS {
class Generation {
public:
  // temp for now
  Generation(const Node::Prog root);

  [[nodiscard]] void gen_expr(const Node::Expression &expr) const;
  [[nodiscard]] void gen_stmt(const Node::Stmt &stmt) const;
  [[nodiscard]] std::string gen_prog() const;

private:
  const Node::Prog m_program;
  const std::stringstream m_output;
};
} // namespace Generation_NS
