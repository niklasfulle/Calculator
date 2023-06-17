// Autor: Niklas Fulle

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.c"
#include "utils.c"

typedef struct{
    char data;
    int used;
    int index;
} Symbol;

typedef struct{
    double data;
    int used;
} Number;

char input[100];
Symbol *symbols;
Number *numbers;

void splitInput2(char * input){
    
    int symbolCount = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if(checkSymbol(input[i]) == 1){
            symbolCount++;
        }
    }

    // ruft die Funktion getStringLenght auf für die Länge des Strings
    int stringLenght = getStringLenght(input);

    // reserviert den Speicher für die Anzahl der Symbole
    symbols = malloc(symbolCount * sizeof(Symbol));
    // reserviert den Speicher für die Anzahl der Zahlen
    numbers = malloc((symbolCount+1) * sizeof(Number));
    
    int k = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if(checkSymbol(input[i]) == 1){
            symbols[k] = (Symbol){input[i], 0, i};
            
            if(k == 0){
                // die Zahl links vom ersten Symbol
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number = malloc(i * sizeof(char));
                for (int j = 0; j < i; j++) {
                    number[j] = input[j];
                }
                numbers[k] = (Number){strtod(number, NULL), 0};
                free(number);
            }else if (k > 0 && k < symbolCount-1){
                // die Zahl links vom Symbol
                int start = symbols[k-1].index+1;
                int length = symbols[k].index - start;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number = malloc(length * sizeof(char));
                int index = 0;
                for (int j = start; j < i; j++) {
                    number[index] = input[j];
                    index++;
                }
                numbers[k] = (Number){strtod(number, NULL), 0};
                free(number);
            }else if ( k == symbolCount-1){
                // die Zahl links vom letzten Symbol
                int start1 = symbols[k-1].index+1;
                int length1 = symbols[k].index - start1;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number1 = malloc(length1 * sizeof(char));
                int index1 = 0;
                for (int j = start1; j < i; j++) {
                    number1[index1] = input[j];
                    index1++;
                }
                numbers[k] = (Number){strtod(number1, NULL), 0};
                free(number1);
                
                // die Zahl rechts vom letzten Symbol
                int start2 = symbols[k].index+1;
                int length2 = stringLenght - start2;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number2 = malloc(length2 * sizeof(char));
                int index2 = 0;
                for (int j = start2; input[j] != '\0'; j++) {
                    printf("%d\n", j);
                    number2[index2] = input[j];
                    index2++;
                }
                numbers[k+1] = (Number){strtod(number2, NULL), 0};
            }
            k++;
        }
    }
}

double splitInput(char *input){
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
        return add(firstNumberDouble, secondNumberDouble);
        break;

    case 45:
        return subtract(firstNumberDouble, secondNumberDouble);
        break;  

    case 47:  
        return divide(firstNumberDouble, secondNumberDouble);
        break;

    case 42:  
        return multiply(firstNumberDouble, secondNumberDouble);
        break;
    }
}

int main(int argc, char** argv){
    printInfo();
    scanf("%s", input);
    // überprüft ob der String "exit" ist um das Programm zu beenden
    if (strncmp(input, "exit", 4) == 0)
        exit(0);
    
    printf("Your input: %s\n", input);
    //splitInput(input);
    splitInput2(input);
    //printf("Result: %f\n", splitInput(input));
    /*while (strncmp(input, "exit", 4) != 0)
    {
       scanf("%s", input2);
       if (strncmp(input2, "exit", 4) == 0)
        exit(0);
       printf("Your input: %s\n", input2);
    }*/
    return 0;
}