#include "matrix.h"
#include <stdio.h>

#define ERROR_CAN_NOT_READ_FILE -1
#define ERROR_NO_ARGS -2

void printMatrix(Matrix* matrix){
	int width = get_cols(matrix);
	int height = get_rows(matrix);

	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			printf("%3.2f ", get_elem(matrix, i, j));
		}
		printf("\n");
	}
}

Matrix* trans(Matrix* matrix){
	int width = get_cols(matrix);
	int height = get_rows(matrix);
	Matrix* result = create_matrix(width, height);

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			set_elem(result, i, j, get_elem(matrix, j, i));
		}
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc < 2){
		return ERROR_NO_ARGS;
	}
	FILE* f = fopen(argv[1], "r");
	if (!f){
		return ERROR_CAN_NOT_READ_FILE;
	}
 
	Matrix* matrix = create_matrix_from_file(f);
	fclose(f);

	Matrix* trMatrix = trans(matrix);
	printMatrix(trMatrix);
	
	free_matrix(matrix);
	free_matrix(trMatrix);

	return 0;
}
