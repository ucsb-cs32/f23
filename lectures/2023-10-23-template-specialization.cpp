#include <iostream>
#include <string>

// float square(float v) {
//   return v * v;
// }

template<class T>
T square(T value) {
  return value * value;
}

template<>
float square<float>(float value) {
  std::cout << "Squaring " << value << "...\n";
  return value * value;
}


template<size_t N, class T>
struct Vector {
  T data[N];
};

template<class T>
struct Vector<3, T> {
  union {
    T data[3];
    struct {
      T x;
      T y;
      T z;
    };
  };
};

// struct Thing1 {
//   int   x;
//   float y;
//   bool  z;
// };

// union Thing2 {
//   int   x;
//   float y;
//   bool  z;
// };

template<size_t N, class T>
std::ostream& operator << (
  std::ostream& stream,
  const Vector<N, T>& vector
) {
  stream << '<';
  for(size_t i = 0; i < N; ++i) {
    if(i > 0) stream << ", ";
    stream << vector.data[i];
  }

  return stream << '>';
}

int main() {
  // int    i = 4;
  // float  f = 42.5;
  // double d = 108.5;

  // std::cout << "i^2 = " << square(i) << '\n';
  // std::cout << "f^2 = " << square(f) << '\n';
  // std::cout << "d^2 = " << square(d) << '\n';


  Vector<4, int> v{.data = {2, 3, 5, 7}};
  Vector<3, int> u{.data = {10, 11, 12}};
  std::cout << v << '\n';
  std::cout << u << '\n';
  std::cout << u.x << ' ' << u.y << ' ' << u.z << '\n';
  return 0;
}
