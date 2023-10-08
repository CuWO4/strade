#include "include/preprocess.h"

#include "include/data.h"

#include <iostream>

static void tab_to_space(FILE *in, FILE *out, int tab_equaling_spaces) {
    char c;
    while ((c = fgetc(in)) != EOF) {
        if (c == '\t') {
            for (int i = 0; i < tab_equaling_spaces; i++) 
                fputc(' ', out);
        }
        else fputc(c, out);
    }
}

void preprocess(int tab_equaling_spaces) {
    FILE *tmp = fopen(TEMPORARY_INTERMEDIATE_FILE_NAME, "w");
    tab_to_space(g_source_file, tmp, tab_equaling_spaces);
    fclose(g_source_file);
    fclose(tmp);
    g_source_file = fopen(TEMPORARY_INTERMEDIATE_FILE_NAME, "r");
}