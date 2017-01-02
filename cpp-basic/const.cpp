#include <iostream>
#include <complex>

typedef std::complex<double> complex;

void print(complex* p, complex const* pc,
           complex* const cp, complex const* const cpc)
{
  *p = 0;
  ++p;

  //*pc = 0;
  ++pc;

  *cp = 0;
  //++cp;

  //*cpc = 0;
  //++cpc;
}

int main(int argc, char* argv[]) {
  complex c(1.0, 1.0);

  complex* pc = &c;
  const complex* pcc = pc;
  complex const* pcc2 = pc;

  complex* const cp = pc;
  // cp = pcc;
  complex const * const cpc = pc;

  return 0;
}
