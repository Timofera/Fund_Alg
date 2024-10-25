#include <stdio.h>
#include <stdio.h>
#include <math.h>

long double calculate_dichotomy(long double (*func)(long double x), long double a, long double b, long double eps) {
    int sign = 1;
    /*if (func(a) > func(b)) {
        sign = 0;
    }*/
    long double c;
    long double fa = func(a);
    long double fc;
    if ((fa * func(b)) > 0) {
        printf("No roots on the segment [a,b]\n");
        return 0;
    }
    long double last;
    while (fabsl(b - a) >= eps) {
        c = (a + b) / 2;
        fc = func(c);
        if (fa * fc <= 0) {
            b = c;
        }
        else {
            a = c;
            fa = fc;
        }
    }
    return c;
}

long double func1(long double x) {
    return (cos((x / 2))); //long double cos() only C++
}

int main() {
    long double a = 0;
    long double b = 3;
    long double epsilon = 0.000000000000001;
    if (epsilon < 0.000000000000001) {
        printf("too much accuracy");
        return 0;
    }
    if (calculate_dichotomy(&func1, a, b, epsilon) == 0) return 0;
    printf("answer = %Lf", calculate_dichotomy(&func1, a, b, epsilon));
    return 0;
}