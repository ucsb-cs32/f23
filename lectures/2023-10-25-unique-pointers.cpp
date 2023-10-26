#include <iostream>
#include <memory>
#include <string>

class Thing {
  std::string mName;

public:
  Thing(const std::string& name): mName(name) {
    std::cout << "Creating Thing(" << mName << ")..." << std::endl;
  }

  // Example copy constructor (unused)
  Thing(const Thing& other): mName(other.mName) {
    std::cout << "Copy Constructor" << std::endl;
  }

  // Example move constructor (unused)
  Thing(Thing&& other): mName(std::move(other.mName)) {
    std::cout << "Move Constructor" << std::endl;
  }

  ~Thing() {
    std::cout << "Deleting Thing(" << mName << ")..." << std::endl;
  }

  const std::string& name() const {
    return mName;
  }
};

void print_thing(const Thing* thing) {
  std::cout << "Thing: " << thing->name() << std::endl;
}

int main() {
  std::cout << "Entering main()..." << std::endl;
  Thing* zero = new Thing("Zero");

  // Pass a pointer to the unique_ptr constructor
  // The unique_ptr takes control of that object
  // It will get deleted automatically when the unique_ptr is destroyed
  // ...or when the unique_ptr is pointed at a different object
  std::unique_ptr<Thing> p0(zero);
  std::cout << "p0: " << p0->name() << std::endl;

  std::unique_ptr<Thing> p1(new Thing("One"));
  std::cout << "p1: " << p1->name() << std::endl;

  // Use reset() to put a new object under the control of a unique_ptr
  // This deletes the object the unique_ptr was previously pointing to
  p0.reset(nullptr);
  std::cout << "0:  " << zero->name() << std::endl;

  // Use release() to take control over the internal pointer
  // This does NOT delete the object that was released
  // This sets the unique_ptr to nullptr
  Thing* one = p1.release();
  std::cout << "1:  " << one->name() << std::endl;

  // You can also create unique_ptrs with std::make_unique()
  // The arguments to make_unique() are passed to the object's constructor
  std::unique_ptr<Thing> p2 = std::make_unique<Thing>("Two");
  std::cout << "p2: " << p2->name() << std::endl;

  // Use get() to get a regular pointer to the managed object
  // Unlike release(), this leaves the object under the unique_ptr's control
  Thing* two = p2.get();
  std::cout << "2:  " << two->name() << std::endl;

  // You can point a unique_ptr at a new object with assignment
  // But you may need to use std::move() to ensure you use move assignment
  p0 = std::move(p2);
  std::cout << "p2: " << p2 << std::endl;
  std::cout << "p0: " << p0->name() << std::endl;

  // Use get if you need to pass a uniqure_ptr as a regular pointer
  // Just don't store this regular pointer anywhere!
  print_thing(p0.get());

  // All objects pointed to by unique_ptrs are deleted
  // when the unique_ptrs go out of scope
  std::cout << "Leaving main()..." << std::endl;
  return 0;
}
