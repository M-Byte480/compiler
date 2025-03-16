#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Token {
    char *value;
    char *type;
};


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

bool isOperator(char chr) {
    return (
        chr == '+' || chr == '-' || chr == '*' || chr == '/' || chr == '='
    );
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

void parseInput(FILE *ptr_file) {
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


// if (chr == ' ' || chr == '\n' || chr == '\r') {
//     if (buffer_size > 0) {
//         buffer[buffer_size] = '\0';
//         buffer_size = 0;
//         if (isKeyword(buffer)) {
//             printf("keywrd ");
//         } else if (isOperator(buffer[0])) {
//             char* op_type = getOperatorType(buffer);
//             printf("op-%s", op_type);
//         } else {
//             printf("id ");
//         }
//     }
//
//     if (chr == '\n') {
//         printf("\n");
//     }
// } else if (chr == ',') {
//     printf(", ");
//     buffer_size = 0; // Reset Buffer
// } else {
//     buffer[buffer_size] = chr;
//     buffer_size++;
// }