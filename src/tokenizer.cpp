#include "../include/tokenizer.hpp"
#include <cstdlib>
#include <iostream>

namespace Tokenizer_NS {
Tokenizer::Tokenizer(const std::string &src) : m_src(src) {}

std::vector<Token> Tokenizer::tokenize() {
  std::vector<Token> tokens;
  std::string buf;
  size_t length = m_src.length();

  for (size_t i = 0; i < length; ++i) {
    char c = m_src[i];

    // Handle identifiers
    if (std::isalpha(c)) {
      buf.push_back(c);
      while (i + 1 < length && std::isalnum(m_src[i + 1])) {
        buf.push_back(m_src[++i]);
      }

      if (buf == "exit") {
        tokens.push_back({TokenType::exit});
      } else {
        std::cerr << "Misspelled keyword: " << buf << std::endl;
        exit(EXIT_FAILURE);
      }
      buf.clear();
    }
    // Handle integer literals
    else if (std::isdigit(c)) {
      buf.push_back(c);
      while (i + 1 < length && std::isdigit(m_src[i + 1])) {
        buf.push_back(m_src[++i]);
      }

      tokens.push_back({TokenType::int_lit, buf});
      buf.clear();
    }
    // Handle semicolon
    else if (c == ';') {
      tokens.push_back({TokenType::semi});
    }
    // Skip whitespace
    else if (std::isspace(c)) {
      continue;
    }
    // Handle unexpected characters
    else {
      std::cerr << "Syntax Error: Unexpected character '" << c
                << "' at position " << i << std::endl;
      exit(EXIT_FAILURE);
    }
  }

  return tokens;
}
} // namespace Tokenizer_NS
