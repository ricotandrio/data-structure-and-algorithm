#include <stdio.h>

int fibonacci(int n) {
    int fib[n + 1] = {};
    fib[0] = 0;
    fib[1] = 1;
    for(int i = 2; i <= n; i++){
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    return (n <= 0 ? 0 : n == 1 ? 1 : fib[n]);
}

int main() {
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...

    for(int i = 0; i < 10; i++){
        printf("Fibonacci(%d) = %d\n", i, fibonacci(i));
    }

    return 0;
}
