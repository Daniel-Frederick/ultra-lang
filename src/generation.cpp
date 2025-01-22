#include "../include/generation.hpp"

namespace Generation_NS {
Generation::Generation(const Node::Exit root) : m_root(root) {}

[[nodiscard]] std::string Generation::generate() const {
  std::stringstream output;
  output << "global _start\n_start:\n";
  output << "    mov rax, 60\n"; // syscall number for exit
  output << "    mov rdi, " << m_root.expr.int_lit.value.value()
         << "\n"; // exit code
  output << "    syscall\n";
  return output.str();
}
} // namespace Generation_NS
