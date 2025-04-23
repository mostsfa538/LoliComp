#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 1000
#define MAX_TOKEN_LEN 64

typedef struct
{
	char type[32];
	char value[32];
} Token;

int is_keyword(char *str)
{
	return strcmp(str, "int") == 0 || strcmp(str, "return") == 0;
}

Token *lex(FILE *file, int *tokenCount)
{
	Token *token = malloc(sizeof(Token) * MAX_TOKENS);
	*tokenCount = 0;
	char c;
	while ((c = fgetc(file)) != EOF)
	{
		if (isspace(c))
		{
			continue;
		}

		else if (isalpha(c))
		{
			char buffer[MAX_TOKEN_LEN] = {0};
			int i = 0;
			buffer[i++] = c;
			while ((c = fgetc(file)) != EOF && (isalnum(c) || c == '_'))
			{
				buffer[i++] = c;
			}
			ungetc(c, file);
			strcpy(token[*tokenCount].value, buffer);
			if (is_keyword(buffer))
				strcpy(token[*tokenCount].type, "KEYWORD");
			else
				strcpy(token[*tokenCount].type, "IDENTIFIER");
			(*tokenCount)++;
		}
		else if (isdigit(c))
		{
			char buffer[MAX_TOKEN_LEN] = {0};
			int i = 0;
			buffer[i++] = c;
			while ((c = fgetc(file)) != EOF && isdigit(c))
			{
				buffer[i++] = c;
			}
			ungetc(c, file);
			strcpy(token[*tokenCount].value, buffer);
			strcpy(token[*tokenCount].type, "NUMBER");
			(*tokenCount)++;
		}
	}
	return token;
}

int main()
{
	FILE *file = fopen("testt.c", "r");
	if (!file)
	{
		perror("Error opening file");
		return 1;
	}
	int count = 0;
	Token *tokens = lex(file, &count);
	fclose(file);
	for (int i = 0; i < count; i++)
	{
		printf("Token %d: Type = %s, Value = %s\n", i + 1, tokens[i].type,
			   tokens[i].value);
	}
	free(tokens);
	return 0;
}
