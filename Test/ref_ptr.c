#include <stdio.h>
#include <stdlib.h>

void GetMemory(char **p, int num) {
  *p = (char*)malloc(sizeof(char)*num);
}

char* GetMemory1(char* p, int num) {
  return p = (char*)malloc(sizeof(char)*num);
}

const char* str() {
  static char s[] = "hello world";
  return s;
}

const char* str2() {
  const char* s = "hello world";
  return s;
}

int main() {
  printf("%s %s\n", str(), str2());

  return 0;
}
