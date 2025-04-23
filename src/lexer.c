#include "../include/lexer.h"


void print_token(Token *token)
{
	if (token == NULL)
	{
		fprintf(stderr, "Error: Token is NULL\n");
		return;
	}

	const char *type_str;

	switch (token->type)
	{
		case TOKEN_IDENTIFIER:
			type_str = "Identifier";
			break;
		case TOKEN_INTEGER:
			type_str = "Integer";
			break;
		case TOKEN_SINTEGER:
			type_str = "Signed Integer";
			break;
		case TOKEN_CHARACTER:
			type_str = "Character";
			break;
		case TOKEN_STRING:
			type_str = "String";
			break;
		case TOKEN_FLOAT:
			type_str = "Float";
			break;
		case TOKEN_SFLOAT:
			type_str = "Signed Float";
			break;
		case TOKEN_VOID:
			type_str = "Void";
			break;
		case TOKEN_CONDITION:
			type_str = "Condition";
			break;
		case TOKEN_LOOP:
			type_str = "Loop";
			break;
		case TOKEN_RETURN:
			type_str = "Return";
			break;
		case TOKEN_BREAK:
			type_str = "Break";
			break;
		case TOKEN_STRUCT:
			type_str = "Struct";
			break;
		case TOKEN_ARITHMETIC_OP:
			type_str = "Arithmetic Operator";
			break;
		case TOKEN_LOGIC_OP:
			type_str = "Logic Operator";
			break;
		case TOKEN_RELATIONAL_OP:
			type_str = "Relational Operator";
			break;
		case TOKEN_ASSIGNMENT_OP:
			type_str = "Assignment Operator";
			break;
		case TOKEN_ACCESS_OP:
			type_str = "Access Operator";
			break;
		case TOKEN_BRACES:
			type_str = "Braces";
			break;
		case TOKEN_CONSTANT:
			type_str = "Constant";
			break;
		case TOKEN_QUOTATION_MARK:
			type_str = "Quotation Mark";
			break;
		case TOKEN_INCLUSION:
			type_str = "Inclusion";
			break;
		case TOKEN_COMMENT_CONTENT:
			type_str = "Comment Content";
			break;
		case TOKEN_COMMENT_START:
			type_str = "Comment Start";
			break;
		case TOKEN_COMMENT_END:
			type_str = "Comment End";
			break;
		case TOKEN_ERROR:
			printf("Line : %d Error in Token Text: %s Token Type: Invalid "
				   "Identifier\n",
				   token->line, token->value);
			free(token->value);
			free(token);
			return;
		default:
			type_str = "Unknown";
	}

	printf("Line : %d Token Text: %s Token Type: %s\n", token->line,
		   token->value, type_str);
	free(token->value);
	free(token);
}

Token *generate_keyword_or_identifier(char *current, int *current_index)
{
	Token *token = malloc(sizeof(Token));
	token->line = malloc(sizeof(size_t));
	token->line = line_number;
	char *keyword = malloc(sizeof(char) * 8);
	int keyword_index = 0;

	while (isalpha(current[*current_index]) && current[*current_index] != '\0')
	{
		keyword[keyword_index++] = current[*current_index++];
	}
	if (strcmp(keyword, "IfTrue") == 0 || strcmp(keyword, "Otherwise") == 0)
	{
		token->type = TOKEN_CONDITION;
	}
	else if (strcmp(keyword, "Imw") == 0)
	{
		token->type = TOKEN_INTEGER;
	}
	else if (strcmp(keyword, "SIMw") == 0)
	{
		token->type = TOKEN_SINTEGER;
	}
	else if (strcmp(keyword, "Chj") == 0)
	{
		token->type = TOKEN_CHARACTER;
	}
	else if (strcmp(keyword, "Series") == 0)
	{
		token->type = TOKEN_STRING;
	}
	else if (strcmp(keyword, "IMwf") == 0)
	{
		token->type = TOKEN_FLOAT;
	}
	else if (strcmp(keyword, "SIMwf") == 0)
	{
		token->type = TOKEN_SFLOAT;
	}
	else if (strcmp(keyword, "NOReturn") == 0)
	{
		token->type = TOKEN_VOID;
	}
	else if (strcmp(keyword, "RepeatWhen") == 0 ||
			 strcmp(keyword, "Reiterate") == 0)
	{
		token->type = TOKEN_LOOP;
	}
	else if (strcmp(keyword, "Turnback") == 0)
	{
		token->type = TOKEN_RETURN;
	}
	else if (strcmp(keyword, "OutLoop") == 0)
	{
		token->type = TOKEN_BREAK;
	}
	else if (strcmp(keyword, "Loli") == 0)
	{
		token->type = TOKEN_STRUCT;
	}
	else if (strcmp(keyword, "Include") == 0)
	{
		token->type = TOKEN_INCLUSION;
	}
	else
	{
		token->type = TOKEN_IDENTIFIER;
		token->value = keyword;
	}
	return token;
}

Token *generate_number(char *current, int *current_index);
Token *generate_separator_or_operator(char *current, int *current_index,
									  TokenType type);
Token *lexer(FILE *file);
