#include "../include/parser.hpp"
#include <cstdlib>

namespace Parser_NS {
Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens) {}

std::optional<Node::Expression> Parser::parse_expr() {
  if (peek().has_value() && peek().value().type == TokenType::int_lit) {
    return Node::Expression{.int_lit = consume()};
  } else {
    return std::nullopt;
  }
}

std::optional<Node::Exit> Parser::parse() {
  std::optional<Node::Exit> exit_node;

  while (peek().has_value()) {
    auto token = peek().value();

    if (token.type == TokenType::exit &&
        peek(1).value().type == TokenType::open_param) {
      consume(); // Remove the "exit" token
      consume(); // Remove the '(' token
      if (auto node_expr = parse_expr()) {
        exit_node = Node::Exit{.expr = node_expr.value()};
      } else {
        std::cerr << "Invalid expression" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (peek().has_value() && peek().value().type == TokenType::close_param) {
        consume();
      } else {
        std::cerr << "No Closing Parameter! Expected ')'" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (peek().has_value() && peek().value().type == TokenType::semi) {
        consume();
      } else {
        std::cerr << "No Semicolon! Expected ';'" << std::endl;
        exit(EXIT_FAILURE);
      }
    } else {
      // consume(); Are you sure about this?
      std::cerr << "Expected 'exit' or '('" << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  m_index = 0;
  return exit_node;
}

[[nodiscard]] std::optional<Token> Parser::peek(int offset) const {
  if (m_index + offset >= m_tokens.size())
    return std::nullopt;
  return m_tokens.at(m_index + offset);
}

Token Parser::consume() { return m_tokens.at(m_index++); }

} // namespace Parser_NS
