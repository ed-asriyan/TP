/**
 * @file
 *
 * 5_2. Сортировка почти упорядоченной последовательности.
 * Дана последовательность целых чисел `a[1]`, ..., `a[n]` и натуральное число `k`, такое что для любых `i`, `j`: если
 * `j >= i + k`, то `a[i] <= a[j]`. Требуется отсортировать последовательность. Последовательность может быть очень
 * длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

#include <iostream>

/**
 * @brief Merge two arrays to ont
 * @param a Pointer to the initial position in the first array.
 * @param a_len Length of the first array.
 * @param b Pointer to the initial position in the second array.
 * @param b_len Length of the second array.
 * @param out Pointer to the initial position in the output array.
 */
template<class T>
void Merge(const T* a, size_t a_len, const T* b, size_t b_len, T* out) {
	size_t i = 0;
	size_t j = 0;

	for (; i < a_len && j < b_len;) {
		if (a[i] < b[j]) {
			out[i + j] = a[i];
			++i;
		} else {
			out[i + j] = b[j];
			++j;
		}
	}
	if (i == a_len) {
		for (; j < b_len; ++j) {
			out[i + j] = b[j];
		}
	} else if (j == b_len) {
		for (; i < a_len; ++i) {
			out[i + j] = a[i];
		}
	}
}

/**
 * @brief Sorts the array
 * @param data Pointer to the initial position in the array.
 * @param count Length of the array.
 */
template<class T>
void MergeSort(T* data, size_t count) {
	T* temp = new T[count];
	for (size_t i = 1; i < count; i *= 2) {
		size_t offset = 0;

		for (; offset + i < count; offset += i * 2) {
			Merge(data + offset, i, data + offset + i, std::min(i, count - i - offset), temp + offset);
		}

		if (offset < count) {
			for (size_t j = offset; j < count; ++j) {
				temp[j] = data[j];
			}
		}

		for (size_t j = 0; j < count; ++j) {
			data[j] = temp[j];
		}
	}
	delete[] temp;
}

/**
 * @brief Sorts the vector.
 * @param data Pointer to the initial position in the sequence to sort.
 * @param size Sequence size.
 * @param k Minimal distance between sorted elements.
 */
template<class T>
void Sort(T* data, size_t size, size_t k) {
	MergeSort(data, k);
	for (size_t offset = k; offset < size; offset += k) {
		size_t len = std::min(k, size - offset);
		T* temp = new T[len + offset];

		MergeSort(data + offset, len);
		Merge(data + (offset - k), k, data + offset, len, temp);
		std::copy(temp, temp + (len + offset), data + (offset - k));

		delete[] temp;
	}
}

int main() {
	size_t count, k;
	std::cin >> count >> k;

	int* data = new int[count];
	for (size_t i = 0; i < count; ++i) {
		std::cin >> data[i];
	}

	Sort(data, count, k);

	for (size_t i = 0; i < count; ++i) {
		std::cout << data[i] << ' ';
	}

	return 0;
}
