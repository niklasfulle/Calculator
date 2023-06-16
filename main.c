#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.c"

char input[100];
char input2[100];
double result;

void printInfo(){
    printf("Calculator v0.1\n");
    printf("Functions like add(+), subtract(-), multiply(x), divide(/)\n");
    printf("Simply like '10.0+10.2'\n");
    printf("Type 'exit' to exit\n");
}

void splitInput(char *input){
    int inputSize = 0;
    for (size_t i = 0; input[i] != '\0'; i++)
    {
        inputSize++;
    }
    
    char symbol;
    int index;
    for (int i = 0; input[i] != '\0'; i++) {
        if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'){
            symbol = input[i];
            index = i;
        }
        if(input[i] == '\0'){
            printf("Invalid input\n");
            exit(0);
        }
    }

    char *firstNumber = malloc(index * sizeof(char));
    int secondNumberSize = inputSize-(index+1);
    char *secondNumber = malloc(secondNumberSize * sizeof(char));

    for (int i = 0; i < index; i++) {
        firstNumber[i] = input[i];
    }

    for (int i = index+1; i <= inputSize; i++) {
        secondNumber[i-(index+1)] = input[i];
    }

    double firstNumberDouble = strtod(firstNumber, NULL);
    double secondNumberDouble = strtod(secondNumber, NULL);

    switch (symbol)
    {
    case 43:
        result = add(firstNumberDouble, secondNumberDouble);
        break;

    case 45:
        result = subtract(firstNumberDouble, secondNumberDouble);
        break;  

    case 47:  
        result = divide(firstNumberDouble, secondNumberDouble);
        break;

    case 42:  
        result = multiply(firstNumberDouble, secondNumberDouble);
        break;
    }
}

int main(int argc, char** argv){
    printInfo();
    scanf("%s", input);
    if (strncmp(input, "exit", 4) == 0)
        exit(0);
    
    printf("Your input: %s\n", input);
    splitInput(input);
    printf("Result: %f\n", result);
    while (strncmp(input, "exit", 4) != 0)
    {
       scanf("%s", input2);
       if (strncmp(input2, "exit", 4) == 0)
        exit(0);
       printf("Your input: %s\n", input2);
    }
    return 0;
}