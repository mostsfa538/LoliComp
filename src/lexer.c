#include "../include/lexer.h"

size_t line_number = 0;

/**
 * @brief Prints the token information.
 * @param token The token to print.
 */
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
			printf("Line : %d Error in Token Text: %s Token Type: Invalid Identifier\n",
                   token->line, token->value);
            free(token->value);
            free(token);
            return;
		default:
			type_str = "Unknown";
	}

	if (!token->value)
    {
        printf("Line : %d Token Type: %s (null value)\n", token->line, type_str);
    }
    else
    {
        printf("Line : %d Token Text: %s Token Type: %s\n", token->line, token->value, type_str);
        free(token->value);
    }
    free(token);
}

/**
 * @brief Generates a keyword or identifier token from the input string.
 * @param current The input string.
 * @param current_index The current index in the input string.
 * @return A pointer to the generated token.
 */

Token *generate_keyword_or_identifier(char *current, int *current_index)
{
	Token *token = malloc(sizeof(Token));
	if (token == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for token\n");
		exit(EXIT_FAILURE);
	}

	token->line = line_number;
	char keyword[64];
	int keyword_index = 0;

	while (keyword_index < 63 && isalpha(current[*current_index]) &&
		   current[*current_index] != '\0')
	{
		keyword[keyword_index++] = current[*current_index++];
	}
	keyword[keyword_index] = '\0';

	if (strcmp(keyword, "IfTrue") == 0 || strcmp(keyword, "Otherwise") == 0)
		token->type = TOKEN_CONDITION;
	else if (strcmp(keyword, "Imw") == 0)
		token->type = TOKEN_INTEGER;
	else if (strcmp(keyword, "SIMw") == 0)
		token->type = TOKEN_SINTEGER;
	else if (strcmp(keyword, "Chj") == 0)
		token->type = TOKEN_CHARACTER;
	else if (strcmp(keyword, "Series") == 0)
		token->type = TOKEN_STRING;
	else if (strcmp(keyword, "IMwf") == 0)
		token->type = TOKEN_FLOAT;
	else if (strcmp(keyword, "NOReturn") == 0)
		token->type = TOKEN_VOID;
	else if (strcmp(keyword, "SIMwf") == 0)
		token->type = TOKEN_SFLOAT;
	else if (strcmp(keyword, "NOReturn") == 0)
		token->type = TOKEN_VOID;
	else if (strcmp(keyword, "RepeatWhen") == 0 ||
			 strcmp(keyword, "Reiterate") == 0)
		token->type = TOKEN_LOOP;
	else if (strcmp(keyword, "Turnback") == 0)
		token->type = TOKEN_RETURN;
	else if (strcmp(keyword, "OutLoop") == 0)
		token->type = TOKEN_BREAK;
	else if (strcmp(keyword, "Loli") == 0)
		token->type = TOKEN_STRUCT;
	else if (strcmp(keyword, "Include") == 0)
		token->type = TOKEN_INCLUSION;
	else
		token->type = TOKEN_IDENTIFIER;

	token->value = strdup(keyword);
	if (!token->value)
	{
		fprintf(stderr,
				"Error: Memory allocation failed for identifier value\n");
		free(token);
		exit(EXIT_FAILURE);
	}
	return token;
}

/**
 * @brief Generates a number token from the input string.
 * @param current The input string.
 * @param current_index The current index in the input string.
 * @return A pointer to the generated token.
 */

Token *generate_number(char *current, int *current_index)
{
	Token *token = malloc(sizeof(Token));
	if (token == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for token\n");
		exit(EXIT_FAILURE);
	}

	token->line = line_number;
	char *number = malloc(sizeof(char) * 20);
	if (number == NULL)
	{
		fprintf(stderr, "Error: Memory allocation failed for number\n");
		free(token);
		exit(EXIT_FAILURE);
	}

	int number_index = 0;

	if (current[*current_index] == '-')
	{
		number[number_index++] = current[*current_index];
		(*current_index)++;

		while (isdigit(current[*current_index]) &&
			   current[*current_index] != '\0')
		{
			number[number_index++] = current[*current_index];
			(*current_index)++;
		}
		number[number_index] = '\0';

		if (current[*current_index] == '.')
		{
			token->type = TOKEN_SFLOAT;
			number[number_index++] = current[*current_index];
			(*current_index)++;
			while (isdigit(current[*current_index]) &&
				   current[*current_index] != '\0')
			{
				number[number_index++] = current[*current_index];
				(*current_index)++;
			}
			number[number_index] = '\0';
		}
		else
		{
			token->type = TOKEN_SINTEGER;
		}
	}
	else
	{
		while (isdigit(current[*current_index]) &&
			   current[*current_index] != '\0')
		{
			number[number_index++] = current[*current_index];
			(*current_index)++;
		}
		number[number_index] = '\0';

		if (current[*current_index] == '.')
		{
			token->type = TOKEN_FLOAT;
			number[number_index++] = current[*current_index];
			(*current_index)++;
			while (isdigit(current[*current_index]) &&
				   current[*current_index] != '\0')
			{
				number[number_index++] = current[*current_index];
				(*current_index)++;
			}
			number[number_index] = '\0';
		}
		else
		{
			token->type = TOKEN_INTEGER;
		}
	}
	token->value = number;
	return token;
}

