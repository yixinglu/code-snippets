
 







#include <iostream>
#include <stdio.h>

int main(int argc, char** argv) {
  
  std::cout << "hello world\n" << std::endl;
  printf("\'%d", 2);
  std::cout << "\\" << "\"" << '/' << "//" << "/**/" << std::endl; 
  std::cout << "'" << '"';
  std::cout << '\n' << "/*" << "***/";

  



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

