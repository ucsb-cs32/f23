#include <iostream>
#include <string>

struct A {
  void f1() {std::cout << "A::f1()\n";}
  virtual void f2() {std::cout << "A::f2()\n";}

  void a() {std::cout << "A things!\n";}
};

struct B: public A {
  void f1() {std::cout << "B::f1()\n";}
  void f2() {std::cout << "B::f2()\n";}

  void b() {std::cout << "B things!\n";}

private:
  void secret() {std::cout << "S3CR3TS\n";}

public:
  void b_secret() {secret();}
};

struct C: public B {
  void f1() {std::cout << "C::f1()\n";}
  void f2() {std::cout << "C::f2()\n";}

  void c() {std::cout << "C things!\n";}

public:
  void c_secret() {secret();}
};

void call_f1_on_A(A& object) {
  object.f1();
}

void call_f2_on_A(A& object) {
  object.f2();
}

void call_f2_on_B(B& object) {
  object.f2();
}

void call_f2_on_Bptr(B* object) {
  object->f2();
}


int main() {
  A a;
  B b;
  C c;

  std::cout << "Direct call:\n";
  a.f1();
  b.f1();
  c.f1();

  std::cout << "Call f1() as A&:\n";
  call_f1_on_A(a);
  call_f1_on_A(b);
  call_f1_on_A(c);

  std::cout << "Call f2() as A&:\n";
  call_f2_on_A(a);
  call_f2_on_A(b);
  call_f2_on_A(c);

  std::cout << "Call f2() as B&:\n";
  // call_f2_on_B(a);
  call_f2_on_B(b);
  call_f2_on_B(c);

  std::cout << "Call f2() as B*:\n";
  // call_f2_on_Bptr(&a);
  call_f2_on_Bptr(&b);
  call_f2_on_Bptr(&c);

  b.b_secret();
  c.c_secret();

  return 0;
}
