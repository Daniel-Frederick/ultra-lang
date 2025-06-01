#include "../include/parser.hpp"
#include <cstdlib>
#include <optional>

namespace Parser_NS {
Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens) {}

std::optional<Node::Expression> Parser::parse_expr() {
  if (peek().has_value() && peek().value().type == TokenType::int_lit) {
    // If Expression is a number
    return Node::Expression{Node::ExprIntLit{consume()}};
  } else if (peek().has_value() && peek().value().type == TokenType::ident) {
    // If Expression is a variable identifier
    return Node::Expression{Node::ExprIdent{consume()}};
  } else {
    // If there is a syntax error
    return std::nullopt;
  }
}

std::optional<Node::Stmt> Parser::parse_stmt() {
  auto token = peek().value();

  if (token.type == TokenType::exit &&
      peek(1).value().type == TokenType::open_param) {
    consume(); // Remove the "exit" token
    consume(); // Remove the '(' token
    Node::StmtExit stmt_exit;
    if (auto node_expr = parse_expr()) {
      stmt_exit = Node::StmtExit{node_expr.value()};
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
    return Node::Stmt{stmt_exit};
  } else if (peek().has_value() && peek().value().type == TokenType::let &&
             peek(1).has_value() && peek(1).value().type == TokenType::ident &&
             peek(2).has_value() && peek(2).value().type == TokenType::equals) {
    consume(); // Remove "let" token
    auto stmt_let = Node::StmtLet{consume()};
    consume(); // Remove '=' token
    if (auto expr = parse_expr()) {
      stmt_let.expr = expr.value();
    } else {
      std::cerr << "Invalid Expression" << std::endl;
      exit(EXIT_FAILURE);
    }
    if (peek().has_value() && peek().value().type == TokenType::semi) {
      consume();
    } else {
      std::cerr << "Expected ';'" << std::endl;
      exit(EXIT_FAILURE);
    }
    return Node::Stmt{stmt_let};
  } else {
    std::cerr << "Expected 'exit' or '('" << std::endl;
    exit(EXIT_FAILURE);
  }
}

std::optional<Node::Prog> Parser::parse_prog() {
  Node::Prog prog;
  while (peek().has_value()) {
    if (auto stmt = parse_stmt()) {
      prog.stmts.push_back(stmt.value());
    } else {
      std::cerr << "Invalid Statment" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
}

[[nodiscard]] std::optional<Token> Parser::peek(int offset) const {
  if (m_index + offset >= m_tokens.size())
    return std::nullopt;
  return m_tokens.at(m_index + offset);
}

Token Parser::consume() { return m_tokens.at(m_index++); }

} // namespace Parser_NS
