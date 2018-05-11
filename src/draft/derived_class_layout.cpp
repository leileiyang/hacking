#include <iostream>

class Base1 {
 public:
  Base1() {
    number_base1_ = 1;
  }
  int number_base1_;

};

class Base2 {
 public:
  Base2() {
    number_base2_ = 1;
  }
  int number_base2_;

};

class Derived: public Base1, public Base2 {
 public:
  Derived() {
    number_d_ = 1;
  }
  int number_d_;

};

int main() {
  Derived d;
  Base1 *b1 = &d;
  Base2 *b2 = &d;

  std::cout << "d: " << &d << ", b1: " << b1 << ", b2: " << b2 << ", d.number_d_: " << &(d.number_d_) << std::endl;
  return 0;
}
