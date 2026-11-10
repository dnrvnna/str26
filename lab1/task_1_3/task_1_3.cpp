#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <string>
#include <atomic>

std::atomic<unsigned long long> sink{ 0 };
std::mutex printMutex;

unsigned long long factorial(int n)
{
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

void Func(std::string name, int iterations)
{
    unsigned long long local = 0;

    // Засекаем время внутри потока
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        local += factorial(10);
    }

    auto end = std::chrono::high_resolution_clock::now();
    sink.fetch_add(local);

    double seconds = std::chrono::duration<double>(end - start).count();

    // Блокируем вывод, чтобы потоки не мешали друг другу
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << name << " finished in " << seconds << " sec\n";
}

int main()
{
    const int iterations = 10000000;

    // 1. Последовательно
    auto start_seq = std::chrono::high_resolution_clock::now();
    Func("seq-1", iterations);
    Func("seq-2", iterations);
    auto end_seq = std::chrono::high_resolution_clock::now();
    double total_seq = std::chrono::duration<double>(end_seq - start_seq).count();

    std::cout << "Sequential total time: " << total_seq << " sec\n\n";

    // 2. В двух потоках
    auto start_thr = std::chrono::high_resolution_clock::now();
    std::thread thread1(Func, "t1", iterations);
    std::thread thread2(Func, "t2", iterations);

    thread1.join();
    thread2.join();

    auto end_thr = std::chrono::high_resolution_clock::now();
    double total_thr = std::chrono::duration<double>(end_thr - start_thr).count();

    std::cout << "Threads total time: " << total_thr << " sec\n";

    return 0;
}