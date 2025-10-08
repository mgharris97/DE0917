// Matthew Harris 241ADB166
// https://github.com/mgharris97/DE0917 <- GitHub repo containing all labs
// Compile with: gcc -O2 -Wall -Wextra -std=c17 -o calc calc.c

#include <stdio.h>

int main(int argc, char *argv[]) 
{
    printf("There are %d arguments\n", argc);
    for (int i = 0; i<argc; i++)
    {
        printf("argv[%d] = %s\n",i, argv[i]);
    }
    return 0;
    
}