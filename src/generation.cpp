#include "../include/generation.hpp"

namespace Generation_NS {
// TODO: add references with std::move(root)
Generation::Generation(const Node::Prog root) : m_program(root) {}

std::string Generation::gen_stmt(const Node::Stmt& stmt) const {

}

// TODO: Make assembly for variables
std::string Generation::gen_prog() const {
  std::stringstream output;
  output << "global _start\n_start:\n";

  for (const Node::Stmt& stmts: m_program.stmts) {
    output << gen_stmt(stmts);
  }

  // If there is no return specfied, default `return 0;`
  output << "    mov rax, 60\n"; // syscall number for exit
  output << "    mov rdi, 0\n";
  output << "    syscall\n";
  return output.str();
}
} // namespace Generation_NS
