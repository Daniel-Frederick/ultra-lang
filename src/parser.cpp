#include "../include/parser.hpp"

namespace Parser_NS {
Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens) {}

std::optional<Node::Expression> Parser::parse_expr() {
  if (peak().has_value() && peak().value().type == TokenType::int_lit) {
    return Node::Expression{.int_lit = consume()};
  } else {
    return std::nullopt;
  }
}

std::optional<Node::Exit> Parser::parse() {
  std::optional<Node::Exit> exit_node;
  while (peak().has_value()) {
    if (peak().value().type == TokenType::exit) {
      consume();
      if (auto node_expr = parse_expr()) {
        exit_node = Node::Exit{.expr = node_expr.value()};
      } else {
        std::cerr << "Invalid expression" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (!peak().has_value() || peak().value().type != TokenType::semi) {
        std::cerr << "Invalid expression" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
  m_index = 0;
  return exit_node;
}

[[nodiscard]] std::optional<Token> Parser::peak(int ahead) const {
  if (m_index + ahead >= m_tokens.size())
    return std::nullopt;
  return m_tokens.at(m_index + ahead);
}

Token Parser::consume() { return m_tokens.at(m_index++); }

} // namespace Parser_NS
