#include <stdio.h>
#include <iostream>

using namespace std;

// the bad code for test
class A {
public:
  A() : m_a(1), m_b(2) {}
  void fun() { printf("%d %d\n", m_a, m_b); }
  int m_a, m_b;
};

class B {
public:
  B() : m_c(3) {}
  void fun() { printf("%d\n", m_c); }
  int m_c;
};

void t1() {
  A a;
  B* pb = (B*)(&a);
  pb->fun();
  printf("%08x %08x\n", &a, &(a.m_a));
  // print offset from object beginning address
  printf("%p, %p, %p\n", &A::m_a, &A::m_b, &B::m_c);
}

struct S {
  int i;
  int *p;
};

void t2() {
  S s;
  int *p = &s.i;
  p[0] = 1;
  p[1] = 5;
  cout << p[0] << " " << s.i << endl;
  cout << &p[0] << " " << &s.i << endl;
  cout << p[1] << " " << s.p << " " << endl; 
  cout << &p[1] << " " << &s.p << " " << &s.p[1] << endl;

  cout << "*********" << endl;
  s.p = p;
  cout << p[0] << " " << s.i << endl;
  cout << &p[0] << " " << &s.i << endl;
  cout << p[1] << " " << s.p << " " << endl; 
  cout << &p[1] << " " << &s.p << " " << &s.p[1] << endl;
  s.p[1] = 1;
  cout << s.p << " " << &s.p << endl;
}

void t3() {
  int v[2][10] = {{1,2,3,4,5,6,7,8,9,10}, {11,12,13,14,15,16,17,18,19,20}};
  int(*a)[10] = v;
  cout << **a << endl;
  cout << **(a+1) << endl;
  cout << *(*a+1) << endl;
  cout << *(a[0]+1) <<endl;
  cout << *(a[1]) <<endl;
  cout << (*a)[10] << endl;
}

void t4() {
  int a[] = {1,2,3,4,5};
  int* ptr = (int*)(&a+1);
  printf("%d %d\n", *(a+1), *(ptr-1));
}

void t5() {
 char* a[] = {"hello", "world", "the"};
 char** ptr = a;
 ptr++;
 cout << *ptr << endl;
}

int main() {
  t1();
  t2();
  t3();
  t4();
  t5();
  return 0;
}
