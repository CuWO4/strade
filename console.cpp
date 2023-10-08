#include "include/console.h"
#include "include/data.h"

#include <iostream>
#include <string.h>

#define is_digit(c) (c >= '0' && c <= '9')
static int string_to_int(std::string s) {
    int res = 0;
    for(unsigned i = 0; i < s.length(); i++) {
        if (!is_digit(s[i])) return 0;  /* here is different from atoi(). atoi("1a") = 1, string_to_int("1a") = 0. */
        res = res * 10 + s[i] - '0';
    }
    return res;
}

void console(int argc, char **argv) {
    std::string source_file_name = "";

    try {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-o") == 0) {
                i++;
                if (i >= argc)
                    throw std::string("Cannot find argument for option \"-o\"!");

                g_target_file = fopen(argv[i], "w+");
            }
            else if (strcmp(argv[i], "-w") == 0) {
                i++;
                if (i >= argc) 
                    throw std::string("Cannot find argument for option \"-w\"!");
                
                g_max_width = string_to_int(argv[i]);
                if (g_max_width == 0) {
                    std::string error_info = "Invalid argument \"";
                    error_info += argv[i];
                    error_info += "\" for option \"-w\"!";
                    throw error_info;
                }
            }
            else {
                if (g_source_file != nullptr) {
                    std::string error_info = "Unknown option \"";
                    error_info += argv[i];
                    error_info += "\"!";
                    throw error_info;
                }

                g_source_file = fopen(argv[i], "r");
                if (g_source_file == nullptr) {
                    std::string error_info = "Failed to open the source file \"";
                    error_info += argv[i]; 
                    error_info += "\"!";
                    throw error_info;
                }
                source_file_name = argv[i];
            }
        }

        if (g_source_file == nullptr) 
            throw std::string("No source file specified!");

        if (g_target_file == nullptr) { /* default taget file */
            bool has_suffix = false;
            for (unsigned i = 0; i < source_file_name.length(); i++) {
                if (source_file_name[i] == '.') {
                    source_file_name.insert(i, "-strade");
                    has_suffix = true;
                    break;
                }
            }
            if (!has_suffix) 
                source_file_name += "-strade";
            g_target_file = fopen(source_file_name.c_str(), "w+");
        }
    }
    catch (const std::string s) {
        std::cerr << s << std::endl;
        exit(-1);
    }
}