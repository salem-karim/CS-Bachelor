#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

void countUp(int &i, int numberOfTimes, std::mutex &m) {
  for (int currentLoop = 0; currentLoop < numberOfTimes; currentLoop++) {
    m.lock();
    i++;
    m.unlock();
  }
}

int dynamicCountThreads(int numberOfThreads, int totalNumberOfTimes) {
  std::mutex m;
  std::vector<std::thread> threads;
  int currentValue = 0;
  threads.reserve(numberOfThreads);
  int timesPerThread = 0;
  if (numberOfThreads)
    timesPerThread = totalNumberOfTimes / numberOfThreads;
  for (int i = 0; i < numberOfThreads; i++) {
    threads.push_back(std::thread(countUp, std::ref(currentValue),
                                  timesPerThread, std::ref(m)));
  }
  for (int i = 0; i < numberOfThreads; i++) {
    if (threads[i].joinable()) {
      threads[i].join();
    }
  }

  return currentValue;
}

/* Aufgabe 2*/
int main() {
  int threadCount;
  int totalNumberCount;

  std::cout << "thread count: ";
  std::cin >> threadCount;
  std::cout << std::endl;

  std::cout << "total number count: ";
  std::cin >> totalNumberCount;
  std::cout << std::endl;

  int i = dynamicCountThreads(threadCount, totalNumberCount);
  std::cout << "i: " << i << std::endl;

  return 0;
}

/* Selbstcheck Threading 2 Aufgabe 1
int main() {
  int i = 0;
  std::mutex m;

  std::thread countThreadA(countUp, std::ref(i), 1000000, std::ref(m));
  std::thread countThreadB(countUp, std::ref(i), 1000000, std::ref(m));
  std::thread countThreadC(countUp, std::ref(i), 1000000, std::ref(m));
  std::thread countThreadD(countUp, std::ref(i), 1000000, std::ref(m));

  countThreadA.join();
  countThreadB.join();
  countThreadC.join();
  countThreadD.join();

  std::cout << "i: " << i << std::endl;

  return 0;
}
*/
