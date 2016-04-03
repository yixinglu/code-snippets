
#ifndef SCOPE_GUARD_H_
#define SCOPE_GUARD_H_

#include <functional>

class ScopeGuard {
public:
    ScopeGuard(const std::tr1::function<void ()>& f)
        : rel(f), isCancel(true) {}

    ~ScopeGuard() {
        if (isCancel) {
            rel();
        }
    }

    void cancel() { isCancel = false; }

private:
    std::tr1::function<void()> rel;
    bool isCancel;
};

#define SCOPE_GUARD_NAME_CAT(x, y) x ## y
#define SCOPE_GUARD_NAME(x, y) SCOPE_GUARD_NAME_CAT(x, y)
#define SCOPE_GUARD(guard) ScopeGuard SCOPE_GUARD_NAME(sg,__LINE__)(guard)


#endif
