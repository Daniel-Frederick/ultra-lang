#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
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

std::string tokens_to_asm(const std::vector<Token> &tokens) {
  std::stringstream output;
  output << "global _start\n_start:\n";

  for (size_t i = 0; i < tokens.size(); ++i) {
    const Token &token = tokens.at(i);

    // Handle `_return` token
    if (token.type == TokenType::_return) {
      // Check if next tokens exist and match the pattern: int_lit -> semi
      if (i + 1 < tokens.size() &&
          tokens.at(i + 1).type == TokenType::int_lit) {
        if (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semi) {
          // Generate assembly for return
          output << "    mov rax, 60\n"; // syscall number for exit
          output << "    mov rdi, " << tokens.at(i + 1).value.value()
                 << "\n"; // exit code
          output << "    syscall\n";
          i += 2; // Skip the processed tokens
        } else {
          throw std::runtime_error(
              "Error: Missing semicolon after `return` statement.");
        }
      } else {
        throw std::runtime_error(
            "Error: Missing integer literal after `return` statement.");
      }
    }
  }

  return output.str();
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

  // std::cout << "File input, test.ultra: " << contents << std::endl;

  // Tokenize source Text
  std::vector<Token> tokens = tokenize(contents);

  // std::cout << tokens_to_asm(tokens) << std::endl;

  // convert Tokens to assembly
  {
    std::fstream file("out.asm", std::ios::out);
    if (!file) {
      std::cerr << "Error: unable to create .asm file" << std::endl;
      return EXIT_FAILURE;
    }
    file << tokens_to_asm(tokens);
  }

  // assemble the file and create executable
  system("nasm -felf64 out.asm");
  system("ld -o out out.o");

  return EXIT_SUCCESS;
}
