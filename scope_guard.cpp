#include "scope_guard.h"
#include "memchk.h"

#define SCOPE_ALLOC_ARRAY(ptr, type, n)  \
    type* ptr = new type[n];        \
    SCOPE_GUARD( [&]{delete[] ptr;} );


#define SCOPE_ALLOC(ptr, type) \
    type* ptr = new type;   \
    SCOPE_GUARD( [&]{delete ptr;} );


void testScopeGuard() {
  SCOPE_ALLOC_ARRAY(pChar1, char, 2);
  SCOPE_ALLOC(pInt1, int);

  char* pChar = new char;
  SCOPE_GUARD( [&]{delete pChar;} );

  int* pInt = new int[2];
  //SCOPE_GUARD( [&]{delete[] pInt;} );
}

int main() {
  MEM_CHK_START_DBG
  testScopeGuard();
  return 0;
}
