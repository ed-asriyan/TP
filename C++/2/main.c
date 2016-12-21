#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// --- Help functions -----------------------------------------------

void skip_space(FILE* f) {
	while (!feof(f)) {
		char c;
		fscanf(f, "%c", &c);
		if (c != ' ') {
			fseek(f, -1, SEEK_CUR);
			return;
		}
	}
}

// --- Vector ------------------------------------------------------

struct Vector {
	int* coordinates;
	size_t dimensions;
};

typedef struct Vector vector_t;

/**
 * @brief Creates new vector instance.
 * @param in Input stream.
 * @return Pointer to new instance.
 */
vector_t* create_vector(FILE* in);

/**
 * @brief Destroys the vector.
 * @param vector Pointer to vector instance.
 */
void free_vector(vector_t* vector);

/**
 * @brief Prints the vector to the output.
 * @param out Output stream.
 * @param vector Pointer to vector instance.
 */
void print_vector(FILE* out, const vector_t* vector);

// --- Vector implementation ---------------------------------------

bool is_valid_vector_symbol(char c) {
	return isdigit(c) || c == ',' || c == ' ' || c == '{' || c == '}';
}

vector_t* create_vector(FILE* in) {
	long init_pos = ftell(in);

	skip_space(in);
	if (fgetc(in) != '{') {
		// vector must starts with '{'
		fseek(in, init_pos, SEEK_SET);
		return NULL;
	}

	vector_t* result = (vector_t*) malloc(sizeof(vector_t));
	if (result == NULL) {
		fseek(in, init_pos, SEEK_SET);
		return NULL;
	}
	result->coordinates = NULL;
	result->dimensions = 0;

	bool is_last_coordinate = false;
	long begin_pos = ftell(in);
	size_t dimensions_buffer_size = 0;
	while (true) {
		skip_space(in);
		const int ch_int = fgetc(in);
		const char ch = (char) ch_int;
		if (ch_int == EOF || !is_valid_vector_symbol(ch)) {
			fseek(in, init_pos, SEEK_SET);
			return NULL;
		}

		if (ch == '}') {
			// if close bracket
			break;
		} else if (ch == ',') {
			// if comma-separator
			if (is_last_coordinate) {
				is_last_coordinate = false;
				continue;
			} else {
				free_vector(result);
				fseek(in, init_pos, SEEK_SET);
				return NULL;
			}
		} else {
			// otherwise it must be a number (coordinate)
			fseek(in, -sizeof(char), SEEK_CUR);
		}

		int coordinate;
		if (fscanf(in, "%d", &coordinate) != 1) {
			free_vector(result);
			fseek(in, init_pos, SEEK_SET);
			return NULL;
		}
		if (dimensions_buffer_size == result->dimensions) {
			dimensions_buffer_size *= 2;
			++dimensions_buffer_size;
			int* new_coordinates = (int*) realloc(result->coordinates, sizeof(vector_t) * dimensions_buffer_size);
			if (new_coordinates == NULL) {
				free_vector(result);
				fseek(in, init_pos, SEEK_SET);
				return NULL;
			}
			result->coordinates = new_coordinates;
		}
		result->coordinates[result->dimensions++] = coordinate;
		is_last_coordinate = true;
	}

	return result;
}

void free_vector(vector_t* vector) {
	if (vector == NULL) {
		return;
	}
	free(vector->coordinates);
	free(vector);
}

void print_vector(FILE* out, const vector_t* vector) {
	if (vector == NULL) {
		return;
	}

	fprintf(out, "{");
	if (vector->dimensions) {
		const int* const coordinates = vector->coordinates;
		fprintf(out, "%d", coordinates[0]);
		for (size_t i = 1, size = vector->dimensions; i < size; ++i) {
			fprintf(out, ",%d", coordinates[i]);
		}
	}
	fprintf(out, "}");
}

// -----------------------------------------------------------------

int main() {

	return 0;
}