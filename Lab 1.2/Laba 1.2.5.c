#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define pi 3.1415
#define Max_iteration 1000
#define MIN_EPSILON 0.000000001

typedef enum Errors {
    Incorrect_arguments = 1,
    Invalid_input = 2
} Errors;


int atof_1(const char* string, double* eps) {
    int sign = 1, signs = 0, dots = 0, numbers = 0;
    double result = 0.0, fraction_part = 1.0;
    for (int i = 0; string[i] != '\0'; ++i) {
        if (strlen(string) > 8) {
            printf("%s", "too accurate epsilon\n");
            break;
        }
        if (string[i] == '-' && signs == 0) {
            signs = 1;
            sign = -1;
            printf("epsilon must be > 0\n");
            break;
        }
        else if (string[i] == '.' && dots == 0) {
            dots = 1;
        }
        else if (string[i] >= '0' && string[i] <= '9' && dots == 0) {
            result += result * 10.0 + (string[i] - '0');
        }
        else if (string[i] >= '0' && string[i] <= '9' && dots == 1) {
            fraction_part /= 10.0;
            result += (string[i] - '0') * fraction_part;
        }
        else {
            printf("Invalid_input");
            return Invalid_input;
        }
    }
    if (result == 0.0) {
        printf("Incorrect_arguments");
        return Incorrect_arguments;
    }
    *eps = result * sign;
    return 0;
}


int GetOpts(int argc, char** argv, double* parametr) {
    if (argv[1] == NULL) {
        printf("No arguments\n");
        return 1;
    }
    if (argc > 2) {
        printf("Too much arguments\n");
        return 1;
    }
    return atof_1(argv[1], parametr);
}

double factorial(int n) {
    int answer = 1;
    for (int i = 2; i <= n; i++) {
        answer *= i;
    }

    return answer * 1.00;
}

double Factorial(int n) {
    double answer = 1.0;
    for (int k = 1; k <= n; k++) {

        answer *= k;
    }
    return answer;
}
// Ãàììà ÷åðåç ïðåäåë
double lim_gamma(double epsilon) {
    double gamma = -100;// ÷òîáû áûëî íå ìåíüøå åïñèëîí â ïåðâûé ðàç ( --100)
    double prev_gamma;
    int m = 1;
    double fact_m = 2;// ëîã(1) == 0
    while (m < Max_iteration) {
        double sum = 0.0;
        double fact_k = 1;
        for (int k = 2; k <= m; k++) {
            fact_k *= k;
            double binomial = fact_m / (fact_k * Factorial(m - k));
            sum += binomial * (k % 2 ? -1.0 : 1.0) * log(fact_k) / k;
        }
        prev_gamma = gamma;
        gamma = sum;

        if (fabs(gamma - prev_gamma) < epsilon) {
            return gamma;
        }
        m++;
        fact_m *= m;
    }
    fprintf(stderr, "Lim_gamma:\n did`t converge for %d iteration \n", Max_iteration);
    return gamma;
}
//       Ãàììà ðÿä
double row_gamma(double epsilon) {
    double gamma = 0.0;
    double term;
    int k = 2;

    while (k < Max_iteration) {
        term = 1.0 / (floor(sqrt(k)) * floor(sqrt(k))) - (1.0 / k);
        gamma += term;
        if (fabsl(term) < epsilon && term != 0) {
            return gamma - pi * pi / 6.0;
        }

        k++;
    }
    fprintf(stderr, "Row_gamma:\n did`t converge for %d iteration \n", Max_iteration);
    return gamma - pi * pi / 6.0;
}

bool IsPrime(int n) {
    for (int i = 2; i <= sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

double ProdResult(int t) {
    double product = 1.0;
    for (int p = 2; p <= t; p++) {
        if (IsPrime(p)) {
            product *= (double)(p - 1) / p;
        }
    }
    return product;
}

// Óðàâíåíèå äëÿ ðàñ÷åòà ãàììà
double Equation_gamma(double epsilon) {
    double a = -1.0;
    double b = 2.0;
    double t = 2.0;
    double prev_x = 0.0;
    double xx = 0.0;
    double f_x = 0.0;
    for (int i = 0; i < Max_iteration; i++) {
        double product = ProdResult((int)t);

        double current_x = log(t) * product;
        if (fabs(current_x - prev_x) < epsilon) {//ïðàâàÿ ïîñ÷èò
            //           double eqv = Eqvation((double) epsilon, (double) current_x, (double) a, (double) b);
            //ïðàâàÿ ïîñ÷èò
            double f_a = current_x - exp(-a);
            while (fabs(a - b) >= epsilon) {
                double c = (a + b) / 2;
                double f_c = current_x - exp(-c);
                if (f_a * f_c > 0) {
                    a = c;
                    f_a = f_c;
                }
                else  b = c;
            }
            return a;

        }
        prev_x = current_x;
        t += 1;

    }
    fprintf(stderr, "Equation_gamma:\n did`t converge for %d iteration \n", Max_iteration);
    return prev_x;
}
//double xx = 0.0;
//double Eqvation(double epsilon, double current_x, double a, double b) {
  //  double c= 0.0  ;
    //double f_a = current_x - exp(-a);
    //while (fabs(a-b) >= epsilon) {
    //    double c = (a + b) / 2;
    //    double f_c = current_x - exp(-c);
    //    if (f_a * f_c > 0) {
    //        a = c;
    //        f_a = f_c;
    //    }
    //    else  b = c;
   //}
   // return c;
//}

double lim_e(double epsilon) {
    int n = 1;
    double current_element = pow((1.00 + 1.00 / n), n * 1.00) * 1.00;
    double last_element = 0;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        n++;
        current_element = pow((1.00 + 1.00 / n), n * 1.00) * 1.00;
    }
    return current_element;
}

double lim_pi(double epsilon) {
    int n = 1;
    double current_element = pow(pow(2, n) * factorial(n), 4) / (n * pow(factorial(2 * n), 2));
    double last_element = 0;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        current_element *= (4 * n * (n + 1)) / pow(2 * n + 1, 2);
        n++;
    }
    return current_element;
}

