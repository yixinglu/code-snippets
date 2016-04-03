#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>

using namespace std;

struct {
  short a;
  short b;
  short c;
} A;

struct {
  long a;
  short b;
} B;

void t1() {
  cout << sizeof A << " " << sizeof B  << endl;
}

void t2() {
  int a;
  char b;
  int c;
  printf("0x%08x\n", &a);
  printf("0x%08x\n", &b);
  printf("0x%08x\n", &c);
}

#pragma pack(1)
struct {
  char c;
  int i;
} struc;
#pragma pack()

void t3() {
  cout << sizeof struc << endl;
}

void t4() {
  string strArr1[] = {"Trend", "Micro", "soft"};
  string* pStrArr = new string[2];
  pStrArr[0] = "US";
  pStrArr[1] = "CN";
  for(int i=0; i < sizeof(strArr1)/sizeof(string); i++) {
    cout << strArr1[i];
  }
  for (int j=0; j < sizeof(*pStrArr)*2/sizeof(string); j++) {
    cout << pStrArr[j];
  }
  cout << endl << sizeof(string) << endl;
}

int f() {return 0;}

void t5() {
  cout << boolalpha << (sizeof(unsigned int) == sizeof(int)) << endl;
  typedef short WORD;
  cout << boolalpha << (sizeof(short) == sizeof(WORD)) << endl;
  cout << sizeof(f()) << endl;
}

class Base {
public:
  virtual ~Base() {};
  virtual void foo() = 0;
};

class Drived : public Base {
public:
  virtual void foo() {}
};

void t6() {
  cout << sizeof(Base) << " " << sizeof(Drived) << endl;
}

char var[10];
int t7_(char var[]) {
  return sizeof(var);
}

void t7() {
  cout << t7_(var) << endl;
}

class AA {};
class AA2 {};
class BB : public AA {};
class CC : public virtual BB {};
class DD : public AA, public AA2 {};

void t8() {
  cout << sizeof (AA) << " " << sizeof(BB) << " "
       << sizeof (CC)  << " " << sizeof(DD) << endl;
}


int main() {
  t1();
  t2();
  t3();
  t4();
  t5();
  t6();
  t7();
  t8();

  return 0;
}
