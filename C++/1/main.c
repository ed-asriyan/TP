#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

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
				return 0;
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

	size_t string_len = str == NULL ? 0 : strlen(str);
	str_len = MIN(string_len, str_len);
	if (str_len == 0) {
		return 1;
	}

	size_t source_length = *source == NULL ? 0 : strlen(*source);
	source_len = MIN(source_length, source_len);

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

/**
 * @brief Increases vector buffer by N times.
 * @param vector Pointer to vector instance.
 * @return 1 if operation is completed; otherwise 0;
 */
int resize_string_vector(string_vector_t* vector) {
	if (vector == NULL) {
		return 0;
	}

	const int RESIZE_FACTOR = 2;
	size_t new_buffer_size = vector->buffer_size * RESIZE_FACTOR;
	if (!new_buffer_size) {
		new_buffer_size = RESIZE_FACTOR;
	}
	char** new_buffer = (char**) realloc(vector->buffer, sizeof(char*) * (new_buffer_size));
	if (new_buffer == NULL) {
		return 0;
	}
	vector->buffer = new_buffer;
	vector->buffer_size = new_buffer_size;


	// remaining no-initialized items
	for (size_t i = vector->size; i < vector->buffer_size; ++i) {
		vector->buffer[i] = NULL;
	}

	return 1;
}

/**
 * @brief Adds string to the vector: push back;
 * @param vector Pointer to vector instance.
 * @param str Pointer to the initial position in the string.
 * @return 1 if operation is completed; otherwise 0;
 */
int add_string_vector(string_vector_t* vector, char* str) {
	if (vector == NULL) return 0;
	if (vector->size + 1 >= vector->buffer_size) {
		if (!resize_string_vector(vector)) {
			return 0;
		}
	}

	if (str == NULL) {
		str = (char*) malloc(sizeof(char));
		if (str == NULL) {
			return 0;
		}
		*str = '\0';
	}

	vector->buffer[vector->size++] = str;
	return 1;
}

/**
 * @brief Destroys vector instance & returns buffer.
 * @param vector Pointer to vector instance.
 * @return Pointer to the vector buffer.
 */
char** extract_buffer(string_vector_t* vector) {
	char** result = vector->buffer;
	free(vector);
	return result;
}

/**
 * @brief Destroys vector buffer.
 * @param buffer Pointer to the buffer.
 */
void free_buffer(char** buffer) {
	for (size_t i = 0; buffer[i] != NULL; ++i) {
		free(buffer[i]);
	}
	free(buffer);
}

/**
 * @brief Destroys vector.
 * @param vector Pointer to vector instance.
 */
void free_string_vector(string_vector_t* vector) {
	free_buffer(extract_buffer(vector));
}

/**
 * @brief Creates new vector instance.
 * @return if operation is completed, pointer to vector instance; otherwise NULL.
 */
string_vector_t* create_string_vector() {
	string_vector_t* vector = (string_vector_t*) malloc(sizeof(string_vector_t));
	if (vector == NULL) {
		return NULL;
	}

	vector->buffer = (char**) malloc(sizeof(char*));
	if (vector->buffer == NULL) {
		free(vector);
		return NULL;
	}
	vector->buffer[0] = NULL;
	vector->buffer_size = 1;
	vector->size = 0;

	resize_string_vector(vector);

	return vector;
}

/**
 * @brief Prints buffer items to the out.
 * @param out Output stream.
 * @param buffer Pointer to the buffer.
 */
void print_string_buffer(FILE* out, char** buffer) {
	if (out == NULL || buffer == NULL) return;

	while (*buffer != NULL) {
		fprintf(out, "%s\n", *buffer);
		++buffer;
	}
}

/**
 * @brief Prints vector items to the out.
 * @param out Output stream.
 * @param vector Pointer to the vector.
 */
void print_string_vector(FILE* out, const string_vector_t* vector) {
	if (out == NULL || vector == NULL) return;;

	print_string_buffer(out, vector->buffer);
}

/**
 * @brief Scans items from the out to the vector.
 * @param in Input stream.
 * @return If operation is completed, pointer to the vector instance; otherwise NULL.
 */
string_vector_t* scan_string_vector(FILE* in) {
	string_vector_t* vector = create_string_vector();
	if (vector != NULL) {
		while (!feof(in)) {
			char* str;
			get_line(in, &str);
			add_string_vector(vector, str);
		}
	}
	return vector;
}

// ---------------------------------------------------------

