#include <stdio.h>
#include <stdlib.h>
#include "../../sine.c"

void main(void) {
	int sine_argc = 3;

	char *sine_argv[] = {
		NULL,
		"_run",
		"main-pattern"
	};

	sine_exec(sine_argc, sine_argv);

	printf(
		"1. %d\n2. %d\n3. %d\n",
		sine_counters[0],
		sine_counters[1],
		sine_counters[2]
	);

	exit(EXIT_SUCCESS);
}
