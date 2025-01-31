#include "../include/tokenizer.hpp"
#include <cstdlib>

namespace Tokenizer_NS {
Tokenizer::Tokenizer(const std::string &src) : m_src(src) {}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;
  std::string buf;

  while (auto c = peek(0)) {
    if (std::isalpha(*c)) {
      buf.push_back(consume());
      while (auto next = peek(0)) {
        if (!std::isalnum(*next))
          break;
        buf.push_back(consume());
      }

      if (buf == "exit") {
        tokens.push_back({TokenType::exit});
      } else {
        tokens.push_back({.type = TokenType::ident, .value = buf});
        buf.clear();
        continue;
      }
      buf.clear();
    } else if (buf == "let") {
      tokens.push_back({.type = TokenType::let});
      buf.clear();
      continue;
    } else if (std::isdigit(*c)) {
      buf.push_back(consume());
      while (auto next = peek(0)) {
        if (!std::isdigit(*next))
          break;
        buf.push_back(consume());
      }
      tokens.push_back({TokenType::int_lit, buf});
      buf.clear();
    } else if (peek().value() == '(') {
      consume();
      tokens.push_back({.type = TokenType::open_param});
    } else if (peek().value() == ')') {
      consume();
      tokens.push_back({.type = TokenType::close_param});
    } else if (*c == '=') {
      consume();
      tokens.push_back({TokenType::equals});
    } else if (*c == ';') {
      consume();
      tokens.push_back({TokenType::semi});
    } else if (std::isspace(*c)) {
      consume();
    } else {
      std::cerr << "Syntax Error: Unexpected character '" << *c
                << "' at position " << m_index << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  return tokens;
}

std::optional<char> Tokenizer::peek(int offset) const {
  if (m_index + offset >= m_src.length())
    return std::nullopt;
  return m_src.at(m_index + offset);
}

char Tokenizer::consume() { return m_src.at(m_index++); }
} // namespace Tokenizer_NS
