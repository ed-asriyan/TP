#include <stdlib.h>
#include <stdio.h>

#define BUFFER_RESIZE_FACTOR 2

// --- get_line ---------------------------------------------

size_t get_line(FILE* input, char** result) {
	if (input == NULL || result == NULL) {
		*result = NULL;
		return 0;
	}

	char* str = NULL;
	size_t buffer_size = 1;
	size_t size = 0;

	char c;
	while (fscanf(input, "%c", &c) == 1 && c != '\n') {
		if (++size == buffer_size) {
			str = (char*) realloc(str, sizeof(char) * (buffer_size *= BUFFER_RESIZE_FACTOR));
		}
		str[size - 1] = c;
	}

	*result = str;
	return size;
}

int main() {

	return 0;
}