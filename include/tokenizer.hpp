#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType {
  exit,
  int_lit,
  semi,
  open_param,
  close_param,
  ident,
  let,
  equals
};

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
  [[nodiscard]] std::optional<char> peek(int offset = 0) const;
  char consume();

  size_t m_index = 0;
  const std::string m_src;
};
} // namespace Tokenizer_NS
