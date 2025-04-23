#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/lexer.h"

int main()
{
    FILE *file = fopen("test.sc", "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }
    lexer(file);
}
