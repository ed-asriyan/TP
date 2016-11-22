/**
 * @file
 *
 * 6_2. LSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6. Отсортировать массив методом
 * поразрядной сортировки LSD по байтам.
 */

#include <iostream>
#include <cassert>

template<class T>
void CountSort(T* arr, int n, int bit) {


	T output[20];
	int i, count[10] = {0};
	for (i = 0; i < n; i++)
		count[(arr[i] / bit) % 10]++;
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / bit) % 10] - 1] = arr[i];
		count[(arr[i] / bit) % 10]--;
	}
	for (i = 0; i < n; i++)
		arr[i] = output[i];
};

/**
 * @brief Sorts the sequence by radix (LSD).
 * @param begin Iterator to the initial position in the sequence.
 * @param end Iterator to the initial position in the sequence.
 */
template<class ITERATOR>
void LsdSort(ITERATOR* begin, ITERATOR* end) {

	assert(sizeof(*begin) <= sizeof(1ULL));

	for (auto i = sizeof(*begin) - 1; i >= 0; --i) {
		CountSort(begin, count, i);
	}
}

int main() {
	size_t n;
	std::cin >> n;

	unsigned long long* array = new unsigned long long[n];
	for (size_t i = 0; i < n; ++i) {
		std::cin >> array[i];
	}

	LsdSort(array, n);

	for (size_t i = 0; i < n; ++i) {
		std::cout << array[i] << ' ';
	}

	delete[] array;

	return 0;
}