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

#define _sine_version		(9)
#define _sine_file_extension	(".sn")
#define _sine_max_cells		(2048)
#define _sine_max_counters	(2048)
#define _sine_max_runs		(64)
#define _sine_file_data_size	(2048)
#define _sine_cell_size		(512)
#define _sine_data_size		(256)

#define _sine_check \
switch (prev_ch) { \
	case '\\': goto ending; \
	default: break; \
} \
\
switch (condition_res) { \
	case 0: \
		if (!in_condition) \
		{ break; } \
		\
		goto ending; \
	case 1: break; \
}

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
	puts("\tsine _ver");
	puts("}");
}

static
void _sine_show_version(void) {
	fprintf(
		stdout,
		"[sine: version]\n"
		"{ %03d }\n",
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
case 9:
	text = "cannot stack condition.";
	break;
case 10:
	text = "no condition could"
		"be terminated.";

	break;
case 11:
	text = "unterminated condition.";
	break;
case 12:
	text = "too many characters to be"
		"processed.";
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
		memcmp(
strrchr(argv[2], '.'),
_sine_file_extension,
strlen(_sine_file_extension) + 1
		) != 0
	) {
		case 0: break;
		case 1:
			_sine_show_error(6);
			break;
	}

	char file_data[_sine_file_data_size];
	int file_len = 0;
	int file_idx = 0;
	int ch = '\0';
	int prev_ch = '\0';
	int cur_cell = 0;
	int cur_counter = 0;
	int in_condition = 0;
	int condition_res = 0;
	void *subject = NULL;
	void *object = NULL;

	while ((ch = getc(stream)) != EOF) {
		switch (file_len) {
case _sine_file_data_size:
	_sine_show_error(12);
default: break;
		}

		file_data[file_len++] = ch;
		file_data[file_len] = '\0';
	}

	while (file_idx < file_len) {
		ch = file_data[file_idx];

		switch (ch) {
case '*':
	_sine_check

	cur_cell++;

	switch (cur_cell) {
		case _sine_max_cells:
			cur_cell = 0;
			break;
		default: break;
	}

	break;
case '&':
	_sine_check

	cur_cell--;

	switch (cur_cell) {
		case -1:
			cur_cell =
			_sine_max_cells - 1;
			break;
		default: break;
	}

	break;
case '>':
	_sine_check

	cur_counter++;

	switch (cur_counter) {
		case _sine_max_counters:
			cur_counter = 0;
		default: break;
	}

	break;
case '<':
	_sine_check

	cur_counter--;

	switch (cur_counter) {
		case -1:
cur_counter =
_sine_max_counters - 1;
break;
		default: break;
	}

	break;
case '$':
	_sine_check

	sine_counters[cur_counter]++;
	break;
case '@':
	_sine_check

	sine_counters[cur_counter] += 4;
	break;
case '!':
	_sine_check

	sine_counters[cur_counter]--;
	break;
case ';':
	_sine_check

	sine_counters[cur_counter] -= 4;
	break;
case '%': {
	_sine_check

	char *str = sine_cells[cur_cell];
	int len = strlen(str);

	switch (len + 1 >= _sine_cell_size) {
		case 0: break;
		case 1: goto ending;
	}

	str[len++] = prev_ch;
	str[len] = '\0';
	break;
} case '^': {
	_sine_check

	char *str = sine_cells[cur_cell];

	switch (*str) {
		case '\0': goto ending;
		default: break;
	}

	str[strlen(str) - 1] = '\0';
	break;
} case '-': {
	 _sine_check

	char *str = sine_cells[cur_cell];

	switch (*str) {
		case '\0': goto ending;
		default: break;
	}

	char *temp = strchr(str, *str) + 1;

	memcpy(
		sine_cells[cur_cell],
		temp,
		strlen(temp) + 1
	);

	break;
} case '+': {
	_sine_check

	char *str = sine_cells[cur_cell];

	char temp[_sine_cell_size] = {
		prev_ch,
		'\0',
	};

	strncat(
		temp,
		str,
		_sine_cell_size -
		strlen(str) - 1
	);

	memcpy(str, temp, strlen(temp) + 1);
} case '#': {
	_sine_check

	int_fast8_t counter =
		sine_counters[cur_counter];

	char data[_sine_data_size];
	int i = 0;

	switch (counter < 0) {
		case 0: break;
		case 1:
			data[i++] = '-';
			counter = -counter;
			break;
	}

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
	_sine_check

	fputs(
		sine_cells[cur_cell],
		stdout
	);

	break;
case ',':
	_sine_check

	fputc(prev_ch, stdout);
	break;
case '\'':
	_sine_check

	subject = sine_cells[cur_cell];
	break;
case '"':
	_sine_check

	object = sine_cells[cur_cell];
	break;
case ':':
	switch (prev_ch) {
		case '\\': goto ending;
		default: break;
	}

	switch (in_condition) {
		case 0: break;
		case 1: _sine_show_error(9);
	}

	in_condition = 1;

	condition_res = memcmp(
		subject,
		object,
		strlen(object) + 1
	) == 0;

	break;
case '?':
	switch (prev_ch) {
		case '\\': goto ending;
		default: break;
	}

	switch (in_condition) {
		case 0: break;
		case 1: _sine_show_error(9);
	}

	in_condition = 1;

	condition_res = memcmp(
		subject,
		object,
		strlen(object) + 1
	) != 0;

	break;
case '}':
	switch (prev_ch) {
		case '\\': goto ending;
		default: break;
	}

	switch (in_condition) {
		case 0: _sine_show_error(10);
		case 1: break;
	}

	in_condition = 0;
	condition_res = 0;
	break;
case ']':
	_sine_check

	sine_counters[cur_counter] =
		file_idx;

	break;
case '[':
	_sine_check

	file_idx =
		sine_counters[cur_counter];

	in_condition = 0;
	condition_res = 0;

	break;
case '~':
	_sine_check

	goto cleaning;
case '/': {
	_sine_check

	int_fast8_t counter =
		sine_counters[cur_counter];

	char data[_sine_data_size];
	int i = 0;

	switch (counter < 0) {
		case 0: break;
		case 1:
			data[i++] = '-';
			counter = -counter;
			break;
	}

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

	memcpy(
		sine_cells[cur_cell],
		data,
		sizeof(data)
	);

	break;
} case '`': {
	static int used = 0;
	static int dest_cell = 0;
	static int src_cell = 0;

	_sine_check

	switch (used) {
		case 0:
			used = 1;
			src_cell = cur_cell;
			break;
		case 1:
			used = 0;
			dest_cell = cur_cell;

memcpy(
	sine_cells[dest_cell],
	sine_cells[src_cell],
	strlen(sine_cells[src_cell]) + 1
);

			break;
	}

	break;
} case '\\':
	_sine_check
	break;
		}

ending:
		prev_ch = ch;
		++file_idx;
	}

	switch (in_condition) {
		case 0: break;
		case 1: _sine_show_error(11);
	}

cleaning:
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
	char *cur_option = "_run";

	switch (
		memcmp(
			option,
			cur_option,
			strlen(cur_option) +
			1
		) == 0
	) {
		case 0: break;
		case 1:
			_sine_run_pattern(
				argc,
				argv
			);

			return;
	}

	cur_option = "_ver";

	switch (
		memcmp(
			option,
			cur_option,
			strlen(cur_option) +
			1
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
