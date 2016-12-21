#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

// --- Help functions -----------------------------------------------

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

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
 * @param dimensions Dimensions count.
 * @return Pointer to new instance.
 */
vector_t* create_vector(size_t dimensions);

/**
 * @brief Reads vector to new instance.
 * @param in Input stream.
 * @return Pointer to new instance.
 */
vector_t* scan_vector(FILE* in);

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

/**
 * @brief Adds vectors a & b.
 * @param a Left vector.
 * @param b Right vector.
 * @param result Result vector.
 * @return Pointer to new vector if operation is completed; otherwise NULL.
 */
vector_t* add_vector(const vector_t* a, const vector_t* b);

// --- Vector implementation ---------------------------------------

bool is_valid_vector_symbol(char c) {
	return isdigit(c) || c == ',' || c == ' ' || c == '{' || c == '}';
}

vector_t* create_vector(size_t dimensions) {
	vector_t* result = (vector_t*) malloc(sizeof(vector_t));
	if (result == NULL) {
		return NULL;
	}
	result->coordinates = (int*) malloc(sizeof(int) * dimensions);
	if (result->coordinates == NULL) {
		free(result);
		return NULL;
	}
	result->dimensions = dimensions;
	return result;
}

vector_t* scan_vector(FILE* in) {
	if (in == NULL) {
		return NULL;
	}

	long init_pos = ftell(in);

	skip_space(in);
	const int init_symb_int = fgetc(in);
	if (init_symb_int == EOF || (char) init_symb_int != '{') {
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

vector_t* add_vector(const vector_t* a, const vector_t* b) {
	if (a == NULL || b == NULL) {
		return NULL;
	}

	const int* a_coordinates = a->coordinates;
	const int* b_coordinates = b->coordinates;
	const size_t result_dimensions = MAX(a->dimensions, b->dimensions);
	vector_t* result = create_vector(result_dimensions);
	const size_t max = MIN(a->dimensions, b->dimensions);
	for (size_t i = 0; i < max; ++i) {
		result->coordinates[i] = a_coordinates[i] + b_coordinates[i];
	}
	const int* coordinates = MAX(a->dimensions, b->dimensions) == a->dimensions ? a->coordinates : b->coordinates;
	for (size_t i = max; i < result_dimensions; ++i) {
		result->coordinates[i] = coordinates[i];
	}

	return result;
}

// -----------------------------------------------------------------

// --- Operand -----------------------------------------------------

struct Operand {
	bool is_vector;
	union {
		vector_t* vector;
		int number;
	} value;
};

typedef struct Operand operand_t;

/**
 * @brief Creates new operand instance.
 * @param in Input stream.
 * @return Pointer to new instance.
 */
operand_t* scan_operand(FILE* in);

/**
 * @brief Destroys the operand.
 * @param vector Pointer to operand instance.
 */
void free_operand(operand_t* operand);

/**
 * @brief Prints the operand to the output.
 * @param out Output stream.
 * @param vector Pointer to operand instance.
 */
void print_operand(FILE* out, operand_t* operand);

/**
 * @brief Adds operands a & b.
 * @param a Left operand.
 * @param b Right operand.
 * @param result Result operand.
 * @return Pointer to new operand if operation is completed; otherwise NULL.
 */
operand_t* add_operand(const operand_t* a, const operand_t* b);

/**
 * @brief Multiplies operands a & b.
 * @param a Left operand.
 * @param b Right operand.
 * @param result Result operand.
 * @return Pointer to new operand if operation is completed; otherwise NULL.
 */
operand_t* mlt_operand(const operand_t* a, const operand_t* b);

// --- Operand implementation --------------------------------------

operand_t* scan_operand(FILE* in) {
	if (in == NULL) {
		return NULL;
	}

	long init_pos = ftell(in);

	operand_t* result = (operand_t*) malloc(sizeof(operand_t));
	if (result == NULL) {
		return NULL;
	}

	if (fscanf(in, "%d", &result->value.number) == 1) {
		// if operand is number
		result->is_vector = false;
		return result;
	}

	// otherwise it must be a vector
	result->value.vector = scan_vector(in);
	if (result->value.vector == NULL) {
		free(result);
		return NULL;
	}
	result->is_vector = true;
	return result;

	free(result);
	return NULL;
}

void free_operand(operand_t* operand) {
	if (operand == NULL) {
		return;
	}

	if (operand->is_vector) {
		free_vector(operand->value.vector);
	}
	free(operand);
}

void print_operand(FILE* out, operand_t* operand) {
	if (operand == NULL) {
		return;
	}

	if (operand->is_vector) {
		print_vector(out, operand->value.vector);
	} else {
		fprintf(out, "%d", operand->value.number);
	}
}

operand_t* add_operand(const operand_t* a, const operand_t* b) {
	if (a == NULL || b == NULL || !a->is_vector || !b->is_vector) {
		return NULL;
	}

	operand_t* result = (operand_t*) malloc(sizeof(operand_t));
	if (result == NULL) {
		return NULL;
	}
	result->is_vector = true;
	result->value.vector = add_vector(a->value.vector, b->value.vector);
	if (result->value.vector == NULL) {
		free(result);
		return NULL;
	}

	return result;
}

operand_t* mlt_operand(const operand_t* a, const operand_t* b) {
	if (a == NULL || b == NULL || a->is_vector == b->is_vector) {
		return NULL;
	}

	int number = a->is_vector ? b->value.number : a->value.number;
	vector_t* vector = a->is_vector ? a->value.vector : b->value.vector;

	operand_t* result = (operand_t*) malloc(sizeof(operand_t));
	if (result == NULL) {
		return NULL;
	}
	result->is_vector = true;
	result->value.vector = create_vector(vector->dimensions);
	if (result->value.vector == NULL) {
		return NULL;
	}

	for (size_t i = 0, size = vector->dimensions; i < size; ++i) {
		result->value.vector->coordinates[i] = vector->coordinates[i] * number;
	}

	return result;
}

// -----------------------------------------------------------------

int main() {
	FILE* f = fopen("in.txt", "r");
	operand_t* a = scan_operand(f);
	operand_t* b = scan_operand(f);
	operand_t* c = add_operand(a, b);
	operand_t* e = mlt_operand(a, b);

	print_operand(stdout, a);
	printf("\n");
	print_operand(stdout, b);
	printf("\n");
	print_operand(stdout, c);
	printf("\n");
	print_operand(stdout, e);
	printf("\n");

	free_operand(a);
	free_operand(b);
	free_operand(c);
	free_operand(e);

	fclose(f);

	return 0;
}