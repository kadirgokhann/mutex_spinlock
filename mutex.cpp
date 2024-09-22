#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;  // Mutex for synchronization
int sharedCounter = 0;

void incrementCounter(int id) {
    for (int i = 0; i < 1000; ++i) {
        std::lock_guard<std::mutex> lock(mtx);  // Locks mutex
        ++sharedCounter;                        // Critical section
        // Mutex is automatically released when lock goes out of scope
    }
}

int main() {
    std::thread t1(incrementCounter, 1);
    std::thread t2(incrementCounter, 2);

    t1.join();
    t2.join();

    std::cout << "Final counter value: " << sharedCounter << std::endl;
    return 0;
}
