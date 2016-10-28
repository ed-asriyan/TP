#include <iostream>

/**
 * Sorts elements of the array by insertion method
 * @param array Pointer to the first object of the array to be sorted
 * @param length Number of elements in the array
 */
template<class T>
void insertion_sort(T* array, int length) {
	if (array == NULL) {
		return;
	}

	for (int i = 1; i < length; ++i) {
		T tmp = array[i];
		int j = i;
		while (j > 0 && array[j - 1] > tmp) {
			array[j] = array[--j];
		}
		array[j] = tmp;
	}
}

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}