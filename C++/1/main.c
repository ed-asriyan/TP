#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define BUFFER_RESIZE_FACTOR 2

// --- string helpers ---------------------------------------------

/**
 * @brief Reads line from the stream input.
 * @param input Input stream.
 * @param result Pointer to the pointer to the result line.
 * @return Line length.
 *
 * Reads line from the stream input. On memory error *result = NULL.
 *
 * Usage:
 *  char* c;
 *  get_line(stdin, &c);
 *  if (c != NULL) {
 *  	printf("%s", c);
 *  	free(c);
 *  } else  {
 *  	printf("[ error ]");
 *  }
 */
size_t get_line(FILE* input, char** result) {
	const unsigned char RESIZE_FACTOR = 2;

	if (input == NULL || result == NULL) {
		return 0;
	}

	char* str = (char*) malloc(sizeof(char));
	if (str == NULL) {
		*result = NULL;
		return 0;
	}
	size_t buffer_size = 1;
	size_t size = 0;

	char c;
	while (fscanf(input, "%c", &c) == 1 && c != '\n') {
		if (++size == buffer_size) {
			char* new_str = (char*) realloc(str, sizeof(char) * ((buffer_size *= RESIZE_FACTOR) + 1));
			if (new_str == NULL) {
				free(str);
				*result = NULL;
				return NULL;
			}
			str = new_str;
		}
		str[size - 1] = c;
	}

	str[size] = '\0';
	*result = str;
	return size;
}

char* append_str(char* source, const char* str, size_t s_len) {
	size_t source_len = source == NULL ? 0 : strlen(source);
	size_t str_len = str == NULL ? 0 : strlen(str);
	str_len = MIN(s_len, str_len);
	source = (char*) realloc(source, sizeof(char) * (source_len + str_len + 1));
	memcpy(source + source_len, str, str_len);
	return source;
}

// --- StringVector -----------------------------------------

struct StringVector {
	char** buffer;
	size_t buffer_size;
	size_t size;
};

typedef struct StringVector string_vector_t;

int resize_string_vector(string_vector_t* vector) {
	if (vector == NULL) {
		return 0;
	}

	vector->buffer =
		(char**) realloc(vector->buffer, sizeof(char*) * ((vector->buffer_size *= BUFFER_RESIZE_FACTOR) + 1));
	for (size_t i = vector->size; i <= vector->buffer_size; ++i) {
		vector->buffer[i] = NULL;
	}

	return 1;
}

int add_string_vector(string_vector_t* vector, char* str) {
	if (vector == NULL) return 0;
	if (vector->size == vector->buffer_size) {
		resize_string_vector(vector);
	}

	vector->buffer[vector->size++] = str;
	return 1;
}

char** extract_buffer(string_vector_t* vector) {
	char** result = vector->buffer;
	free(vector);
	return result;
}

void free_buffer(char** buffer) {
	for (size_t i = 0; buffer[i] != NULL; ++i) {
		free(buffer[i]);
	}
	free(buffer);
}

void free_string_vector(string_vector_t* vector) {
	free_buffer(extract_buffer(vector));
}

string_vector_t* create_string_vector() {
	string_vector_t* vector = (string_vector_t*) malloc(sizeof(string_vector_t));
	if (vector == NULL) {
		return NULL;
	}

	vector->buffer = (char**) malloc(sizeof(char*));
	vector->buffer[0] = NULL;
	vector->buffer_size = 1;
	vector->size = 0;

	resize_string_vector(vector);

	return vector;
}

void print_string_buffer(FILE* out, char** buffer) {
	if (out == NULL || buffer == NULL) return;

	while (*buffer != NULL) {
		fprintf(out, "%s\n", *buffer);
		++buffer;
	}
}

void print_string_vector(FILE* out, const string_vector_t* vector) {
	if (out == NULL || vector == NULL) return;;

	print_string_buffer(out, vector->buffer);
}

string_vector_t* scan_string_vector(FILE* in) {
	string_vector_t* vector = create_string_vector();
	while (!feof(in)) {
		char* str;
		get_line(in, &str);
		add_string_vector(vector, str);
	}
	return vector;
}

// ---------------------------------------------------------

int cmp_str_begin(char* a, char* b) {
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);
	size_t len = MAX(a_len, b_len);
	for (size_t i = 0; i < len; ++i) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

int is_open_tag(char* s) {
	return cmp_str_begin(s, "<div>");
}

int is_close_tag(char* s) {
	return cmp_str_begin(s, "</div>");
}

/**
 * @brief Determines begin & end of the string by skipping white spaces.
 * @param str Pointer to the pointer to the initial position in the string to write in it new string beginning.
 * @return Filtered string length.
 */
size_t skip_space(const char** str) {
	if (str == NULL || *str == NULL || **str == '\0') {
		return 0;
	}

	// detecting beginning of the string
	const char* s = *str;
	while (*s++ == ' ');
	const char* const begin = s - 1;

	// detecting end of the string
	size_t length = strlen(begin);
	s = begin + (length - 1);
	while (*s == ' ' && length > 0) {
		--length;
		--s;
	}

	*str = begin;
	return length;
}

char** div_format(char** s) {
	string_vector_t* vector = create_string_vector();
	while (*s != NULL) {
		char* str = (char*) malloc(sizeof(char*) * (strlen(*s) + 1));
		strcpy(str, *s);
		add_string_vector(vector, str);
		++s;
	}
	return extract_buffer(vector);
}

int main() {
	string_vector_t* vector = scan_string_vector(stdin);
	char** input = extract_buffer(vector);

	char** output = div_format(input);
	print_string_buffer(stdout, output);

	free_buffer(output);
	free_buffer(input);

	return 0;
}