#include <iostream>
#include <string>

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
			array[j] = array[j - 1];
			--j;
		}
		array[j] = tmp;
	}
}

int main() {
	int n = 0;
	std::cin >> n;

	std::string* lines = new std::string[n];
	for (int i = 0; i < n; ++i) {
		std::getline(std::cin, lines[i]);
		std::cin >> lines[i];
	}

	// if last line is empty
	n -= !lines[n - 1].size();

	insertion_sort(lines, n);

	for (int i = 0; i < n; ++i) {
		std::cout << lines[i] << std::endl;
	}

	delete[] lines;

	return 0;
}