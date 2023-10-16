#include <iostream>
#include <string>

template<class T> class List {
  struct Node {
    Node* next;
    T     data;
  };

  Node* mHead;

public:
  List() {
    mHead = nullptr;
  }

  ~List() {
    while(mHead != nullptr) {
      Node* temp = mHead->next;
      delete mHead;
      mHead = temp;
    }
  }

  bool empty() const {
    return mHead == nullptr;
  }

  void push(const T& data) {
    mHead = new Node{mHead, data};
  }

  T pop() {
    if(mHead == nullptr) {
      throw std::underflow_error("List is empty.");
    }

    T temp = mHead->data;
    Node* node = mHead;
    mHead = mHead->next;
    delete node;
    return temp;
  }
};

// template<int N, class T>
// class Block {
//   T mData[N];


// };

// template<class T>
// class Array {
//   T*  mData;
//   int mCount;

// public:
//   Array(int n) {
//     mData = new T[n];
//     // ...
//   }
// }

template<class T> T mean(T x, T y) {
  return (x + y) / 2;
}

int main() {
  // List<int> ints;

  // ints.push(12);
  // ints.push(30);
  // ints.push(45);

  // while(!ints.empty()) {
  //   std::cout << ints.pop() << '\n';
  // }

  // List<std::string> strs;

  // strs.push("apples");
  // strs.push("bananas");
  // strs.push("cherries");

  // while(!strs.empty()) {
  //   std::cout << strs.pop() << '\n';
  // }

  float fx = 12;
  float fy = 17;
  std::cout << mean<float>(fx, fy) << '\n';

  double dx = 3;
  double dy = 42;
  std::cout << mean(dx, dy) << '\n';

  return 0;
}
