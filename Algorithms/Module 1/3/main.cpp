/**
 * @brief Task 3_1
 * @author Ed Asriyan
 *
 * Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел
 * B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс k
 * минимального элемента массива A, равного или превосходящего
 * B[i]: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы
 * поиска k для каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
 */

#include <iostream>
#include <cstring>

/**
 * @brief Represents an array with fixed length
 */
template<class T>
class Array {
	private:
		T* data;
		int size;

	public:
		/**
		 * @brief array iterator
		 */
		typedef T* iterator;

		/**
		 * @brief const array iterator
		 */
		typedef const T* const_iterator;

		/**
		 * @brief array constructor
		 * @param size_ size of array
		 */
		Array(int size_) {
			data = new T[size = size_];
		}

		/**
		 * @brief array copying constructor
		 * @param array source array
		 */
		Array(const Array<T>& array) {
			data = new T[size = array.size];
			std::memcpy(data, array.data, size * sizeof(T));
		}

		/**
		 * @brief array destructor
		 */
		~Array() {
			delete[] data;
			data = NULL;
			size = 0;
		}

		/**
		 * @brief returns an iterator pointing to the first element in the array
		 * @return an iterator pointing to the first element in the array
		 */
		iterator begin() {
			return data;
		}

		/**
		 * @brief returns a const iterator pointing to the first element in the array
		 * @return a const iterator pointing to the first element in the array
 		 */
		const_iterator begin() const {
			return data;
		}

		/**
		 * @brief returns an iterator pointing to the past-the-end element in the array
		 * @return an iterator pointing to the past-the-end element in the array
		 */
		iterator end() {
			return data + size;
		}

		/**
		 * @brief returns a const iterator pointing to the past-the-end element in the array
 		 * @return a const iterator pointing to the past-the-end element in the array
 		 */
		const_iterator end() const {
			return data + size;
		}

		/**
		 * @brief returns a reference to the element at position n in the array container
		 * @param index position of the element in the array
		 * @return a reference to the element at position n in the array container.
		 */
		T& operator[](int index) {
			return data[index];
		}

		/**
		 * @brief returns a const reference to the element at position n in the array container
		 * @param index position of the element in the array
		 * @return a const reference to the element at position n in the array container.
		 */
		const T& operator[](int index) const {
			return data[index];
		}

		/**
		 * @brief returns array size
		 * @return array size
		 */
		int get_size() const {
			return size;
		}

		template<class I>
		friend std::ostream& operator<<(std::ostream& out, const Array<I>& array) {
			for (int i = 0; i < array.size; ++i) {
				out << array.data[i] << ' ';
			}
			return out;
		}
};

/**
 * @brief Reads an array form input stream
 * @param in input stream
 * @param array[out] the array where to write read information
 */
template<class T>
void read_array(std::istream& in, Array<T>& array) {
	int size = array.get_size();
	for (int i = 0; i < size; ++i) {
		in >> array[i];
	}
}

/**
 * @brief Search value exists in sorted array by binary algorithm
 * @param source sorted array
 * @param value value to search
 * @param begin index of the left border of regarging part in the source array
 * @param end index of the right border of regarding part in the source array
 * @return index of the first element that is more or equal to value, if element is not found -1
 */
template<class T>
int binary_search(const Array<T>& source, const T& value, int begin = -1, int end = -1) {
	// if source is empty, it does not contain element, which is equal to value
	if (!source.get_size()) {
		return -1;
	}

	// checking begin & end arguments
	if (begin < 0) {
		begin = 0;
	}
	if (end < 0) {
		end = source.get_size() - 1;
	}

	// while length of regarded part of source is bigger then 2
	while (end - begin > 1) {
		// define the middle of the current part
		int curr_index = (begin + end) / 2;
		const T& curr_elem = source[curr_index];

		// in this way we need to consider right half of the current part
		if (curr_elem < value) {
			begin = curr_index + 1;
		}
			// in another way we need to consider left half of the current part
		else {
			end = curr_index;
		}
	}

	// checking left & right elements of the part
	if (source[begin] >= value) {
		return begin;
	} else if (source[end] >= value) {
		return end;
	} else {
		return -1;
	}
}

/**
 * @brief Search value exists in sorted array by logarithmic time
 * @param source sorted array
 * @param value value to search
 * @return index of the first element that is more or equal to value, if element is not found -1
 *
 * @see binary_search
 */
template<class T>
int search(const Array<T>& source, const T& value) {
	// border of the regarding part of the source array
	int begin = 0;
	int end = 1;

	const int source_size = source.get_size();

	// checking borders
	if (!source_size ||
		source[source_size - 1] < value) {
		return -1;
	}

	// moving regarding part to the right
	// on each step part length increase by 2 times
	while (end < source_size && source[end] < value) {
		begin = end;
		end <<= 1;
	}

	// when part is detected, run binary search
	return binary_search(source, value, begin, end < source_size ? end : source_size - 1);
}

Array<int> process(const Array<int>& a, const Array<int>& b) {
	int a_size = a.get_size();
	int b_size = b.get_size();
	Array<int> result(b_size);

	for (int i = 0; i < b_size; ++i) {
		int search_result = search(a, b[i]);
		result[i] = search_result < 0 ? a_size : search_result;
	}

	return result;
}

int main() {
	int n = 0;
	std::cin >> n;
	int m = 0;
	std::cin >> m;

	Array<int> a(n);
	read_array(std::cin, a);

	Array<int> b(m);
	read_array(std::cin, b);

	std::cout << process(a, b);

	return 0;
}