/**
 * @file
 *
 * 5_2. Сортировка почти упорядоченной последовательности.
 * Дана последовательность целых чисел `a[1]`, ..., `a[n]` и натуральное число `k`, такое что для любых `i`, `j`: если
 * `j >= i + k`, то `a[i] <= a[j]`. Требуется отсортировать последовательность. Последовательность может быть очень
 * длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

#include <iostream>
#include <vector>

/**
 * @brief Merge two arrays to ont
 * @param a Pointer to the initial position in the first array.
 * @param a_len Length of the fisrt array.
 * @param b Pointer to the initial position in the second array.
 * @param b_len Length of the second array.
 * @param out Pointer to the initial position in the output array.
 */
template<class T>
void Merge(T* a, int a_len, T* b, int b_len, T* out) {
	int i = 0;
	int j = 0;

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
void MergeSort(T* data, int count) {
	T* temp = new T[count];
	for (int i = 1; i < count; i *= 2) {
		// distance o the next array to sort
		int offset = 0;

		for (; offset + i < count; offset += i * 2) {
			Merge(data + offset, i, data + offset + i, std::min(i, count - i - offset), temp + offset);
		}

		if (offset < count) {
			for (int j = offset; j < count; ++j) {
				temp[j] = data[j];
			}
		}

		for (int j = 0; j < count; ++j) {
			data[j] = temp[j];
		}
	}
	delete[] temp;
}

/**
 * @brief Sorts the vector.
 * @param data Vector.
 * @param k Minimal distance between sorted elements.
 */
template<class T>
void Sort(std::vector<T>& data, int k) {
	int size = static_cast<int>(data.size());

	// sort first k elements
	int offset = k;
	MergeSort(&data[0], k);

	for (int i = k; i < size; i += k) {
		MergeSort(&data[0] + offset, k);
		Merge(&data[0], k, &data[0] + offset, k, &data[0]);

		offset += k;
	}
}

int main() {
	int count, k;
	std::cin >> count >> k;

	std::vector<int> data;
	data.reserve(static_cast<unsigned long>(count));
	for (int i = 0; i < count; ++i) {
		int value;
		std::cin >> value;
		data.push_back(value);
	}

	Sort(data, count);

	for (int i = 0; i < count; ++i) {
		std::cout << data[i] << ' ';
	}

	return 0;
}
