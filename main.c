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
int symbolCount;

void createNumberStart(size_t size, size_t start, size_t end, size_t numbersIndex, char * input){
    // reserviert den Speicher für die Anzahl der Zeichen
    char *number = malloc(size * sizeof(char));
    int index = 0;
    for (size_t j = start; j < end; j++) {
        number[index] = input[j];
        index++;
    }
    number[index] = '\0';
    numbers[numbersIndex] = (Number){strtod(number, NULL), 0};
    free(number);
}

void createNumberLastCharakter(size_t size, size_t start, size_t numbersIndex, char * input){
    // reserviert den Speicher für die Anzahl der Zeichen
    char *number = malloc(size * sizeof(char));
    int index = 0;
    for (size_t j = start; input[j] != '\0'; j++) {
        number[index] = input[j];
        index++;
    }
    number[index] = '\0';
    numbers[numbersIndex] = (Number){strtod(number, NULL), 0};
    free(number);
}

void splitInput(char * input){
    
    symbolCount = 0;
    for (size_t i = 0; input[i] != '\0'; i++){
        if(checkSymbol(input[i]) == 1){
            symbolCount++;
        }
    }

    // ruft die Funktion getStringLenght auf für die Länge des Strings
    int stringLenght = getStringLenght(input);

    // reserviert den Speicher für die Anzahl der Symbole
    symbols = malloc(symbolCount * sizeof(Symbol));
    if (symbols == NULL){   
        printf("Error: malloc failed\n");
        exit(1);
    }
    
    // reserviert den Speicher für die Anzahl der Zahlen
    int numberCount = symbolCount+1;
    numbers = malloc(numberCount * sizeof(Number));
    if (numbers == NULL){   
        printf("Error: malloc failed\n");
        exit(1);
    }
    
    size_t k = 0;
    for (size_t i = 0; input[i] != '\0'; i++){
        if(checkSymbol(input[i]) == 1){
            symbols[k] = (Symbol){input[i], 0, i};
            
            if(k == 0 && symbolCount > 1){
                // die Zahl links vom ersten Symbol
                createNumberStart(i, 0, i, k, input);
            }else if (symbolCount == 1){
                // die Zahl links vom Symbol
                createNumberStart(i, 0, i, 0, input);

                // die Zahl rechts vom Symbol
                size_t start = symbols[k].index+1;
                size_t length = stringLenght - start;
                createNumberLastCharakter(length, start, 1, input);
            }else if (k > 0 && k < symbolCount-1){
                // die Zahl links vom Symbol
                size_t start = symbols[k-1].index+1;
                size_t length = symbols[k].index - start;
                createNumberStart(length, start, i, k, input);
            }else if ( k == symbolCount-1){
                // die Zahl links vom letzten Symbol
                size_t start1 = symbols[k-1].index+1;
                size_t length1 = symbols[k].index - start1;
                createNumberStart(length1, start1, i, k, input);
                
                // die Zahl rechts vom letzten Symbol
                size_t start2 = symbols[k].index+1;
                size_t length2 = stringLenght - start2;
                createNumberLastCharakter(length2, start2, k+1, input);
            }
            k++;
        }
    }
}

double calculate(void){
    int symbolCountMulDiv, symbolCountAddSub = 0;
    for (size_t i = 0; i < symbolCount; i++){
        if(symbols[i].data == '*' || symbols[i].data == '/'){
            symbolCountMulDiv++;
        }else if (symbols[i].data == '+' || symbols[i].data == '-'){
            symbolCountAddSub++;
        }
    }

    if(symbolCount == 1){
        numbers[0].data = calculateOneSymbol(numbers[0].data, numbers[1].data, symbols[0].data);
        numbers[1].used = 1;
        symbols[0].used = 1;
        numbers[0].used = 1;
    }else if (symbolCount > 1){
        if(symbolCountMulDiv > 0 && symbolCountAddSub == 0){
            int i = 0;
            while (i < symbolCount){
                if(numbers[i+1].used != 1 && symbols[i].used != 1){
                    if (symbols[i].data == '*' || symbols[i].data == '/'){
                        numbers[0].data = calculateOneSymbol(numbers[0].data, numbers[i+1].data, symbols[i].data);
                        numbers[i+1].used = 1;
                        symbols[i].used = 1;
                    }
                }
                i++;
            }
            numbers[0].used = 1;
        }
        else if (symbolCountMulDiv > 0 && symbolCountAddSub > 0){
            /*int i = 0;
            while (i < symbolCount){
                if(symbols[i].used != 1){
                    if (symbols[i].data == '*' || symbols[i].data == '/'){
                        /*numbers[i].data = calculateOneSymbol(numbers[i].data, numbers[i+1].data, symbols[i].data);
                        numbers[i+1].used = 1;
                        symbols[i].used = 1;
                        printf("i: %d\n", i);
                        symbols[i].used = 1;
                    }
                }
                i++;
            }*/
            /*int i = 0;
            while (i < symbolCount){
                if(numbers[i].used != 1 && numbers[i+1].used != 1 && symbols[i].used != 1){
                    if (symbols[i].data == '*' || symbols[i].data == '/'){
                        numbers[i].data = calculateOneSymbol(numbers[i].data, numbers[i+1].data, symbols[i].data);
                        numbers[i+1].used = 1;
                        symbols[i].used = 1;
                    }
                }
                i++;
            }
            int j = 0;
            while (j < symbolCount){
                if(numbers[j].used != 1 && numbers[j+2].used != 1 && symbols[j].used != 1 || symbols[j+1].used != 1){
                    if (symbols[j].data == '*' || symbols[j].data == '/'){
                        numbers[j].data = calculateOneSymbol(numbers[j].data, numbers[j+2].data, symbols[j+1].data);
                        numbers[j+2].used = 1;
                        symbols[j].used = 1;
                        printf("%c\n", symbols[j].data);
                    }
                }
                j++;
            }*/
        }else {
            int i = 0;
            while (i < symbolCount){
                if (symbols[i].data == '+' || symbols[i].data == '-'){
                    numbers[0].data = calculateOneSymbol(numbers[0].data, numbers[i+1].data, symbols[i].data);
                    numbers[i+1].used = 1;
                    symbols[i].used = 1;
                }
                i++;
            }
            numbers[0].used = 1;
        }
    }

    /*for (size_t i = 0; i < symbolCount; i++)
    {   
        printf("Numbers: %f\n", numbers[i].data);
        printf("Used: %d\n", numbers[i].used);
        printf("Symbols: %c\n", symbols[i].data);
        printf("Used: %d\n", symbols[i].used);
    }*/
    
    
    return numbers[0].data;
}

int main(int argc, char** argv){
    printInfo();
    scanf("%s", input);
    // überprüft ob der String "exit" ist um das Programm zu beenden
    if (strncmp(input, "exit", 4) == 0)
        exit(0);
    
    validateInput(input);
    splitInput(input);
    printf("Your input: %s\n", input);
    //calculate();
    printf("Result: %f\n", calculate());
    return 0;
}