#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include "vars.h"
#include "scanner.h"
#include <ctype.h>
#include <string.h>

long current_position = 0;

void scan_string(FILE *file, Token *token) {
    // Rewind the file one character back
    //fseek(file, -1, SEEK_CUR);
    current_position--;

    int buffer_size = 128;
    int length = 0;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF && ch != '"') {
        buffer[length++] = ch;
        current_position++;
        if (length >= buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
            if (buffer == NULL) {
                perror("Failed to reallocate memory");
                exit(1);
            }
        }
    }
    current_position++;
    buffer[length] = '\0';

    token->tok = buffer;
    token->type = TOKEN_TYPE_STRING;
}

void scan_keyword_or_identifier(FILE *file, Token *token) {
    // Rewind the file one character back
    fseek(file, -1, SEEK_CUR);
    current_position--;

    int buffer_size = 128;
    int length = 0;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF && (isalnum(ch) || ch == '_')) {
        buffer[length++] = ch;
        current_position++;
        if (length >= buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
            if (buffer == NULL) {
                perror("Failed to reallocate memory");
                exit(1);
            }
        }
    }
    ungetc(ch, file); // Put back the non-alphanumeric character
    current_position--;
    buffer[length] = '\0';

    // Check if the buffer is a reserved keyword
    token->type = TOKEN_TYPE_IDENTIFIER;
    for (int i = 0; reserved_keywords[i] != NULL; i++) {
        if (strcmp(buffer, reserved_keywords[i]) == 0) {
            token->type = TOKEN_TYPE_KEYWORD;
            break;
        }
    }

    token->tok = buffer;
}

void scan_number(FILE *file, Token *token) {
    // Rewind the file one character back
    fseek(file, -1, SEEK_CUR);
    current_position--;

    int buffer_size = 128;
    int length = 0;
    char *buffer = (char *)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        perror("Failed to allocate memory");
        exit(1);
    }

    char ch;
    while ((ch = fgetc(file)) != EOF && isdigit(ch)) {
        buffer[length++] = ch;
        current_position++;
        if (length >= buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size * sizeof(char));
            if (buffer == NULL) {
                perror("Failed to reallocate memory");
                exit(1);
            }
        }
    }
    ungetc(ch, file); // Put back the non-digit character
    current_position--;
    buffer[length] = '\0';

    token->tok = buffer;
    token->type = TOKEN_TYPE_NUMBER;
    token->value = atoi(buffer);
}

void scan_operator_or_delimiter(FILE *file, Token *token) {
    // Rewind the file one character back
    fseek(file, -1, SEEK_CUR);
    current_position--;

    char ch = fgetc(file);
    current_position++;

    char buffer[2] = {ch, '\0'};
    token->tok = strdup(buffer);

    // Check if the character is an operator
    token->type = TOKEN_TYPE_OPERATOR;
    for (int i = 0; operators[i] != NULL; i++) {
        if (strcmp(buffer, operators[i]) == 0) {
            return;
        }
    }

    // Check if the character is a delimiter
    token->type = TOKEN_TYPE_DELIMITER;
    for (int i = 0; delimiters[i] != NULL; i++) {
        if (strcmp(buffer, delimiters[i]) == 0) {
            return;
        }
    }

    // If not an operator or delimiter, set as unknown
    token->type = TOKEN_TYPE_UNKNOWN;
}

void start_scanner(FILE *file) {
    char ch;
    Token token;
    while ((ch = fgetc(file)) != EOF) {
        current_position++;if (ch == '"') {
            scan_string(file, &token);
            printf("Token: %s, Type: STRING\n", token.tok);
        } else if (isalpha(ch)) {
            scan_keyword_or_identifier(file, &token);
            printf("Token: %s, Type: %s\n", token.tok, token.type == TOKEN_TYPE_KEYWORD ? "KEYWORD" : "IDENTIFIER");
        } else if (isdigit(ch)) {
            scan_number(file, &token);
            printf("Token: %s, Type: NUMBER, Value: %d\n", token.tok, token.value);
        } else if (isspace(ch)) {
            continue;
        } else {
            scan_operator_or_delimiter(file, &token);
            printf("Token: %s, Type: %s\n", token.tok,
                   token.type == TOKEN_TYPE_OPERATOR ? "OPERATOR" :
                   token.type == TOKEN_TYPE_DELIMITER ? "DELIMITER" : "UNKNOWN");
        }
    }
}