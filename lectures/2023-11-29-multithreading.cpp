#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

const size_t N = 1000000000;

std::mutex MUTEX;
uint64_t new_sum_total = 0;

void new_sum(const uint64_t* data, size_t step) {
  // std::cout << "Starting at pointer " << data << std::endl;
  uint64_t sum = 0;

  for(size_t i = 0; i < N; i += step) {
    sum += data[i];
  }

  std::lock_guard<std::mutex> lock(MUTEX);
  new_sum_total += sum;
}

// load data[i]
// load new_sum_total
// add the above
// store new_sum_total


std::atomic<uint64_t> atomic_sum = 0;

void atomic_adder(const uint64_t* data, size_t step) {
  uint64_t sum = 0;
  for(size_t i = 0; i < N; i += step) {
    sum += data[i];
  }

  atomic_sum += sum;
}

uint64_t async_sum_worker(const uint64_t* data, size_t step) {
  uint64_t sum = 0;
  for(size_t i = 0; i < N; i += step) {
    sum += data[i];
  }

  return sum;
}

void async_sum(const uint64_t* data) {
  auto start = std::chrono::high_resolution_clock::now();

  auto fut1 = std::async(std::launch::async, async_sum_worker, &data[0], 2);
  auto fut2 = std::async(std::launch::async, async_sum_worker, &data[1], 2);

  uint64_t sum = fut1.get() + fut2.get();

  auto stop = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

  std::cout << "Sum: " << sum << '\n';
  std::cout << "Took " << time << " milliseconds.\n";
}


void old_sum(const uint64_t* data) {
  auto start = std::chrono::high_resolution_clock::now();

  uint64_t sum = 0;
  for(size_t i = 0; i < N; ++i) {
    sum += data[i];
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

  std::cout << "Sum: " << sum << '\n';
  std::cout << "Took " << time << " milliseconds.\n";
}

void init_array(uint64_t* data) {
  auto start = std::chrono::high_resolution_clock::now();

  for(size_t i = 0; i < N; ++i) {
    data[i] = i;
  }

  auto stop = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
  std::cout << "Initialized in " << time << " milliseconds." << std::endl;
}

int main() {
  uint64_t* data = new uint64_t[N];
  init_array(data);

  old_sum(data);
  // old_sum(data);
  // old_sum(data);

  async_sum(data);

  // auto start = std::chrono::high_resolution_clock::now();

  // new_sum_total = 0;
  // std::thread t1(atomic_adder, &data[0], 2);
  // std::thread t2(atomic_adder, &data[1], 2);

  // t1.join();
  // t2.join();

  // auto stop = std::chrono::high_resolution_clock::now();
  // auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

  // std::cout << "Sum: " << atomic_sum << '\n';
  // std::cout << "Took " << time << " milliseconds.\n";
  delete [] data;
  return 0;
}
