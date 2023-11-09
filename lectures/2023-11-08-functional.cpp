#include <functional>
#include <iostream>
#include <string>
#include <vector>

template <class T>
class Vec {
  std::vector<T> mData;

public:
  size_t count() const {
    return mData.size();
  }

  void each(std::function<void(const T&)> f) const {
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      f(*itr);
      ++itr;
    }
  }

  Vec filter(std::function<bool(const T&)> f) {
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

  template <class R>
  Vec<R> flat_map(std::function<Vec<R>(const T& x)> f) {
    Vec<R> result;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      f(*itr).each([&](const R& x) {
        result.push(x);
      });

      ++itr;
    }

    return result;
  }

  template <class R>
  Vec<R> map(std::function<R(const T&)> f) {
    Vec<R> result;
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      result.push(f(*itr));
      ++itr;
    }

    return result;
  }

  void print() const {
    for(const T& x: mData) {
      std::cout << x << ' ';
    }

    std::cout << '\n';
  }

  void push(const T& x) {
    mData.push_back(x);
  }

  T pop() {
    T x = mData.back();
    mData.pop_back();
    return x;
  }

  template <class R>
  R reduce(R accum, std::function<R(const R&, const T&)> f) {
    auto itr = mData.cbegin();
    while(itr != mData.cend()) {
      accum = f(accum, *itr);
      ++itr;
    }

    return accum;
  }
};

void printint(int x) {
  std::cout << x << '\n';
}

int main() {
  Vec<int> vec;
  vec.push(1);
  vec.push(22);
  vec.push(303);
  vec.push(4004);
  vec.push(50005);
  vec.print();

  vec.each([](const int& i) {
    std::cout << i << '\n';
  });

  auto strs = vec.map<std::string>([](const int& i) {
    return std::to_string(i);
  });
  strs.each([](const std::string& s) {
    std::cout << ('"' + s + '"') << '\n';
  });

  auto odds = vec.filter([](const int& i) {
    return (i & 1) == 1;
  });

  odds.print();

  size_t total_len = strs.map<size_t>([](const std::string& s) {
    return s.size();
  }).reduce<size_t>(0, [](const size_t& acc, const size_t& s) {
    return acc + s;
  });

  std::cout << "Total len: " << total_len << '\n';

  auto chars = strs.flat_map<char>([](const std::string& s) {
    Vec<char> cs;
    for(char c: s) {
      cs.push(c);
    }
    return cs;
  });

  chars.print();

  return 0;
}
