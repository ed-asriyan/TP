#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_RESIZE_FACTOR 2

// --- get_line ---------------------------------------------

size_t get_line(FILE* input, char** result) {
	if (input == NULL || result == NULL) {
		return 0;
	}

	char* str = (char*) malloc(sizeof(char));
	size_t buffer_size = 1;
	size_t size = 0;

	char c;
	while (fscanf(input, "%c", &c) == 1 && c != '\n') {
		if (++size == buffer_size) {
			str = (char*) realloc(str, sizeof(char) * ((buffer_size *= BUFFER_RESIZE_FACTOR) + 1));
		}
		str[size - 1] = c;
	}

	str[size] = '\0';
	*result = str;
	return size;
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