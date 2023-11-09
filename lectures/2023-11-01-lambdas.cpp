#include <functional>
#include <iostream>
#include <string>

std::function<int(int)> adder(int inc) {
  return [&](int x){
    return x + inc;
  };
}

int main() {
  int y = 13;
  int z = 1000;

  std::function<void(int)> f = [&z, y](int x){
    std::cout << "x+y+z = " << x+y+z << "\n";
  };

  y = 30;
  z = 2000;
  f(7);

  std::function<int(int)> add5 = adder(5);
  std::cout << add5(20) << '\n';
  std::cout << adder(12)(20) << '\n';
  return 0;
}
