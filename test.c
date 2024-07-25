#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct 
{
    char *type;
    char *value;
    void *next;
} Token;

void add_token(Token **tokens, int *token_count, const char *type, const char *value) 
{
    Token *new_tokens = malloc((*token_count + 1) * sizeof(Token));
    if (new_tokens == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    if (*tokens != NULL) 
    {
        memcpy(new_tokens, *tokens, *token_count * sizeof(Token));
        free(*tokens);
    }

    new_tokens[*token_count].type = strdup(type);
    new_tokens[*token_count].value = strdup(value);

    if (new_tokens[*token_count].type == NULL || new_tokens[*token_count].value == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    *tokens = new_tokens;
    (*token_count)++;
}

void tokenize(const char *input, Token **tokens, int *token_count) 
{
    const char *current = input;
    char *buffer = malloc(strlen(input) + 1);
    if (buffer == NULL) 
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    int buf_idx;

    while (*current != '\0') 
    {
        if (isspace(*current)) 
        {
            current++;
            continue;
        }

        buf_idx = 0;

        if (*current == '-' && isalnum(*(current + 1))) 
        {
            while (*current && !isspace(*current)) 
                buffer[buf_idx++] = *current++;
            
            buffer[buf_idx] = '\0';
            add_token(tokens, token_count, "OPTION", buffer);
        } 
        else if (strchr("|&><=", *current)) 
        {
            buffer[buf_idx++] = *current++;
            buffer[buf_idx] = '\0';
            add_token(tokens, token_count, "OPERATOR", buffer);
        } 
        else if (*current == '"' || *current == '\'') 
        {
            char quote = *current++;
            while (*current && *current != quote) 
                buffer[buf_idx++] = *current++;
            
            if (*current == quote) 
                current++;
            
            buffer[buf_idx] = '\0';
            add_token(tokens, token_count, "QUOTED_STRING", buffer);
        } 
        else if (*current == '$' && isalnum(*(current + 1))) 
        {
            buffer[buf_idx++] = *current++;
            while (isalnum(*current) || *current == '_') 
                buffer[buf_idx++] = *current++;
            
            buffer[buf_idx] = '\0';
            add_token(tokens, token_count, "VARIABLE", buffer);
        } 
        else 
        {
            while (*current && !isspace(*current) && !strchr("|&><=", *current)) 
                buffer[buf_idx++] = *current++;
            
            buffer[buf_idx] = '\0';

            if (*token_count == 0 || strcmp((*tokens)[*token_count - 1].type, "OPERATOR") == 0) 
                add_token(tokens, token_count, "COMMAND", buffer);
            else 
                add_token(tokens, token_count, "ARGUMENT", buffer);
        }
    }

    free(buffer);
}

int main() 
{
    const char *command = "ls ls";
    Token *tokens = NULL;
    int token_count = 0;

    tokenize(command, &tokens, &token_count);
    for (int i = 0; i < token_count; i++) 
    {
        printf("Token type: %s, value: '%s'\n", tokens[i].type, tokens[i].value);
        free(tokens[i].type);
        free(tokens[i].value);
    }

    free(tokens);

    return 0;
}
