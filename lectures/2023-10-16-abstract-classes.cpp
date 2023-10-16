#include <iostream>
#include <string>

struct Animal {
  virtual void speak() = 0;
};

struct Cat: public Animal {
  void speak() {
    std::cout << "Meow!\n";
  }
};

struct Dog: public Animal {
  void speak() {
    std::cout << "Woof!\n";
  }
};

void speak(Animal& animal) {
  animal.speak();
}

int main() {
  // Animal animal;
  Cat cat;
  Dog dog;

  // speak(animal);
  speak(cat);
  speak(dog);

  return 0;
}