Token *generate_separator_or_operator(char *current, int *current_index,
									  TokenType type)
{
	Token *token = malloc(sizeof(Token));
	if (!token)
	{
		fprintf(stderr, "Error: Memory allocation failed for token\n");
		exit(EXIT_FAILURE);
	}
	token->line = line_number;
	char *value = malloc(sizeof(char) * 3);
	if (!value)
	{
		fprintf(stderr, "Error: Memory allocation failed for token value\n");
		free(token);
		exit(EXIT_FAILURE);
	}
	value[0] = current[*current_index];
	value[1] = '\0';
	token->value = value;

	switch (current[*current_index])
	{
		case '+':
		case '-':
			if (current[*current_index] == '-' &&
				current[(*current_index) + 1] == '>')
			{
				free(token->value);
				token->value = strdup("->");
				token->type = TOKEN_ACCESS_OP;
				(*current_index) += 2;
				return token;
			}
			token->type = TOKEN_ARITHMETIC_OP;
			break;
		case '*':
		case '/':
			if (current[*current_index + 1] == '@')
			{
				free(token->value);
				free(token);
				return NULL;
			}
			token->type = TOKEN_ARITHMETIC_OP;
			break;
		case '&':
		case '|':
			if (current[(*current_index) + 1] == current[*current_index])
			{
				free(token->value);
				token->value = strndup(&current[*current_index], 2);
				token->type = TOKEN_LOGIC_OP;
				(*current_index)++;
			}
			else
			{
				token->type = TOKEN_LOGIC_OP;
			}
			break;
		case '=':
			if (current[(*current_index) + 1] == '=')
			{
				free(token->value);
				token->value = strdup("==");
				token->type = TOKEN_RELATIONAL_OP;
				(*current_index)++;
			}
			else
			{
				token->type = TOKEN_ASSIGNMENT_OP;
			}
			break;
		case '>':
		case '<':
		case '!':
			if (current[(*current_index) + 1] == '=')
			{
				free(token->value);
				token->value = strndup(&current[*current_index], 2);
				token->type = TOKEN_RELATIONAL_OP;
				(*current_index)++;
			}
			else if (current[*current_index] == '!')
			{
				token->type = TOKEN_ERROR;
			}
			else
			{
				token->type = TOKEN_RELATIONAL_OP;
			}
			break;
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
			token->type = TOKEN_BRACES;
			break;
		case ';':
			token->type = TOKEN_ERROR;
			break;
		default:
			token->type = type;
			break;
	}
	(*current_index)++;
	return token;
}

Token *lexer(FILE *file)
{
	char *current = malloc(sizeof(char) * 256);
	if (!current)
	{
		fprintf(stderr, "Error: Memory allocation failed for buffer\n");
		exit(EXIT_FAILURE);
	}
	int current_index = 0;
	Token *token = NULL;

	while (fgets(current, 256, file) != NULL)
	{
		line_number++;
		current_index = 0;

		while (current[current_index] != '\0')
		{
			if (isspace(current[current_index]))
			{
				current_index++;
				continue;
			}

			if (current[current_index] == '/' &&
				current[current_index + 1] == '@')
			{
				Token *start_token = malloc(sizeof(Token));
				start_token->type = TOKEN_COMMENT_START;
				start_token->value = strdup("/@");
				start_token->line = line_number;
				print_token(start_token);

				current_index += 2;

				char content[256] = {0};
				int content_index = 0;
				while (current[current_index] != '\0' &&
					   !(current[current_index] == '@' &&
						 current[current_index + 1] == '/'))
				{
					content[content_index++] = current[current_index++];
				}
				content[content_index] = '\0';

				if (content_index > 0)
				{
					Token *content_token = malloc(sizeof(Token));
					content_token->type = TOKEN_COMMENT_CONTENT;
					content_token->value = strdup(content);
					content_token->line = line_number;
					print_token(content_token);
				}

				if (current[current_index] == '@' &&
					current[current_index + 1] == '/')
				{
					Token *end_token = malloc(sizeof(Token));
					end_token->type = TOKEN_COMMENT_END;
					end_token->value = strdup("@/");
					end_token->line = line_number;
					print_token(end_token);
					current_index += 2;
				}

				continue;
			}
			size_t prev_index = current_index;

			if (isalpha(current[current_index]))
			{
				token = generate_keyword_or_identifier(current, &current_index);
			}
			else if (isdigit(current[current_index]) ||
					 (current[current_index] == '-' &&
					  isdigit(current[current_index + 1])))
			{
				token = generate_number(current, &current_index);
			}
			else if (current[current_index] == '\"' ||
					 current[current_index] == '\'')
			{
				token = generate_separator_or_operator(current, &current_index,
													   TOKEN_QUOTATION_MARK);
			}
			else
			{
				token = generate_separator_or_operator(current, &current_index,
													   TOKEN_ERROR);
			}

			if (current_index == prev_index)
			{
				fprintf(stderr, "Line %zu: Forcing skip of character '%c'\n",
						line_number, current[current_index]);
				current_index++;
			}

			if (token)
			{
				print_token(token);
			}
		}
	}

	free(current);
	return NULL;
}
