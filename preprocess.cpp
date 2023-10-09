#include "include/preprocess.h"

#include "include/data.h"

#include <iostream>

static void tab_to_space(std::string &s, int tab_equaling_spaces) {
    std::string tmp = "";
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == '\t') 
            for (int j = 0; j < tab_equaling_spaces; j++) tmp += ' ';   /* can be optimized by metaprogramming */
        else tmp += s[i];
    }
    s = tmp;
}

static void count_space(std::string &s) {
    int current_line = 1;
    g_space_count[1] = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == ' ') g_space_count[current_line]++;
        else {
            for (; i < s.length() && s[i] != '\n'; i++);
            current_line++;
            g_space_count[current_line] = 0;
        }
        
    }
}

static void count_lines(std::string &s) {
    for (unsigned i = 0; i < s.length(); i++) {
        if (s[i] == '\n') g_max_line++;
    }
}

void preprocess(int tab_equaling_spaces) {
    tab_to_space(g_text, tab_equaling_spaces);
    count_lines(g_text);
    g_char_count = new int[g_max_line + 5];
    g_space_count = new int[g_max_line + 5];
    count_space(g_text);
}