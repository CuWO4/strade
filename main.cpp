#define extern_
#include "include/data.h"
#undef extern_
#include "include/console.h"
#include "include/preprocess.h"
#include "include/transform.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

// #define DEBUG

static void initialize(void) {
	g_source_file = nullptr;
	g_target_file = nullptr;

	g_line = 1;
	g_max_line = 0;
	g_char_count = nullptr;
	g_space_count = nullptr;
	g_text = "";

	g_max_width = 120;
}

static void aftermath(void) {
	fclose(g_source_file);
	fclose(g_target_file);
	delete[] g_char_count;
	delete[] g_space_count;
}


int main(int argc, char **argv) {
	initialize();

	#ifdef DEBUG
		g_source_file = fopen("preprocess.cpp", "r+");
		g_target_file = fopen("sample", "w+");
	#else
		console(argc, argv);
	#endif

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