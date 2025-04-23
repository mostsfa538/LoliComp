#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "../include/lexer.h"

void init_scanner(FILE *src);         // Set the source file
Token *get_next_token();              // Main function to get next token
void reset_scanner();                 // Optional, to reset file pointer
void scan_file();                     // Optional utility to scan whole file

#endif
