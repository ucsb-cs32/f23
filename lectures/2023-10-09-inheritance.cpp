#include <iostream>
#include <string>
#include <vector>

struct Animal {
  std::string name;
  int         age;

  virtual ~Animal() {}

  virtual void speak() const {
    std::cout << "PLACEHOLDER";
  }
};

struct Bird: public Animal {
  int wingspan;

  Bird(const std::string& name, int age, int wingspan) {
    this->name = name;
    this->age = age;
    this->wingspan = wingspan;
  }

  void speak() const {
    std::cout << "Sqwak";
  }
};

struct Dog: public Animal {
  int* idnumber;

  Dog(const std::string& name, int age) {
    idnumber = new int(42);
    this->name = name;
    this->age = age;
  }

  ~Dog() {
    delete idnumber;
  }

  // void speak() const {
  //   std::cout << "Woof";
  // }
};


int main() {
  std::vector<Animal*> zoo;

  zoo.push_back(new Bird("Bob",  12, 32));
  zoo.push_back(new Bird("Polly", 4, 35));
  zoo.push_back(new Dog{"Rover",  1});

  for(const Animal* animal: zoo) {
    std::cout << animal->name << " says ";
    animal->speak();
    std::cout << '\n';
    // std::cout << animal->age  << '\n';
    // std::cout << animal->wingspan << '\n';
  }

  for(const Animal* animal: zoo) {
    delete animal;
    // call destructor
    // deallocate memory
  }

  return 0;
}
