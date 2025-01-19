#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class TokenType { _return, int_lit, semi };

struct Token {
  TokenType type;
  std::optional<std::string> value;
};

// Lexical Analysis
std::vector<Token> tokenize(const std::string &str) {
  std::vector<Token> tokens;
  std::string buf;
  size_t length = str.length();

  for (size_t i = 0; i < length; ++i) {
    char c = str[i];

    // Handle identifiers (e.g., "return")
    if (std::isalpha(c)) {
      buf.push_back(c);
      while (i + 1 < length && std::isalnum(str[i + 1])) {
        buf.push_back(str[++i]);
      }

      if (buf == "return") {
        tokens.push_back({TokenType::_return});
      } else {
        std::cerr << "Misspelled keyword: " << buf << std::endl;
        exit(EXIT_FAILURE);
      }
      buf.clear();
    }
    // Handle integer literals
    else if (std::isdigit(c)) {
      buf.push_back(c);
      while (i + 1 < length && std::isdigit(str[i + 1])) {
        buf.push_back(str[++i]);
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

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Incorrect Usage. Should be:" << std::endl;
    std::cerr << "./build/release/ultra ./src/<file_name>.ultra" << std::endl;
    std::cerr << "or" << std::endl;
    std::cerr << "./build/debug/ultra ./src/<file_name>.ultra" << std::endl;
    return EXIT_FAILURE;
  }

  // Get text from test.ultra file
  std::string contents;
  std::fstream input(argv[1], std::ios::in);
  contents.assign((std::istreambuf_iterator<char>(input)),
                  std::istreambuf_iterator<char>());

  // Tokenize Text
  std::cout << contents;
  tokenize(contents);
  return EXIT_SUCCESS;
}
