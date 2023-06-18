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
    if (symbols == NULL)
    {   
        printf("Error: malloc failed\n");
        exit(1);
    }
    
    // reserviert den Speicher für die Anzahl der Zahlen
    int numberCount = symbolCount+1;
    numbers = malloc(numberCount * sizeof(Number));
    if (numbers == NULL)
    {   
        printf("Error: malloc failed\n");
        exit(1);
    }
    
    int k = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if(checkSymbol(input[i]) == 1){
            symbols[k] = (Symbol){input[i], 0, i};
            
            if(k == 0 && symbolCount > 1){
                // die Zahl links vom ersten Symbol
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number = malloc(i * sizeof(char));
                int index = 0;
                for (int j = 0; j < i; j++) {
                    number[index] = input[j];
                    index++;
                }
                number[index] = '\0'; 
                numbers[k] = (Number){strtod(number, NULL), 0};
                free(number);
            }else if (symbolCount == 1){
                // die Zahl links vom Symbol
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number1 = malloc(i * sizeof(char));
                int index = 0;
                for (int j = 0; j < i; j++) {
                    number1[index] = input[j];
                    index++;
                }
                number1[index] = '\0'; 
                numbers[0] = (Number){strtod(number1, NULL), 0};
                free(number1);

                // die Zahl rechts vom Symbol
                int start2 = symbols[k].index+1;
                int length2 = stringLenght - start2;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number2 = malloc((length2) * sizeof(char));
                int index2 = 0;
                for (int j = start2; input[j] != '\0'; j++) {
                    number2[index2] = input[j];
                    index2++;
                }
                number2[index2] = '\0';   
                numbers[k+1] = (Number){strtod(number2, NULL), 0};
                free(number2);
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
                number[index] = '\0'; 
                numbers[k] = (Number){strtod(number, NULL), 0};
                free(number);
            }else if ( k == symbolCount-1){
                // die Zahl links vom letzten Symbol
                int start1 = symbols[k-1].index+1;
                int length1 = symbols[k].index - start1;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number1 = malloc((length1) * sizeof(char));
                int index1 = 0;
                for (int j = start1; j < i; j++) {
                    number1[index1] = input[j];
                    index1++;
                }
                number1[index1] = '\0'; 
                numbers[k] = (Number){strtod(number1, NULL), 0};
                free(number1);
                
                // die Zahl rechts vom letzten Symbol
                int start2 = symbols[k].index+1;
                int length2 = stringLenght - start2;
                // reserviert den Speicher für die Anzahl der Zeichen
                char *number2 = malloc((length2) * sizeof(char));
                int index2 = 0;
                for (int j = start2; input[j] != '\0'; j++) {
                    number2[index2] = input[j];
                    index2++;
                }
                number2[index2] = '\0';   
                numbers[k+1] = (Number){strtod(number2, NULL), 0};
                free(number2);
            }
            k++;
        }
    }
}

double calculate(void){
    
}

int main(int argc, char** argv){
    printInfo();
    scanf("%s", input);
    // überprüft ob der String "exit" ist um das Programm zu beenden
    if (strncmp(input, "exit", 4) == 0)
        exit(0);
    
    printf("Your input: %s\n", input);
    splitInput2(input);
    printf("Result: %f\n", calculate());
    return 0;
}