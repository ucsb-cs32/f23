#include <iostream>
#include <mutex>
#include <thread>

struct Account {
  std::mutex mutex;
  int balance;

  Account(int balance) {
    this->balance = balance;
  }
};

void transfer(Account* src, Account* dst, int amount) {
  // {
    std::lock_guard<std::mutex> src_lock(src->mutex);
    src->balance -= amount;
  // }

  // {
    std::lock_guard<std::mutex> dst_lock(dst->mutex);
    dst->balance += amount;
  // }
}

void multi_transfer(Account* src, Account* dst, int amount) {
  for(int i = 0; i < 1000; ++i) {
    transfer(src, dst, amount);
  }
}

int main() {
  Account alice(1000000);
  Account bob(1000000);

  std::cout << "Starting the transfer..." << std::endl;
  std::cout << "Alice's balance: " << alice.balance << std::endl;
  std::cout << "Bob's balance:   " << bob.balance << std::endl;

  std::thread a2b(multi_transfer, &alice, &bob, 15);
  std::thread b2a(multi_transfer, &alice, &bob, -20);

  std::cout << "Transferring..." << std::endl;
  a2b.join();
  b2a.join();

  std::cout << "Done!" << std::endl;
  std::cout << "Alice's balance: " << alice.balance << std::endl;
  std::cout << "Bob's balance:   " << bob.balance << std::endl;
  return 0;
}
