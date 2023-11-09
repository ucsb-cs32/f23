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

// typedef std::shared_ptr<Thing> ThingPtr;
// using ThingPtr = std::shared_ptr<Thing>;

// std::unique_ptr => Trees
// std::shared_ptr => DAGs
// std::shared_ptr + std::weak_ptr => Directed Graph

void print_thing(const Thing* thing) {
  std::cout << "Thing: " << thing->name() << std::endl;
}


int main() {
  std::shared_ptr<Thing> p1 = std::make_shared<Thing>("Alice");
  std::shared_ptr<Thing> p2 = p1;

  std::cout << "Alice's ref count: " << p2.use_count() << std::endl;

  p1 = nullptr;

  std::cout << "Alice's ref count: " << p2.use_count() << std::endl;

  print_thing(p2.get());

  std::weak_ptr<Thing> w1 = p2;
  std::weak_ptr<Thing> w2 = w1;

  // p2 = nullptr;

  std::shared_ptr<Thing> l1 = w2.lock();
  if(l1 != nullptr) {
    std::cout <<"w1/l1: " << l1->name() << std::endl;
  }
  else {
    std::cout << "w1 was alread cleaned up.\n";
  }

  Thing* thing2 = new Thing("Bob");
  std::shared_ptr<Thing> p3(thing2);
  // std::shared_ptr<Thing> p4(thing2);
  std::shared_ptr<Thing> p4 = p3;

  std::cout << "Bob's ref count: " << p3.use_count() << std::endl;

  std::cout << "Leaving main()..." << std::endl;
  return 0;
}
