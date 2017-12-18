//dafdgahfasdfkasjfa
/* dalgaad*/ // iafsdfasdfakajglsd
//    alksf jakdfajsf       jdakf
/**********\\\\/////*////

/*
 * print hello world
 */

#include <iostream>
#include <stdio.h>

int main(int argc, char** argv) {
  // print 2 line blank
  std::cout << "hello world\n" << std::endl;
  printf("\'%d", 2);
  std::cout << "\\" << "\"" << '/' << "//" << "/**/" << std::endl; // comment
  std::cout << "'" << '"';
  std::cout << '\n' << "/*" << "***/";

  /**
   * computation / * a pointer * /
   * computation /"//" * a pointer * /
   */
  std::cout << "\"" << "\\\"";
  std::cout << "#include <iostream>\n"
      "using namespace std;\n"
      "int main(int argc, char**argv) {\n"
      "\tcout << \"hello world\n\";// first program\n"
      "\treturn 0;"
      "}";
  int a = 1;
  const int* p = &a;
  int b = 2 / *p;

  return 0;
}
