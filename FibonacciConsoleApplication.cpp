// FibonacciConsoleApplication.cpp

#include <iostream>

struct FibNum
{
    double val = 0;
    unsigned int exp = 0;
};


FibNum calcFib(unsigned int n)
{
    FibNum prev2;
    FibNum prev1;
    FibNum fib;
    prev2.val = 0;
    prev1.val = 1;

    for (unsigned int i = 2; i < n + 1; i++)
    {
        // Calculate the current Fibonacci-Number and adjust the previous values
        fib.val = prev1.val + prev2.val;
        prev2.val = prev1.val;
        prev1.val = fib.val;

        // Enable numbers above the double type limit by keeping the numbers small and storing the exponent (Base 10) separately
        if (fib.val > 10)
        {
            prev2.val /= 10;
            prev1.val /= 10;
            fib.val /= 10;
            prev2.exp++;
            prev1.exp++;
            fib.exp++;
        }
    }
    return fib;
}


int main()
{
    std::cout << "Fibonacci-Calculator, Eingabe: " << std::endl;
    unsigned int n;
    FibNum fib;
    while (true)
    {
        std::cin >> n;
        fib = calcFib(n);
        std::cout << "Die Fibonacci Zahl fuer " << n << " ist: " << fib.val << "*10^" << fib.exp << std::endl;
    }
    return 0;
}