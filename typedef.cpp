#include <iostream>
#include <memory>
#include <stdint.h>

struct Interface {
  virtual void print() = 0;
};

typedef std::tr1::shared_ptr<Interface> isptr;

// error: can not typedef template without a type
// typedef std::tr1::shared_ptr shared_ptr

// warning
// class Impl : public isptr {

class Impl : public Interface {
    typedef int32_t value_type;
    value_type mem;
  public:
    typedef int32_t* pointer;
    Impl(const pointer ptr) : mem(*ptr) {} 
    
    // not recommend, because value_type doesn't be seen
    // in out of this class, although auto could be use 
    // when C++11 supported
    value_type getMem() const { return mem; }

    virtual void print() {
      std::cout << "Impl" << mem << std::endl;
    }
};

typedef std::tr1::shared_ptr<Impl> ImplSptr;
typedef double matrix2[2][2];

void test(matrix2& mat, matrix2* mat2) {
  mat[0][0] = 1.0e-03;
  (*mat2)[1][1] = 3.0e-03;
}

// 2 dimentional array reference and pointer
void test2(double (&mat)[2][2], double (*mat2)[2][2],
           double (*mat3)[2], double mat4[][2]) {
  mat[1][0] = 2.0e-03;
  (*mat2)[0][1] = 4.0e-03;
  mat3[0][1] += 4.0e-02;
  mat4[1][0] += 2.0e-02;
}

int main(int argc, char** argv) {

  matrix2 mat = {{1,0}, {0,1}};
  test(mat, &mat);
  test2(mat, &mat, mat, mat);
  std::cout << mat[0][0] << ", " << mat[0][1] << std::endl
            << mat[1][0] << ", " << mat[1][1] << std::endl;

  int32_t a = 0x7fffffff;
  isptr sp(new Impl(&a));
  sp->print();

  ImplSptr imp(new Impl(&a));
  // Impl::value_type var = imp->getMem();
  auto var = imp->getMem();
  std::cout << var << std::endl;

  return 0;
}
