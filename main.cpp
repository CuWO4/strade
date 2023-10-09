#define extern_
#include "include/data.h"
#undef extern_
#include "include/console.h"
#include "include/preprocess.h"
#include "include/transform.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

static void initialize(void) {
	g_source_file = nullptr;
	g_target_file = nullptr;

	g_line = 1;
	g_char_count.reserve(1);
	g_char_count[1] = 0; 
	g_text = "";

	g_max_width = 120;
}

static void aftermath(void) {
	fclose(g_source_file);
	fclose(g_target_file);
}


int main(int argc, char **argv) {
	initialize();

	console(argc, argv);

	for (char ch; (ch = fgetc(g_source_file)) != EOF;) {
		g_text += ch;
	}

	preprocess();

	transform();

	for (unsigned i = 0; i < g_text.length(); i++) {
		fputc(g_text[i], g_target_file);
	}

	aftermath();

	return 0;
}