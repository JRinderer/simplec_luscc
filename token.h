#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_TYPE_STRING,
    TOKEN_TYPE_KEYWORD,
    TOKEN_TYPE_IDENTIFIER,
    TOKEN_TYPE_NUMBER,
    TOKEN_TYPE_OPERATOR,
    TOKEN_TYPE_DELIMITER,
    TOKEN_TYPE_WHITESPACE,
    TOKEN_TYPE_UNKNOWN
} TokenType;

typedef struct {
    char *tok;
    char *value;
    TokenType type;
} Token;

#endif // TOKEN_H