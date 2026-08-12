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

/* == sine constants == */

const int _sine_version = 1;
const int _sine_max_cells = 2048;
const int _sine_max_counters = 2048;
const int _sine_cell_size = 512;

/* == sine static functions == */

static
void _sine_show_usage(void) {
	puts("[sine usage]");
	puts("- sine _run [pattern]");
	puts("- sine _help");
	puts("- sine _version");
}

static
void _sine_show_version(void) {
	fprintf(
		stdout,
		"[sine %04d]\n",
		_sine_version
	);
}

static
void _sine_show_error(int ref) {
	char *text = NULL;

	switch (ref) {
case 1: text = "too many arguments."; break;
case 2: text = "unknown option."; break;
case 3: text = "too many files."; break;
case 4: text = "file is unreachable."; break;
default:
	text = "unknown error reference.";
	break;
	}

	fputs("! ", stderr);
	fputs(text, stderr);
	fputc('\n', stderr);
	exit(EXIT_FAILURE);
}

static
void _sine_run_pattern(int argc, char **argv) {
	switch (argc) {
		case 3: break;
		default:
			_sine_show_error(3);
			break;
	}

	FILE *stream = fopen(argv[2], "rb");

	if (stream == NULL)
		_sine_show_error(4);

	int ch = '\0';
	int prev_ch = '\0';
	int cur_cell = 0;
	int cur_counter = 0;
	int just_ignored = 0;
	int ignored = 0;
	char cells
		[_sine_max_cells]
		[_sine_cell_size];

	void *subject = NULL;
	void *object = NULL;

	register uint32_t counters
		[_sine_max_counters];

	for (
		int i = 0;
		i < _sine_max_cells;
		i++
	) { memcpy(cells[i], "", 1); }

	for (
		int i = 0;
		i < _sine_max_counters;
		i++
	) { counters[i] = 0; }

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

	counters[cur_counter]++;
	break;
case '@':
	if (ignored) { goto ending; }

	counters[cur_counter] += 4;
	break;
case '!':
	if (ignored) { goto ending; }

	counters[cur_counter]--;
	break;
case ';':
	if (ignored) { goto ending; }

	counters[cur_counter] -= 4;
	break;
case '%': {
	if (ignored) { goto ending; }

	char *str = cells[cur_cell];
	int len = strlen(str);
	str[len++] = prev_ch;
	str[len] = '\0';
	break;
} case '^': {
	if (ignored) { goto ending; }

	char *str = cells[cur_cell];
	str[strlen(str) - 1] = '\0';
	break;
} case '#': {
	if (ignored) { goto ending; }

	int counter = counters[cur_counter];
	char data[256];
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
		cells[cur_cell],
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

#ifdef _sine_exe
void main(int argc, char **argv) {
	sine_exec(argc, argv);
	exit(EXIT_SUCCESS);
}
#endif /* _sine_exe */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _sine_c */