int cmp_str_begin(const char* a, const char* b) {
	size_t a_len = strlen(a);
	size_t b_len = strlen(b);

	if (a_len < b_len) {
		return 0;
	}
	for (size_t i = 0; i < b_len; ++i) {
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
size_t skip_space(const char** str, size_t length) {
	if (str == NULL || *str == NULL || **str == '\0') {
		return 0;
	}

	// detecting beginning of the string
	const char* s = *str;
	while (*s++ == ' ') {
		--length;
	}
	const char* const begin = s - 1;

	// detecting end of the string
	s = begin + (length - 1);
	while (length > 0 && *s == ' ') {
		--length;
		--s;
	}

	*str = begin;
	return length;
}

char** div_format(const char** s) {
	const size_t OFFSET = 4;

	string_vector_t* vector = create_string_vector();

	char* current_str = NULL;
	int level = 0;
	int is_empty = 1; // determines whether current_str contains one useful character at least

	while (*s != NULL) {
		size_t begin_pos = 0;
		const char* str = *s;
		size_t str_len = strlen(*s);

		for (size_t i = 0; i < str_len;) {
			// on any tag:
			// 1. add remaining string part to the current_str;
			// 2. add current_str to the vector;
			// 3. clean current_str;
			// 4. set is_empty = 1 (because of 3);
			// 5. add tag to the vector;
			// 6. increase or decrease level;
			// 7. move begin index;
			// 8. increase i by tag length;
			if (is_open_tag(str + i)) {
				// append current_str by data on current line
				const char* begin = str + begin_pos;
				size_t line_len = skip_space(&begin, i - begin_pos);
				append_str(&current_str, ULONG_MAX, begin, line_len);

				// if current_str contains useful characters add it to the vector
				// and reset current_str & is_empty = 1
				if (!is_empty) {
					add_string_vector(vector, current_str);
					current_str = NULL;
					is_empty = 1;
				} else {
					free(current_str);
				}

				// add open tag to the vector
				char* tag = (char*) malloc(sizeof(char) * (level * OFFSET + 6));
				memset(tag, ' ', OFFSET * level);
				memcpy(tag + (level * OFFSET), "<div>", 5);
				tag[level * OFFSET + 5] = '\0';
				add_string_vector(vector, tag);

				// increase level
				++level;

				// add offset to the current_str beginning
				current_str = (char*) malloc(sizeof(char) * (level * OFFSET + 1));
				memset(current_str, ' ', OFFSET * level);
				current_str[OFFSET * level] = '\0';

				begin_pos = i += 5;
			} else if (is_close_tag(str + i)) {
				// decrease level
				--level;

				// check for level
				if (level < 0) {
					free(current_str);
					free_string_vector(vector);
					vector = create_string_vector();
					char* error = (char*) malloc(sizeof(char) * 8);
					strcpy(error, "[error]");
					add_string_vector(vector, error);
					return extract_buffer(vector);
				}

				// if current_str contains useful characters add it to the vector
				// and reset current_str & is_empty = 1
				if (!is_empty) {
					const char* begin = str + begin_pos;
					size_t line_len = skip_space(&begin, i - begin_pos);
					append_str(&current_str, ULONG_MAX, begin, line_len);
					add_string_vector(vector, current_str);
					is_empty = 1;
				} else {
					free(current_str);
				}

				// add offset to the current_str beginning
				// if no level offset is not necessary
				if (level) {
					current_str = (char*) malloc(sizeof(char) * (level * OFFSET + 1));
					memset(current_str, ' ', level * OFFSET);
					current_str[level * OFFSET] = '\0';
				} else {
					current_str = NULL;
					is_empty = 1;
				}

				// add close tag to the vector
				char* tag = (char*) malloc(sizeof(char) * (level * OFFSET + 7));
				memset(tag, ' ', OFFSET * level);
				memcpy(tag + (level * OFFSET), "</div>", 6);
				tag[level * OFFSET + 6] = '\0';
				add_string_vector(vector, tag);

				begin_pos = i += 6;
			} else {
				// on general character:
				// 1. update is_empty state;
				// 2. increase i by 1;
				if (is_empty) {
					is_empty = str[i] == ' ';
				}
				++i;
			}
		}

		// 'if' block for empty line safety
		if (!is_empty) {
			const char* begin = str + begin_pos;
			size_t line_len = skip_space(&begin, str_len - begin_pos);
			append_str(&current_str, ULONG_MAX, begin, line_len);
			add_string_vector(vector, current_str);
			is_empty = 1;

			// add offset to the current_str beginning
			current_str = (char*) malloc(sizeof(char) * (level * OFFSET + 1));
			memset(current_str, ' ', OFFSET * level);
			current_str[OFFSET * level] = '\0';
		}
		++s;
	}

	if (level) {
		free(current_str);
		free_string_vector(vector);
		vector = create_string_vector();
		char* error = (char*) malloc(sizeof(char) * 8);
		strcpy(error, "[error]");
		add_string_vector(vector, error);
		return extract_buffer(vector);
	}

	add_string_vector(vector, current_str);

	return extract_buffer(vector);
}

int main() {
	string_vector_t* vector = scan_string_vector(stdin);
	char** input = extract_buffer(vector);

	char** output = div_format((const char**) input);
	print_string_buffer(stdout, output);

	free_buffer(output);
	free_buffer(input);

	return 0;
}