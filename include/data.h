#ifndef DATA_H
#define DATA_H

#ifndef extern_
    #define extern_ extern
#endif

#include <iostream>
#include <vector>

extern_ FILE    *g_source_file;
extern_ FILE    *g_target_file;

extern_ int     g_line;
extern_ int     g_max_line;
extern_ int    *g_char_count;   /* count of characters on each line. start from 1. */
extern_ int    *g_space_count;  /* count of characters on each line. start from 1. */
extern_ std::string         g_text;

extern_ int     g_max_width;

#endif /* DATA_H */