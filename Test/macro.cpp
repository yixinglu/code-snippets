#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define FIND(struc, e) (size_t)&(((struc*)0)->e)

struct student {
  int a;
  char b[20];
  double ccc;
};

void t1() {
 printf("0x%08x\n", FIND(student, a)); 
 printf("0x%08x\n", FIND(student, b)); 
 printf("0x%08x\n", FIND(student, ccc)); 
 printf("%d\n", FIND(student, ccc)-FIND(student, b));
}

#define SECONDS_PER_YEAR (60*60*24*365)/*UL*/
#define literal_num 0UL

void t2() {
  const uint64_t sec = SECONDS_PER_YEAR;
  const uint32_t ui = literal_num;
}

#define MIN(A,B) ((A) <= (B) ? (A) : (B))

void t3() {
  printf("%d\n", MIN(10, 65));
}

int main()
{
  t1();
  t2();
  t3();
  return 0;
}
