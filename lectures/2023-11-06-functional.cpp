#include <functional>
#include <iostream>
#include <string>
#include <vector>

class Vec {
  std::vector<int> mData;

public:
  size_t count() const {
    return mData.size();
  }

  void each(std::function<void(int)> f) const {
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      f(*itr);
      ++itr;
    }
  }

  Vec filter(std::function<bool(int)> f) {
    Vec result;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      if(f(*itr)) {
        result.push(*itr);
      }
      ++itr;
    }

    return result;
  }

  Vec flat_map(std::function<Vec(int x)> f) {
    Vec result;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      f(*itr).each([&](int x) {
        result.push(x);
      });

      ++itr;
    }

    return result;
  }

  Vec map(std::function<int(int)> f) {
    Vec result;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      result.push(f(*itr));
      ++itr;
    }

    return result;
  }

  void print() const {
    for(int x: mData) {
      std::cout << x << ' ';
    }

    std::cout << '\n';
  }

  void push(int x) {
    mData.push_back(x);
  }

  int pop() {
    int x = mData.back();
    mData.pop_back();
    return x;
  }

  int reduce(int start, std::function<int(int, int)> f) {
    int  acc = start;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      acc = f(acc, *itr);
      ++itr;
    }

    return acc;
  }
};

void printint(int x) {
  std::cout << x << '\n';
}

int main() {
  Vec vec;
  vec.push(1);
  vec.push(2);
  vec.push(3);
  vec.push(4);
  vec.push(5);
  vec.push(6);
  vec.push(7);
  vec.push(8);
  vec.push(9);
  vec.print();

  auto f = [](int x) {
    std::cout << '~' << x << "~\n";
  };

  f(108);

  vec.each([](int x) {
    std::cout << x << '\n';
  });

  vec = vec.filter([](int x) {
    return (x & 1) == 1;
  });

  vec.print();

  Vec squares = vec.map([](int x) {
    return x * x;
  });

  squares.print();

  int sum = squares.reduce(0, [](int acc, int x) {
    return acc + x;
  });

  int product = squares.reduce(1, [](int acc, int x) {
    return acc * x;
  });

  std::cout << "Sum of squares: " << sum << '\n';

  vec.print();
  Vec factors = vec.flat_map([](int x) {
    Vec factors;
    for(int i = 1; i <= x; ++i) {
      if(x % i == 0) {
        factors.push(i);
      }
    }

    return factors;
  });

  factors.print();

  return 0;
}
