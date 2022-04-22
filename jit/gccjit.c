#include <libgccjit.h>
#include <stdio.h>

int main() {
  gcc_jit_context_acquire();
  printf("hello world!\n");
  return 0;
}
