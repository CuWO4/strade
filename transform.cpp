#include "include/transform.h"
#include "include/data.h"

#include <iostream>

/* @return whether ch is '{' or ';' or '}' */
static bool is_control_char(char ch) {
    return ch == '{' || ch == ';' || ch == '}';
}

static void vector_assign(std::vector<int> &vec, int i, int x) { /* for unknown reason, vector::push_back() crushes. */
    vec.reserve((i / 10 + 1) * 10);
    vec[i] = 0; 
}

void transform(void) {
    std::string tmp = "";
    int in_bracket = 0;
    bool in_single_quote = false, in_double_quote = false;
    for (unsigned i = 0; i < g_text.length(); i++) { // handle the comment
        if (g_text[i] == '(') in_bracket++;
        if (g_text[i] == ')') in_bracket--;
        // Note: The two conditions i>0 and g_text[i - 1] != '\\' take advantage of short-circuit evaluation techniques
        if (g_text[i] == '\'' && i > 0 && g_text[i - 1] != '\\') in_single_quote = !in_single_quote;
        if (g_text[i] == '\"' && i > 0 && g_text[i - 1] != '\\') in_double_quote = !in_double_quote;
        if (i + 1 < g_text.length()) {
            if (g_text[i] == '/' && g_text[i + 1] == '/') {
                tmp += '\n';
                for (; i < g_text.length() && g_text[i] != '\n'; i++) {
                    tmp += g_text[i];
                    g_char_count[g_line]++;
                }
            }
            if (g_text[i] == '/' && g_text[i + 1] == '*') {
                tmp += '\n';
                for (; i < g_text.length() - 1 &&
                    !(g_text[i] == '*' && g_text[i + 1] == '/'); i++) {
                    tmp += g_text[i];
                    if (g_text[i] == '\n') g_line++;
                    else g_char_count[g_line]++;
                }
                
            }
        }
        if (is_control_char(g_text[i])) {
            if (in_single_quote || in_double_quote) {
                tmp += g_text[i];
                g_char_count[g_line]++;
                continue;
            }
            if (g_text[i] == ';' && in_bracket) {
                tmp += g_text[i];
                g_char_count[g_line]++;
                continue;
            }

            while (true) {
                if (tmp.length() == 0) break;

                char c = tmp[tmp.length() - 1];
                if (c == '\n') {
                    g_line--;
                    tmp.pop_back();
                }
                else if (c == ' ') {
                    g_char_count[g_line]--;
                    tmp.pop_back();
                }
                else break;
            }

            std::string spaces = "";
            for (int j = g_char_count[g_line]; j <= g_max_width; j++) {
                spaces += ' ';
                g_char_count[g_line]++;
            }
            tmp += spaces;

            tmp += g_text[i];
            g_char_count[g_line]++;
        }
        else if (g_text[i] == '\n') {
            g_line++;
            vector_assign(g_char_count, g_line, 0);
            tmp += '\n';
        }
        else {
            g_char_count[g_line]++;
            tmp += g_text[i];
        }
    }
    g_text = tmp;
}