double lim_log(double epsilon) {
    int n = 1;
    double current_element = (pow(2, 1.00 / n) - 1) * n;
    double last_element = 0;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        n++;
        current_element = (pow(2, 1.00 / n) - 1) * n;
    }
    return current_element;
}

double lim_square(double epsilon) {
    double current_element = -0.5;
    double last_element = 0;
    while (fabs(last_element - current_element) >= epsilon) {
        last_element = current_element;
        current_element = last_element - pow(last_element, 2) / 2 + 1;
    }
    return current_element;
}


double row_e(double epsilon) {
    int n = 0;
    double current_element = 1.0000;
    double summ = 0;
    while (current_element >= epsilon) {
        summ += current_element;
        n++;
        current_element /= n;
    }
    return summ;
}

double row_pi(double epsilon) {
    int n = 2;
    double last_element = 0.0;
    double current_element = 4.0;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        current_element += 4 * (pow(-1, n - 1) / (2 * n - 1));
        n++;
    }
    return current_element;
}

double row_log(double epsilon) {
    int n = 2;
    double last_element = 0.0000;
    double current_element = 1.0000;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        current_element += (pow(-1, n - 1) / n);
        n++;
    }
    return current_element;
}

double row_sqrt(double epsilon) {
    int k = 2;
    double last_element = 0.0000;
    double current_element = pow(2, 1 / pow(2, k));
    k++;
    while (fabs(current_element - last_element) >= epsilon) {
        last_element = current_element;
        current_element *= pow(2, 1 / pow(2, k));
        k++;
    }
    return current_element;
}


double Equation_e(double epsilon) {
    double a = 1.00;
    double b = 3.00;
    double c = 0;
    double fa = log(a) - 1;
    while (fabs(a - b) >= epsilon) {
        c = (a + b) / 2;
        double fc = log(c) - 1;
        if (fc * fa > 0) {
            a = c;
            fa = fc;

        }
        else {
            b = c;
        }
    }
    return c;
}

double Equation_pi(double epsilon) {
    double a = 1.00;
    double b = 3.00;
    double c = 0;
    double fa = cos(a);//ô-ÿ >=0
    while (fabs(a - b) >= epsilon) {
        c = (a + b) / 2;
        double fc = cos(c);
        if (fc * fa > 0) {
            a = c;
            fa = fc;

        }
        else {
            b = c;
        }
    }
    return c * 2;//èùåì ïè/2, ïîòîì ïè/2 * 2
}

double Equation_log(double epsilon) {
    double a = 0.00;
    double b = 1.00;
    double c = 0;
    double fa = exp(a) - 2;
    while (fabs(a - b) >= epsilon) {
        c = (a + b) / 2;
        double fc = exp(c) - 2;
        if (fc * fa > 0) {
            a = c;
            fa = fc;

        }
        else {
            b = c;
        }
    }
    return c;
}

double Equation_sqrt(double epsilon) {
    double a = 0.00;
    double b = 2.00;
    double c = 0;
    double fa = a * a - 2;
    while (fabs(a - b) >= epsilon) {
        c = (a + b) / 2;
        double fc = c * c - 2;
        if (fc * fa > 0) {
            a = c;
            fa = fc;

        }
        else {
            b = c;
        }
    }
    return c;
}



int main(int argc, char** argv) {
    double epsilon;
    if (GetOpts(argc, argv, &epsilon)) {
        return 1;
    }
    printf("E: \n Limit: %f; Row: %f; Equation: %f;\n", lim_e(epsilon), row_e(epsilon), Equation_e(epsilon));
    printf("Pi: \n Limit: %f; Row: %f; Equation: %f\n", lim_pi(epsilon), row_pi(epsilon), Equation_pi(epsilon));
    printf("Ln2: \n Limit: %f; Row: %f; Equation: %f\n", lim_log(epsilon), row_log(epsilon), Equation_log(epsilon));
    printf("Sqrt: \n Limit: %f; Row: %f; Equation: %f\n", lim_square(epsilon), row_sqrt(epsilon), Equation_sqrt(epsilon));
    printf("Gamma: \nLimit: %f; Row: %f; Equation: %f\n", lim_gamma(epsilon), row_gamma(epsilon), Equation_gamma(epsilon));
    return 0;
}