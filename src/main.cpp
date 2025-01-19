#include <fstream>
#include <iostream>

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

  std::cout << contents;
  return EXIT_SUCCESS;
}
