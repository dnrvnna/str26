#include <thread>
#include <mutex>
#include <string>
#include <iostream>
#include <time.h>

std::mutex m;

void Func(std::string name)
{
	long double i = 0;
	clock_t start = clock();
    clock_t now = clock();
    while ((double)(now - start) / CLOCKS_PER_SEC < 1.0)
    {
		i += 1e-9;
        now = clock();
    }
	
    m.lock();
    std::cout << name << ": " << i << std::endl;
    m.unlock();

}

int main()
{
    std::thread thread1(Func, "t1");
    std::thread thread2(Func, "t2");
    std::thread thread3(Func, "t3");
    thread1.join();
    thread2.join();
    thread3.join();

    system("pause");
}
