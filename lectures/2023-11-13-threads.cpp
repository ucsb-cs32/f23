#include <chrono>
#include <iostream>
#include <string>
#include <thread>

const size_t N = 1000000000;

uint64_t new_sum_total = 0;
void new_sum(const uint64_t* data, size_t step) {
  std::cout << "Starting at pointer " << data << std::endl;
  for(size_t i = 0; i < N; i += step) {
    new_sum_total += data[i];
  }
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
  std::cout << "Took " << time << " seconds.\n";
}

int main() {
  uint64_t* data = new uint64_t[N];

  for(size_t i = 0; i < N; ++i) {
    data[i] = i;
  }

  // old_sum(data);
  // old_sum(data);
  // old_sum(data);

  auto start = std::chrono::high_resolution_clock::now();

  new_sum_total = 0;
  std::thread t1(new_sum, &data[0], 2);
  std::thread t2(new_sum, &data[1], 2);

  t1.join();
  t2.join();

  auto stop = std::chrono::high_resolution_clock::now();
  auto time = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

  std::cout << "Sum: " << new_sum_total << '\n';
  std::cout << "Took " << time << " seconds.\n";
  delete [] data;
  return 0;
}
