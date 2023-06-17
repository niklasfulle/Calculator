// Autor: Niklas Fulle

// printet die Info über den Calculator
void printInfo(){
    printf("Calculator v1.0\n");
    printf("Functions like add(+), subtract(-), multiply(x), divide(/)\n");
    printf("Simply like '10+10+10'\n");
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
    for (int i = 0; string[i] != '\0'; i++)
    {
        lenght++;
    }
    return lenght;
}