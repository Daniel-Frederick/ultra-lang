#include "../include/generation.hpp"

namespace Generation_NS {
// TODO: add references with std::move(root)
Generation::Generation(const Node::Prog root) : m_program(root) {}

// TODO: Make assembly for variables
[[nodiscard]] std::string Generation::generate() const {
  std::stringstream output;
  output << "global _start\n_start:\n";
  output << "    mov rax, 60\n"; // syscall number for exit
  output << "    mov rdi, " << m_program.expr.int_lit.value.value()
         << "\n"; // exit code
  output << "    syscall\n";
  return output.str();
}
} // namespace Generation_NS
