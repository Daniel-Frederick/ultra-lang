#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType { exit, int_lit, semi };

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

namespace Tokenizer_NS {
class Tokenizer {
public:
  Tokenizer(const std::string &src);

  std::vector<Token> tokenize();

private:
  [[nodiscard]] std::optional<char> peek(int ahead = 1) const;
  char consume();

  size_t m_index = 0;
  const std::string m_src;
};
} // namespace Tokenizer_NS
