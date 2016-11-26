/**
 * @file
 *
 * 6_2. LSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6. Отсортировать массив методом
 * поразрядной сортировки LSD по байтам.
 */

#include <iostream>
#include <cstring>
#include <cassert>

namespace Sort {

	/**
	 * @brief Returns byte value by it index.
	 * @param value The instance of the object to extract the byte value.
	 * @param byte Byte index.
	 * @return Value of the byte.
	 */
	template<class T>
	inline int _get_byte_by_index(const T& value, int byte) {
		assert(sizeof(T) <= sizeof(1ULL));
		return (value >> (8 * byte)) & 255;
	}

	/**
	 * @brief Counting sort by p-th byte
	 * @param begin Pointer to the initial position in the sequence.
	 * @param count Sequence length.
	 * @param byte Number of the byte to sort.
	 */
	template<class T>
	void CountingSort(T* begin, size_t count, int byte) {
		assert(sizeof(T) <= sizeof(1ULL));

		T* b = new T[count];
		int c[256] = {0};

		for (size_t j = 0; j < count; ++j) {
			c[_get_byte_by_index(begin[j], byte)]++;
		}
		for (int j = 1; j < 256; ++j) {
			c[j] += c[j - 1];
		}
		for (int j = static_cast<int>(count) - 1; j >= 0; --j) {
			b[--c[_get_byte_by_index(begin[j], byte)]] = begin[j];
		}
		std::memcpy(begin, b, sizeof(T) * count);

		delete[] b;
	}

	/**
	 * @brief Sorts the sequence by radix (LSD).
	 * @param begin Pointer to the initial position in the sequence.
	 * @param count Sequence length.
	 */
	template<class T>
	void LsdSort(T* begin, const size_t count) {
		assert(sizeof(T) <= sizeof(1ULL));

		for (int i = 0; i < static_cast<int>(sizeof(*begin)); ++i) {
			CountingSort(begin, count, i);
		}
	}

}

int main() {
	size_t n;
	std::cin >> n;

	unsigned long long* array = new unsigned long long[n];
	for (size_t i = 0; i < n; ++i) {
		std::cin >> array[i];
	}

	Sort::LsdSort(array, n);

	for (size_t i = 0; i < n; ++i) {
		std::cout << array[i] << ' ';
	}

	delete[] array;

	return 0;
}