#include "../include/generation.hpp"

namespace Generation_NS {
// TODO: add references with std::move(root)
Generation::Generation(const Node::Prog root) : m_program(root) {}

void gen_expr(const Node::Expression &expr) const {
  struct ExprVisitor {
    Generator *gen;

    void operator()(const Node::ExprIntLit &expr_int_lit) {
      gen->m_output << "move rax, " << expr_int_lit.int_lit.value.value()
                    << "\n";
      gen->m_output << "push rax\n";
    }
    void operator()(const Node::ExprIdent &expr_ident) {}
  };

  ExprVisitor visitor{.gen = this};
  std::visit(visitor, expr.variant);
}

void Generation::gen_stmt(const Node::Stmt &stmt) const {
  struct StmtVisitor {
    Generator *gen;

    void operator()(const Node::StmtExit &stmt_exit) const {
      gen->gen_expr(stmt_exit.expr);
      gen->m_output << "    mov rax, 60\n"; // syscall number for exit
      gen->m_output << "    pop rdi\n";
      gen->m_output << "    syscall\n";
    }

    void operator()(const Node::StmtLet &stmt_let) {}
  };

  StmtVisitor visitor{.gen = this};
  std::visit(visitor, stmt.variant);
}

// TODO: Make assembly for variables
std::string Generation::gen_prog() const {
  std::stringstream output;
  output << "global _start\n_start:\n";

  for (const Node::Stmt &stmts : m_program.stmts) {
    output << gen_stmt(stmts);
  }

  // If there is no return specfied, default `return 0;`
  output << "    mov rax, 60\n"; // syscall number for exit
  output << "    mov rdi, 0\n";
  output << "    syscall\n";
  return output.str();
}
} // namespace Generation_NS
