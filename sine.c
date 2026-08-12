#ifndef _sine_c
#define _sine_c

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* == sine dependencies == */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>

/* == sine constants == */

#define _sine_version		(2)
#define _sine_file_extension	(".sn")
#define _sine_max_cells		(2048)
#define _sine_max_counters	(2048)
#define _sine_max_runs		(64)
#define _sine_cell_size		(512)
#define _sine_data_size		(256)

/* == sine static variables == */

static
int _sine_runs_count = 0;

/* == sine global variables == */

char sine_cells
	[_sine_max_cells][_sine_cell_size];

int_fast8_t sine_counters
	[_sine_max_counters];

/* == sine static
	functions declarations == */

static
void _sine_show_usage(void);

static
void _sine_show_version(void);

static
void _sine_show_error(int ref);

static
void _sine_run_pattern(
	int argc,
	char **argv
);

/* == sine global
	functions declarations == */

void sine_exec(int argc, char **argv);

/* == sine static functions == */

static
void _sine_show_usage(void) {
	puts("[sine: usage] {");
	puts("\tsine _run <pattern-file>");
	puts("\tsine _help");
	puts("\tsine _version");
	puts("}");
}

static
void _sine_show_version(void) {
	fprintf(
		stdout,
		"[sine: version]\n"
		"{ %02d }\n",
		_sine_version
	);
}

static
void _sine_show_error(int ref) {
	char *text = NULL;

	switch (ref) {
case 1: text = "too many arguments."; break;
case 2: text = "unknown option."; break;
case 3: text = "too few arguments."; break;
case 4: text = "too many files."; break;
case 5: text = "file is unreachable."; break;
case 6:
	text = "unsupported file type.";
	break;
case 7: text = "too many runs."; break;
case 8:
	text = "stack overflows.";
	break;
default:
	text = "unknown error reference.";
	break;
	}

	fputs("[sine: error]\n{ ", stderr);
	fputs(text, stderr);
	fputs(" }\n", stderr);
	exit(EXIT_FAILURE);
}

static
void _sine_run_pattern(int argc, char **argv)
{
	switch (argc < 0) {
		case 0: break;
		case 1:
			argc = -argc;
			break;
	}

	switch (argc) {
		case 0:
		case 1:
		case 2:
			_sine_show_error(3);
			break;
		case 3: break;
		default:
			_sine_show_error(4);
			break;
	}

	register
	FILE *stream = fopen(argv[2], "rb");

	switch (stream == NULL) {
		case 0: break;
		case 1:
			_sine_show_error(5);
			break;
	}

	switch (
		strcmp(
strrchr(argv[2], '.'),
_sine_file_extension
		) != 0
	) {
		case 0: break;
		case 1:
			_sine_show_error(6);
			break;
	}

	int ch = '\0';
	int prev_ch = '\0';
	int cur_cell = 0;
	int cur_counter = 0;
	int just_ignored = 0;
	int ignored = 0;

	for (
		int i = 0;
		i < _sine_max_cells;
		i++
	) { memcpy(sine_cells[i], "", 1); }

	for (
		int i = 0;
		i < _sine_max_counters;
		i++
	) { sine_counters[i] = 0; }

	while ((ch = getc(stream)) != EOF) {
		just_ignored = 0;

		switch (ch) {
case '*':
	if (ignored) { goto ending; }

	cur_cell++;
	break;
case '&':
	if (ignored) { goto ending; }

	cur_cell--;
	break;
case '>':
	if (ignored) { goto ending; }

	cur_counter++;
	break;
case '<':
	if (ignored) { goto ending; }

	cur_counter--;
	break;
case '$':
	if (ignored) { goto ending; }

	sine_counters[cur_counter]++;
	break;
case '@':
	if (ignored) { goto ending; }

	sine_counters[cur_counter] += 4;
	break;
case '!':
	if (ignored) { goto ending; }

	sine_counters[cur_counter]--;
	break;
case ';':
	if (ignored) { goto ending; }

	sine_counters[cur_counter] -= 4;
	break;
case '%': {
	if (ignored) { goto ending; }

	char *str = sine_cells[cur_cell];
	int len = strlen(str);
	str[len++] = prev_ch;
	str[len] = '\0';
	break;
} case '^': {
	if (ignored) { goto ending; }

	char *str = sine_cells[cur_cell];
	str[strlen(str) - 1] = '\0';
	break;
} case '#': {
	if (ignored) { goto ending; }

	int8_t counter =
		sine_counters[cur_counter];
	char data[_sine_data_size];
	int i = 0;


	do {
		data[i++] =
			(counter % 10) + '0';

		counter /= 10;
	} while (counter != 0);

	data[i++] = '\0';

	char *data_ptr = data;

	char *reversed_ptr =
		data + strlen(data) - 1;

	while (data_ptr < reversed_ptr) {
		char temp = *data_ptr;
		*data_ptr++ = *reversed_ptr;
		*reversed_ptr = temp;
	}

	fputs(data, stdout);
	break;
} case '.':
	if (ignored) { goto ending; }

	fputs(
		sine_cells[cur_cell],
		stdout
	);

	break;
case ',':
	if (ignored) { goto ending; }

	fputc(prev_ch, stdout);
	break;
case '\\':
	if (ignored) { goto ending; }

	just_ignored = 0;
	ignored = 1;
	continue;
case '=':
	if (ignored) { goto ending; }

	if (
		_sine_runs_count
		>=
		_sine_max_runs
	) { _sine_show_error(7); }

	int sine_argc = 3;

	char *sine_argv[] = {
		NULL,
		NULL,
		sine_cells[cur_cell]
	};

	++_sine_runs_count;

	_sine_run_pattern(
		sine_argc,
		sine_argv
	);

	break;
		}

ending:
		switch (just_ignored) {
			case 0:
				ignored = 0;
				break;
			case 1: break;
		}

		prev_ch = ch;
	}

	if (_sine_runs_count > 0)
	{ ++_sine_runs_count; }

	fclose(stream);
}

/* == sine global functions == */

void sine_exec(int argc, char **argv) {
	switch (argc) {
		case 1:
			_sine_show_usage();
			return;
		default: break;
	}

	if (argc > 3) _sine_show_error(1);

	char *option = argv[1];

	switch (strcmp(option, "_run") == 0)
	{
		case 0: break;
		case 1:
			_sine_run_pattern(
				argc,
				argv
			);

			return;
	}

	switch (strcmp(option, "_help") == 0)
	{
		case 0: break;
		case 1:
			_sine_show_usage();
			return;
	}

	switch (
		strcmp(
			option,
			"_version"
		) == 0
	) {
		case 0: break;
		case 1:
			_sine_show_version();
			return;
	}

	_sine_show_error(2);
}

/* == sine main functions */

#ifdef _sine_exe

static
void _sine_signal(int signum) {
	switch (signum != SIGSEGV) {
		case 0: return;
		case 1: break;
	}

	_sine_show_error(8);
}

void main(int argc, char **argv) {
	signal(SIGSEGV, _sine_signal);
	sine_exec(argc, argv);
	exit(EXIT_SUCCESS);
}

#endif /* _sine_exe */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _sine_c */
