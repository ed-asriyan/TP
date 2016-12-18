#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>

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

/**
 * @brief Appends (concatenates) *source and str.
 * @param source Pointer to the left (and resulting) string.
 * @param The number of characters from the source beginning to process.
 * @param str Pointer to the right string.
 * @param str_len The number of characters from the str beginning to process.
 * @return 1 if operation is completed; otherwise 0.
 *
 * Usage:
 *  char* s1 = (char*)malloc(sizeof(char) * 5);
 *  strcpy(s1, "abcd");
 *  char* s2 = (char*)malloc(sizeof(char) * 10);
 *  strcpy(s2, "123456789");
 *  if (append_str(&s1, INTMAX, s2, 3)) {
 *  	printf("%s", s1); // abcd123
 *  } else {
 *  	printf("[ error ]");
 *  }
 *  free(s2);
 *  free(s1);
 */
int append_str(char** source, size_t source_len, const char* str, size_t str_len) {
	if (source == NULL) {
		return 0;
	}

	size_t source_length = *source == NULL ? 0 : strlen(*source);
	source_len = MIN(source_length, source_len);

	size_t string_len = str == NULL ? 0 : strlen(str);
	str_len = MIN(string_len, str_len);
	if (str_len == 0) {
		return 1;
	}

	char* new_source = (char*) realloc(*source, sizeof(char) * (source_len + str_len + 1));
	if (new_source == NULL) {
		return 0;
	}
	memcpy(new_source + source_len, str, str_len);
	new_source[source_len + str_len] = '\0';

	*source = new_source;
	return 1;
}

/**
 * @brief Returns substring beginnings by begin index & ends by end index.
 * @param source Source string.
 * @param begin Beginning index.
 * @param end Ending index.
 * @return Substring beginnings by begin index & ends by end index.
 *
 * Usage:
 *  const char* s = "abcdef";
 *  char* sub_s = sub_str(s, 1, 4);
 *  if (sub_s != NULL) {
 *  	printf("%s", sub_s); // bcd
 *  	free(sub_s);
 *  }
 */
char* sub_str(const char* source, size_t begin, size_t end) {
	if (source == NULL) {
		return NULL;
	}

	size_t length = end - begin;
	char* result = (char*) malloc(sizeof(char) * (length + 1));
	if (result == NULL) {
		return NULL;
	}
	memcpy(result, source + begin, length);
	result[length] = '\0';
	return result;
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
		if (str[0] == '`') break;
		add_string_vector(vector, str);
	}
	return vector;
}

// ---------------------------------------------------------

int cmp_str_begin(char* a, char* b) {
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);
	size_t len = MIN(a_len, b_len);
	for (size_t i = 0; i < len; ++i) {
		if (a[i] != b[i]) {
			return 0;
		}
	}
	return 1;
}

int is_open_tag(const char* s) {
	return cmp_str_begin(s, "<div>") * 5;
}

int is_close_tag(const char* s) {
	return cmp_str_begin(s, "</div>") * 6;
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

const char** div_format(const char** s) {
	string_vector_t* vector = create_string_vector();

	char* str = NULL;
	int level = 0;

	while (*s != NULL) {
		size_t begin_pos = 0;
		size_t end_pos = 0;
		size_t s_len = strlen(*s);

		for (size_t i = 0; i < s_len;) {
			if (level < 0) {
				assert(0);
			}
			if (is_open_tag(*s + i)) {
				begin_pos = i += 5;
				++level;
			} else if (is_close_tag(*s + i)) {
//				str = append_str(str, *s + begin_pos, i - begin_pos);
				end_pos = i += 6;
				--level;
				str = NULL;
			} else {
				++i;
			}
		}

		++s;
	}
	add_string_vector(vector, str);
	return extract_buffer(vector);
}

int main() {
	char* s;
	char* d;
	if (!get_line(stdin, &s)) assert(0);
	if (!get_line(stdin, &d)) assert(0);

	printf("%s|\n", s);
	char* ss = s;
	const size_t i = skip_space((const char**) (&ss));
	ss[i] = '\0';
	printf("%s|\n", ss);

	printf("%s|\n", d);
	char* dd = d;
	const size_t j = skip_space((const char**) (&dd));
	dd[j] = '\0';
	printf("%s|\n", dd);

	append_str(&s, ULLONG_MAX, dd, ULONG_MAX);
	printf("%s|\n", s);

	free(d);
	free(s);

	return 0;

	string_vector_t* vector = scan_string_vector(stdin);
	char** input = extract_buffer(vector);

	char** output = div_format(input);
	print_string_buffer(stdout, output);

	free_buffer(output);
	free_buffer(input);

	return 0;
}