#pragma once
#include "tokenizer.hpp"
#include <optional>
#include <string>
#include <variant>
#include <vector>

// Tree Nodes
namespace Node {
// Expression Int Litteral
struct ExprIntLit {
  Token int_lit;
};

// Expression Identifier
struct ExprIdent {
  Token ident;
};

// Expression
struct Expression {
  std::variant<Node::ExprIntLit, Node::ExprIdent> variant;
};

// Statment Exit
struct StmtExit {
  Node::Expression expr;
};

// Statement let
struct StmtLet {
  Token ident;
  Node::Expression expr;
};

// Statment
struct Stmt {
  std::variant<Node::StmtExit, StmtLet> variant;
};

// Program
struct Prog {
  std::vector<Node::Stmt> stmts;
};
} // namespace Node

namespace Parser_NS {
class Parser {
public:
  Parser(const std::vector<Token> &tokens);

  std::optional<Node::Expression> parse_expr();
  std::optional<Node::Stmt> parse_stmt();
  std::optional<Node::Prog> parse_prog();

private:
  [[nodiscard]] std::optional<Token> peek(int offset = 0) const;
  Token consume();

  size_t m_index = 0;
  const std::vector<Token> m_tokens;
};
} // namespace Parser_NS
