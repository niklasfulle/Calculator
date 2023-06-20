// Autor: Niklas Fulle

#include <math.h>

// addiert zwei Zahlen
double add(double a, double b){
    return a + b;
}

// subtrahiert zwei Zahlen
double subtract(double a, double b){
    return a - b;
}

// multipliziert zwei Zahlen
double multiply(double a, double b){
    return a * b;
}

// dividiert zwei Zahlen
double divide(double a, double b){
    return a / b;
}

double calculateOneSymbol(double a, double b, char symbol){
    switch (symbol){
        case '+':
            return add(a, b);
        case '-':
            return subtract(a, b);
        case '*':
            return multiply(a, b);
        case '/':
            return divide(a, b);
        default:
            return 0;
    }
}