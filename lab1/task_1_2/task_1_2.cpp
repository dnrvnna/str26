#include <iostream>
#include <time.h>


unsigned long long factorial(int n)
{
    unsigned long long result = 1;
    for (int i = 2; i <= n; ++i)
        result *= i;
    return result;
}

int main()
{
    std::cout << "--- Task 1.2 Factorial ---\n";
    const int iterations = 10000000;
    unsigned long long result = 0;

    clock_t start_clock = clock();;

    for (int i = 0; i < iterations; ++i)
    {
        result += factorial(10);
    }

    clock_t end_clock = clock();


    double seconds_clock = (double)(end_clock - start_clock) / CLOCKS_PER_SEC;
    
	std::cout << "Result = " << result << "\n";
    std::cout << "Time (clock)  = " << seconds_clock << " sec\n";

    return 0;
}