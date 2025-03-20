#include "lexical.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

struct Token {
    char *value;
    char *type;
};

typedef enum {
    IDENTIFIER, NUMBER, OPERATOR, UNKNOWN, KEYWORD
} TokenType;


bool isOperator(char chr) {
    return (
        chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '='
    );
}

void processToken(char *token) {
    if (isdigit(token[0])) {
        printf("NUMBER: %s\n", token);
    } else if (isalpha(token[0])) {
        printf("IDENTIFIER: %s\n", token);
    // } else if (isKeyword(token[0])) {
    //     printf("KEYWORD: %s\n", token);
    } else {
        printf("UNKNOWN TOKEN: %s\n", token);
    }
}

bool isKeyword(char *str) {
    const char *keywords[]
            = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }

    return false;
}


char* getOperatorType(char op) {
    switch (op) {
        case '+': return "plus";
        case '-': return "minus";
        case '*': return "mult";
        case '/': return "div";
        case '=': return "assign";
        default: return "unknown";
    }
}

void lexicalAnalyser(FILE *ptr_file) {
    char chr;
    char buffer[100];
    int buffer_size = 0;

    while ((chr = fgetc(ptr_file)) != EOF) {
        if (isalpha(chr)) {
            buffer[buffer_size++] = chr;
            while ((chr = fgetc(ptr_file)) != EOF && (isalpha(chr) || isdigit(chr))) {
                buffer[buffer_size++] = chr;
            }
            buffer[buffer_size] = '\0';
            ungetc(chr, ptr_file);

            if (isKeyword(buffer)) {
                printf("keywrd ");
            } else {
                printf("id ");
            }
            buffer_size = 0;
        }
        else if (isdigit(chr)) {
            buffer[buffer_size++] = chr;
            while ((chr = fgetc(ptr_file)) != EOF && isdigit(chr)) {
                buffer[buffer_size++] = chr;
            }
            buffer[buffer_size] = '\0';
            ungetc(chr, ptr_file);
            printf("num ");
            buffer_size = 0;
        }
        else if (isOperator(chr)) {
            printf("op-%s ", getOperatorType(chr));
        }
        else if (chr == ';') {
            printf(";\n");
        }
        else if (isspace(chr)) {
            continue;
        }
        else {
            printf("%c", chr);
        }
    }
}

void test(FILE *ptrFile) {
    char ch, buffer[MAX_TOKEN_LENGTH];
    int index = 0;

    while ((ch = fgetc(ptrFile)) != EOF) {
        if (isspace(ch)) {
            continue;
        } else if (isalnum(ch)) {
            buffer[index++] = ch;
        } else if (isOperator(ch)) {
            if (index > 0) {
                buffer[index] = '\0';
                processToken(buffer);
                index = 0;
            }
            printf("%c", ch);
        } else {
            if (index > 0) {
                buffer[index] = '\0';
                processToken(buffer);
                index = 0;
            }
            printf("UNKNOWN CHARACTER: %c\n", ch);
        }
    }

    if (index > 0) {
        buffer[index] = '\0';
        processToken(buffer);
    }
}
