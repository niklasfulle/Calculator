// Autor: Niklas Fulle

// printet die Info über den Calculator
void printInfo(){
    printf("Calculator v1.0\n");
    printf("Functions like add(+), subtract(-), multiply(x), divide(/)\n");
    printf("Simply like '10+10+10+10'\n");
    printf("Max Four Numbers\n");
    printf("Type 'exit' to exit\n");
}

// überprüft ob ein Symbol ein gültiges Rechenzeichen ist und gibt 1 zurück wenn ja, sonst 0
int checkSymbol(char symbol){
    if(symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/'){
        return 1;
    }
    return 0;
}

// gibt die Länge eines Strings zurück
int getStringLenght(char *string){
    int lenght = 0;
    for (int i = 0; string[i] != '\0'; i++){
        lenght++;
    }
    return lenght;
}

void validateInput(char *input){
    int stringLenght = getStringLenght(input);
    int symbolCount = 0;
    for (int i = 0; input[i] != '\0'; i++){
        //check for only valid symbols
        if(input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != '.' && (input[i] < '0' || input[i] > '9')){
            printf("\033[0;31mError: invalid symbol found\033[0m\n");
            exit(1);
        }
        if(input[i] == '.'){
            if((input[i-1] < '0' || input[i-1] > '9') || (input[i+1] < '0' || input[i+1] > '9')){
                printf("\033[0;31mError: invalid symbol found\033[0m\n");
            exit(1);
            }
        }
        //check for only one symbol in a row
        if(checkSymbol(input[i]) == 1 && checkSymbol(input[i+1]) == 1){
            printf("\033[0;31mError: two symbols in a row\033[0m\n");
            exit(1);
        }
        if(checkSymbol(input[i]) == 1){
            symbolCount++;
        }
    }
    if(symbolCount == 0){
        printf("\033[0;31mError: no symbol found\033[0m\n");
        exit(1);
    }
    if(symbolCount > 0){
        if(input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/'){
            printf("\033[0;31mError: first symbol is not a number\033[0m\n");
            exit(1);
        }
        if(input[stringLenght-1] == '+' || input[stringLenght-1] == '-' || input[stringLenght-1] == '*' || input[stringLenght-1] == '/'){
            printf("\033[0;31mError: last symbol is not a number\033[0m\n");
            exit(1);
        }
    }
}