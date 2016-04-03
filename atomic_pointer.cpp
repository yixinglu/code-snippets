#include "memchk.h"
#include <iostream>


using namespace std;

template<typename T>
class AtomicPointer
{
public:
    typedef T* value_type;
    AtomicPointer() : pointer(0) {}
    AtomicPointer(value_type p) : pointer(p) {}

    inline operator value_type() const {
        return pointer;
    }

    inline value_type operator->() const {
        return pointer;
    }

    value_type pointer;
};

struct Interface {
    virtual int getter() const = 0;
};

struct Impl : public Interface {
    virtual int getter() const {
        return 0x7FFFFFFF;
    }
};

class Test {
public:
    Test() : m_pInterface() {}
    Test(Interface* p) : m_pInterface(p) {}
    inline void test() const {
        if (m_pInterface) {
            cout << m_pInterface << endl;
        } else {
            cout << "NULL" << endl;
        }
        cout << m_pInterface->getter() << endl;
    }

private:
    AtomicPointer<Interface> m_pInterface;
};


int main(int argc, char** argv)
{
    Interface* impl = new Impl;
    Test t(impl);
    t.test();
    delete impl;

    cout << sizeof(impl) << endl;
    _STATIC_ASSERT(sizeof(impl) == sizeof(int));

    return 0;
}
