#pragma once
#include "tokenizer.hpp"
#include <optional>
#include <string>
#include <vector>

// Tree Node
namespace Node {
struct Expression {
  Token int_lit;
};

struct Exit {
  Node::Expression expr;
};
} // namespace Node

namespace Parser_NS {
class Parser {
public:
  Parser(const std::vector<Token> &tokens);

  std::optional<Node::Expression> parse_expr();
  std::optional<Node::Exit> parse();

private:
  [[nodiscard]] std::optional<Token> peak(int ahead = 1) const;
  Token consume();

  size_t m_index = 0;
  const std::vector<Token> m_tokens;
};
} // namespace Parser_NS
