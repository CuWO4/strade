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

void preprocess(int tab_equaling_spaces) {
    tab_to_space(g_text, tab_equaling_spaces);
}