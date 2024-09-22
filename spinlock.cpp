#include <atomic>
#include <thread>
#include <iostream>

class Spinlock {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;

public:
    void lock() {
        while (flag.test_and_set(std::memory_order_acquire)) {
            // Busy-wait (spin)
        }
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

// Shared resource
int sharedCounter = 0;
Spinlock spinlock;

void incrementCounter(int id) {
    for (int i = 0; i < 1000; ++i) {
        spinlock.lock();
        ++sharedCounter;
        spinlock.unlock();
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
