//
// g++ -std=c++11 specification.cc  -g -ggdb
//

#include <iostream>
#include <memory>
#include <vector>
#include <functional>

using std::vector;

template <typename T>
struct Specification;
template <typename Ty>
using spec_ptr = std::shared_ptr<Specification<Ty>>;

template <typename T>
struct Specification {
  virtual bool IsSatisfiedBy(T candidate) const = 0;
  virtual spec_ptr<T> And(spec_ptr<T> other) = 0;
  virtual spec_ptr<T> Or(spec_ptr<T> other) = 0;
  virtual spec_ptr<T> Not() = 0;
};

template <typename T>
struct AndSpecification;
template <typename T>
struct OrSpecification;
template <typename T>
struct NotSpecification;

template <typename T>
struct CompositSpecification : Specification<T> {
  spec_ptr<T> And(spec_ptr<T> other) override {
    return std::make_shared<AndSpecification<T>>(*this, *other);
  }
  spec_ptr<T> Or(spec_ptr<T> other) override {
    return std::make_shared<OrSpecification<T>>(*this, *other);
  }
  spec_ptr<T> Not() override {
    return std::make_shared<NotSpecification<T>>(*this);
  }
};

template <typename T>
struct AndSpecification : CompositSpecification<T> {
  const Specification<T> &one;
  const Specification<T> &other;
  AndSpecification(const Specification<T> &one, const Specification<T> &other) : one(one), other(other) {}
  bool IsSatisfiedBy(T candidate) const override {
    return one.IsSatisfiedBy(candidate) && other.IsSatisfiedBy(candidate);
  }
};

template <typename T>
struct OrSpecification : CompositSpecification<T> {
  const Specification<T> &one;
  const Specification<T> &other;
  OrSpecification(const Specification<T> &one, const Specification<T> &other) : one(one), other(other) {}
  bool IsSatisfiedBy(T candidate) const override {
    return one.IsSatisfiedBy(candidate) || other.IsSatisfiedBy(candidate);
  }
};

template <typename T>
struct NotSpecification : CompositSpecification<T> {
  const Specification<T> &one;
  NotSpecification(const Specification<T> &one) : one(one) {}
  bool IsSatisfiedBy(T candidate) const override {
    return !one.IsSatisfiedBy(candidate);
  }
};

struct OddSpecification : CompositSpecification<int> {
  bool IsSatisfiedBy(int candidate) const override {
    return candidate % 2 == 1;
  }
};

struct PositiveSpecification : CompositSpecification<int> {
  bool IsSatisfiedBy(int candidate) const override {
    return candidate > 0;
  }
};

//---------------------------------------------------------

template <typename T>
struct ISpec {
  virtual bool IsSatisfiedBy(T candidate) const = 0;
};

template <typename T>
using spec_ptr2 = std::shared_ptr<ISpec<T>>;
template <typename T>
using is_satisfied_by_t = std::function<bool(T)>;

template <typename T>
struct Spec : ISpec<T> {
  is_satisfied_by_t<T> is_satisfied_by;
  Spec(is_satisfied_by_t<T> is_satisfied_by) : is_satisfied_by(is_satisfied_by) {}
  bool IsSatisfiedBy(T candidate) const override {
    return is_satisfied_by(candidate);
  }
};

template <typename T>
spec_ptr2<T> operator &&(spec_ptr2<T> one, spec_ptr2<T> other) {
  return std::make_shared<Spec<T>>([=](T candidate) {
      return one->IsSatisfiedBy(candidate) && other->IsSatisfiedBy(candidate);
    });
}

template <typename T>
spec_ptr2<T> operator ||(spec_ptr2<T> one, spec_ptr2<T> other) {
  return std::make_shared<Spec<T>>([=](T candidate) {
      return one->IsSatisfiedBy(candidate) || other->IsSatisfiedBy(candidate);
    });
}

template <typename T>
spec_ptr2<T> operator !(spec_ptr2<T> one) {
  return std::make_shared<Spec<T>>([=](T candidate) {
      return !one->IsSatisfiedBy(candidate);
    });
}

//---------------------------------------------------------

template <typename T>
is_satisfied_by_t<T> operator &&(is_satisfied_by_t<T> one, is_satisfied_by_t<T> other) {
  return [=](T candidate) { return one(candidate) && other(candidate); };
}

template <typename T>
is_satisfied_by_t<T> operator ||(is_satisfied_by_t<T> one, is_satisfied_by_t<T> other) {
  return [=](T candidate) { return one(candidate) || other(candidate); };
}

template <typename T>
is_satisfied_by_t<T> operator !(is_satisfied_by_t<T> one) {
  return [=](T candidate) { return !one(candidate); };
}
//---------------------------------------------------------


template <typename T>
void print(const vector<int> &int_arr, T spec) {
  for(auto i : int_arr) {
    if (spec->IsSatisfiedBy(i)) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

void print(const vector<int> &int_arr, is_satisfied_by_t<int> spec) {
  for(auto i : int_arr) {
    if (spec(i)) {
      std::cout << i << " ";
    }
  }
  std::cout << std::endl;
}

int main() {
  vector<int> int_arr{-2, -1, 0, 1, 2, 3, 4, 5, 6};

  spec_ptr<int> spec = std::make_shared<OddSpecification>();
  spec_ptr<int> positive_spec = std::make_shared<PositiveSpecification>();
  auto odd_and_positive_spec = spec->And(positive_spec);
  auto odd_or_positive_spec = spec->Or(positive_spec);
  auto even_spec = spec->Not();

  print<spec_ptr<int>>(int_arr, odd_and_positive_spec);
  print<spec_ptr<int>>(int_arr, odd_or_positive_spec);
  print<spec_ptr<int>>(int_arr, even_spec);

  std::cout << "------------------" << std::endl;

  spec_ptr2<int> spec2 = std::make_shared<Spec<int>>([](int candidate) { return candidate % 2 == 1; });
  spec_ptr2<int> positive_spec2 = std::make_shared<Spec<int>>([](int candidate) { return candidate > 0; });
  auto odd_and_positive_spec2 = spec2 && positive_spec2;
  auto odd_or_positive_spec2 = spec2 || positive_spec2;
  auto even_spec2 = !spec2;

  print<spec_ptr2<int>>(int_arr, odd_and_positive_spec2);
  print<spec_ptr2<int>>(int_arr, odd_or_positive_spec2);
  print<spec_ptr2<int>>(int_arr, even_spec2);

  std::cout << "------------------" << std::endl;

  is_satisfied_by_t<int> odd_spec3 = [](int i) { return i % 2 == 1; };
  is_satisfied_by_t<int> positive_spec3= [](int i) { return i > 0; };
  auto odd_and_positive_spec3 = odd_spec3 && positive_spec3;
  auto odd_or_positive_spec3 = odd_spec3 || positive_spec3;
  auto even_spec3 = !odd_spec3;

  print(int_arr, odd_and_positive_spec3);
  print(int_arr, odd_or_positive_spec3);
  print(int_arr, even_spec3);

  return 0;
}
