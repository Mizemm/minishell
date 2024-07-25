#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, world! This is a test.";
    const char delim[] = " ,!."; // Delimiters: space, comma, exclamation mark, period
    char *token;

    // Get the first token
    token = strtok(str, delim);


    printf("Token: %s\n", token);


    return 0;
}
