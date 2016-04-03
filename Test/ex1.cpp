#include <stdio.h>
#include <math.h>
#include <iostream>
#include <conio.h>

// cann't use judgement statement to get max value of 2 integer
inline int max_value(int a, int b) {
 return ((a+b)+abs(a-b)) >> 1; //((a+b)+abs(a-b))/2
}

// cann't use temp var to swap 2 integer
// no overflow
inline void swap_i(int& a, int& b) {
  a = a^b;
  b = a^b;
  a = a^b;
}

// (x+y)/2
inline int avg(int x, int y) {
  return (x&y)+((x^y)>>1);
}

void t1() {
  unsigned char a = 0xA5;
  unsigned char b = ~a>>4+1;
  printf("b=%d\n", b);
  // 0000 0000 1010 0101 => 1111 1111 0101 1010 =>
  // 0000 0111 1111 1010 == 250
}

void t2() {
  unsigned int a = 0xFFFFFFF7;
  unsigned char i = (unsigned char)a;
  char* b = (char*)&a;
  printf("%08x, %08x\n", i, *b);
}

int i = 1;
void t3() {
  int i = i;
  printf("%d\n", i);
}

int get1bits(int x) {
  int count = 0;
  while(x) {
    count++;
    x &= (x-1);
  }
  return count;
}

void t4() {
  int arr[] = {6,7,8,9,10};
  int* ptr = arr;
  *(ptr++) += 123;
  printf("%d, %d\n", *ptr, *(++ptr)); // printf parameters from right to left are pushed to stack.
}

using namespace std;

void t5() {
  float a = 1.0f;
  cout << (int)a << " " << &a << " " << (int&)a << " "
   << boolalpha << ((int)a == (int&)a) << endl;
  float b = 0.0f;
  cout << (int)b << " " << &b << " " << (int&)b << " "
   << boolalpha << ((int)b == (int&)b) << endl;
}

int main() {
  printf("%d\n", max_value(10, 9));

  int a = 1, b = 2;
  swap_i(a, b);
  printf("a=%d, b=%d\n", a, b);

  printf("%d\n", avg(5, 3));

  t1(); t2(); t3(); t4(); t5();

  printf("%08x, %d\n", 9999, get1bits(9999));
  return 0;
}
