#include "matrix.h"

//TODO

int isSeparator(char c){
	return isspace(c) || c == '\0';
}

int get_numbers_count_on_line(FILE* file){
	long pos = ftell(file);

	int result = 0;
	int isWord = 0;
	int isEOL = 0;
	while (!isEOL) {
		char c = getc(file);
		isEOL = feof(file) || c == '\n';
		
		int isCurrWord = !isSeparator(c);
		if ((isWord != isCurrWord || isEOL)){
			if (isWord){
				result++;
			}
			
			isWord = isCurrWord;
		}
	}

	fseek(file, pos, SEEK_SET);
	return result;
}

void go_to_end_of_line(FILE* file){
	while (fgetc(file) != '\n' && !feof(file));
}

Matrix* create_matrix_from_file(FILE* file){
	int width, height;
	fscanf(file, "%d", &height);
	fscanf(file, "%d", &width);

	Matrix* result = create_matrix(height, width);

	go_to_end_of_line(file);
	int row = 0;
	while (!feof(file)){
		if (row + 1 > result->height){
			//printf("Expading height %d to %d\n", result->height, row);
			expand_matrix(result, row + 1, result->width);
		}

		int numbersCount = get_numbers_count_on_line(file);
		if (numbersCount > result->width){
			//printf("Expading width %d to %d\n", result->width, numbersCount);
			expand_matrix(result, result->height, numbersCount);
		}
		//printf("Reading %d numbers on %d line (%d, %d)\n", numbersCount, row, result->height, result->width);
		for (int i = 0; i < numbersCount; i++){
			double t;
			fscanf(file, "%lf", &t);
			set_elem(result, row, i, t);
		}
		go_to_end_of_line(file);

		row++;
	}

	return result;
}

Matrix* create_matrix(int row, int col){
	Matrix* result = (Matrix*)malloc(sizeof(Matrix));
	
	result->height = row;
	result->width = col;
	result->data = (double**)calloc(row, sizeof(double*));
	
	for (int i = 0; i < row; i++){
		result->data[i] = (double*)calloc(col, sizeof(double));
	}

	return result;
}

void free_matrix(Matrix* matrix){
	for (int i = 0; i < matrix->height; i++){
		free(matrix->data[i]);
	}
	free(matrix->data);
	free(matrix);
}

double get_elem(Matrix* matrix, int row, int col){
	return matrix->data[row][col];
}

void set_elem(Matrix* matrix, int row, int col, double val){
	matrix->data[row][col] = val;
}

int get_rows(Matrix* matrix){
	return matrix->height;
}
int get_cols(Matrix* matrix){
	return matrix->width;
}

void expand_matrix(Matrix* matrix, int row, int col){
	if (col != matrix->width){
		for (int i = 0; i < matrix->height; i++){
			matrix->data[i] = (double*)realloc(matrix->data[i], col * sizeof(double));
			for (int j = matrix->width; j < col; j++){
				matrix->data[i][j] = 0;
			}
		}
		matrix->width = col;
	}
	if (row != matrix->height){
		for (int i = row; i < matrix->height; i++){
			free(matrix->data[i]);
		}
		matrix->data = (double**)realloc(matrix->data, row * sizeof(double*));
		for (int i = matrix->height; i < row; i++){
			matrix->data[i] = (double*)calloc(matrix->width, sizeof(double));
		}
		matrix->height = row;
	}
}