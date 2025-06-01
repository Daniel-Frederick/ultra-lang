#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "../include/generation.hpp"
#include "../include/parser.hpp"
#include "../include/tokenizer.hpp"

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

  Parser_NS::Parser parser(std::move(tokens));
  std::optional<Node::Prog> program = parser.parse_prog();

  if (!program.has_value()) {
    std::cerr << "Invalid Program" << std::endl;
    exit(EXIT_FAILURE);
  }

  // convert Tokens to assembly
  Generation_NS::Generation generation(program.value());
  {
    std::fstream file("out.asm", std::ios::out);
    if (!file) {
      std::cerr << "Error: unable to create .asm file" << std::endl;
      return EXIT_FAILURE;
    }
    file << generation.gen_prog();
  }

  // assemble the file and create executable
  system("nasm -felf64 out.asm");
  system("ld -o out out.o");

  return EXIT_SUCCESS;
}
