#include <iostream>

// Structs and Classes
// Members are laid out sequentially
struct Thing {
  int   x;
  float y;
};

// Memory Layout of Thing
// |-------------------|
// | (4 bytes) int x   |
// |-------------------|
// | (4 bytes) float y |
// |-------------------|

// Example Output
// Thing t;
// std::cout << sizeof(t) << '\n'; // 8
// std::cout << &t        << '\n'; // 0x7000
// std::cout << &t.x      << '\n'; // 0x7000
// std::cout << &t.y      << '\n'; // 0x7040



// Unions
// Members are laid out on top of each other
union Blob {
  int   x;
  float y;
};

// Memory Layout of Blob
// |----------------------------|
// | (4 bytes) int x OR float y |
// |----------------------------|

// Blob b;
// std::cout << sizeof(b) << '\n'; // 4
// std::cout << &b        << '\n'; // 0x8000
// std::cout << &b.x      << '\n'; // 0x8000
// std::cout << &b.y      << '\n'; // 0x8000



// Example of a Tagged Union
// Store a tag to keep track of what's in the union
struct Variant {
  enum TypeTag {
    INT,
    FLOAT,
    DOUBLE
  };

  TypeTag type;
  union {
    int    int_value;
    float  float_value;
    double double_value;
  };

  Variant(int value) {
    type      = INT;
    int_value = value;
  }

  Variant(float value) {
    type        = FLOAT;
    float_value = value;
  }

  Variant(double value) {
    type         = DOUBLE;
    double_value = value;
  }
};

std::ostream& operator << (
  std::ostream& stream,
  const Variant& variant
) {
  if(variant.type == Variant::INT) {
    stream << variant.int_value << 'i';
  }
  else if(variant.type == Variant::FLOAT) {
    stream << variant.float_value << 'f';
  }
  else if(variant.type == Variant::DOUBLE) {
    stream << variant.double_value << 'd';
  }

  return stream;
}

int main() {
  Variant var1(42);
  std::cout << var1 << '\n';           // 42i
  std::cout << var1.int_value << '\n'; // 42

  Variant var2(2.78f);
  std::cout << var2 << '\n';           // 2.78f
  std::cout << var2.int_value << '\n'; // garbage

  Variant var3(3.14159);
  std::cout << var3 << '\n';           // 3.14159d
  std::cout << var3.int_value << '\n'; // garbage

  return 0;
}
