#include <stdio.h>
#include <stdlib.h>
#include "lexical.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input file>\n", argv[0]);
        exit(1);
    }

    {
        FILE *ptrfile = fopen(argv[1], "r");
        if (ptrfile == NULL) {
            printf("Error: Unable to open file\n");
            return 1;
        }
        lexicalAnalyser(ptrfile);

        fclose(ptrfile);
    }

    return 0;
}
