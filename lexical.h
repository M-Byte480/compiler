//
// Created by kmila on 10/03/2025.
//

#ifndef LEXICAL_H
#define LEXICAL_H
#include <stdbool.h>
#include <stdio.h>

void lexicalAnalyser(FILE* input);
bool isKeyword(char* str);
bool isOperator(char chr);

#endif //LEXICAL_H
