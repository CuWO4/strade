#define extern_
#include "include/data.h"
#undef extern_
#include "include/console.h"
#include "include/preprocess.h"

#include <iostream>
#include <stdlib.h>
#include <string.h>

static void initialize(void) {
	g_source_file = nullptr;
	g_target_file = nullptr;

	g_line = 0;
	g_char_count.push_back(0);  /* index of g_char_count starts from 1, g_char_count[0] is not used. */

	g_max_width = 100;
}

static void aftermath(void) {
	fclose(g_source_file);
	fclose(g_target_file);

	remove(TEMPORARY_INTERMEDIATE_FILE_NAME);
}


int main(int argc, char **argv) {
	initialize();

	console(argc, argv);

	preprocess();

	aftermath();

	return 0;
}