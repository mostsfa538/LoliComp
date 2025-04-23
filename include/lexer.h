#ifndef LEXER_H
#define LEXER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "error.h"

typedef enum {
    TOKEN_IDENTIFIER,     // Variable name
    TOKEN_INTEGER,        // Unsigned integer
    TOKEN_SINTEGER,       // Signed integer
    TOKEN_CHARACTER,      // Character
    TOKEN_STRING,         // String
    TOKEN_FLOAT,          // Double precision float
    TOKEN_SFLOAT,         // Single precision float
    TOKEN_VOID,           // Void
    TOKEN_CONDITION,      // IfTrue-Otherwise
    TOKEN_LOOP,           // RepeatWhen/Reiterate
    TOKEN_RETURN,         // Turnback
    TOKEN_BREAK,          // OutLoop
    TOKEN_STRUCT,         // Loli
    TOKEN_ARITHMETIC_OP,  // +, -, *, /
    TOKEN_LOGIC_OP,       // &&, ||, ~
    TOKEN_RELATIONAL_OP,  // ==, <, >, !=, <=, >=
    TOKEN_ASSIGNMENT_OP,  // =
    TOKEN_ACCESS_OP,      // ->
    TOKEN_BRACES,         // {, }, [, ]
    TOKEN_CONSTANT,       // Numbers
    TOKEN_QUOTATION_MARK, // ", '
    TOKEN_INCLUSION,      // Include
    TOKEN_COMMENT_CONTENT,// Comment Content
    TOKEN_COMMENT_START,  // start of comment
    TOKEN_COMMENT_END,    // End of comment
    TOKEN_ERROR           // Error token
} TokenType;

typedef struct {
    TokenType type;
    char *value;
    int line;
} Token;

size_t line_number = 0;

void print_token(Token *token);
Token *generate_number(char *current, int *current_index);
Token *generate_keyword_or_identifier(char *current, int *current_index);
Token *generate_separator_or_operator(char *current, int *current_index, TokenType type);
Token *lexer(FILE *file);
#endif