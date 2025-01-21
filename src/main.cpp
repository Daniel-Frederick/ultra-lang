#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/tokenizer.hpp"

// Lexical Analysis
std::string tokens_to_asm(const std::vector<Token> &tokens) {
  std::stringstream output;
  output << "global _start\n_start:\n";

  for (size_t i = 0; i < tokens.size(); ++i) {
    const Token &token = tokens.at(i);

    // Handle `exit` token
    if (token.type == TokenType::exit) {
      // Check if next tokens exist and match the pattern: int_lit -> semi
      if (i + 1 < tokens.size() &&
          tokens.at(i + 1).type == TokenType::int_lit) {
        if (i + 2 < tokens.size() && tokens.at(i + 2).type == TokenType::semi) {
          // Generate assembly for exit
          output << "    mov rax, 60\n"; // syscall number for exit
          output << "    mov rdi, " << tokens.at(i + 1).value.value()
                 << "\n"; // exit code
          output << "    syscall\n";
          i += 2; // Skip the processed tokens
        } else {
          throw std::runtime_error(
              "Error: Missing semicolon after `exit` statement.");
        }
      } else {
        throw std::runtime_error(
            "Error: Missing integer literal after `exit` statement.");
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
  Tokenizer_NS::Tokenizer tokenizer(std::move(contents));
  std::vector<Token> tokens = tokenizer.tokenize();

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
