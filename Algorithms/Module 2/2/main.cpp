/**
 * @file
 *
 * Вовочка ест фрукты из бабушкиной корзины. В корзине лежат фрукты разной массы.
 * Вовочка может поднять не более `K` грамм. Каждый фрукт весит не более `K`
 * грамм. За раз он выбирает несколько самых тяжелых фруктов, которые может
 * поднять одновременно, откусывает от каждого половину и кладет огрызки обратно в
 * корзину. Если фрукт весит нечетное число грамм, он откусывает большую
 * половину. Фрукт массы 1гр он съедает полностью.
 *
 * Определить за сколько подходов Вовочка съест все фрукты в корзине.
 *
 * Решение данного раздела предполагает использование кучи.
 *
 * Формат входных данных. Вначале вводится `n` - количество фруктов и n строк
 * с массами фруктов. Затем `K` - "грузоподъемность".
 *
 * Формат выходных данных. Неотрицательное число - количество подходов к корзине.
 */

#include <iostream>
#include <initializer_list>
#include <exception>
#include <algorithm>
#include <vector>

namespace Heap {
	/**
	 * @brief The exception that is thrown when extracting from empty heap occur.
	 */
	class EmptyHeapException : public std::exception {};

	/**
	 * @brief Heap.
	 */
	template<class T>
	class BinaryHeap {
		private:
			std::vector<T> data = {T()};

		public:
			/**
			 * @brief Empty container constructor (default constructor).
			 *
			 * Constructs an empty heap, with no elements.
			 */
			BinaryHeap() = default;

			/**
			 * @brief Range constructor.
			 * @param begin Iterator to the initial position in range.
			 * @param end Iterator to the final position in range.
			 *
			 * Constructs a heap with as many elements as the range [first,last).
			 */
			template<class ITERATOR>
			BinaryHeap(ITERATOR begin, ITERATOR end);

			/**
			 * @brief Constructs the heap with the contents of the initializer list init.
			 * @param init Initializer list to initialize the elements of the heap with.
			 * @return
			 */
			BinaryHeap(const std::initializer_list<T>& init);

			/**
			 * @brief Extracts element from heap.
			 */
			T Pop();

			/**
			 * @brief Inserts the element into the heap.
			 * @param value Value to insert.
			 */
			void Push(const T& value);

			/**
			 * Returns the max element of the heap if it exists; otherwise, trows NodeNotExistsException.
			 * @return The max element of the heap.
			 */
			const T& Top() const;

			/**
			 * @brief Returns heap size.
			 * @return Heap size.
			 */
			int get_size() const;

		private:
			void heapify(unsigned long i);
	};

	template<class T>
	template<class ITERATOR>
	BinaryHeap<T>::BinaryHeap(ITERATOR begin, ITERATOR end) {
		data.reserve(std::distance(begin, end));
		for (; begin != end; ++begin) {
			data.push_back(*begin);
		}

		for (long i = static_cast<long>(data.size()) - 1; i >= 1; --i) {
			heapify(i);
		}
	}

	template<class T>
	BinaryHeap<T>::BinaryHeap(const std::initializer_list<T>& init_list) :BinaryHeap(init_list.begin(),
	                                                                                 init_list.end()) {}

	template<class T>
	void BinaryHeap<T>::heapify(unsigned long i) {
		if (i >= data.size()) {
			return;
		}
		unsigned long left = i << 1;
		unsigned long right = left + 1;
		unsigned long largest = i;

		if (left < data.size() && data[left] > data[largest]) {
			largest = left;
		}
		if (right < data.size() && data[right] > data[largest]) {
			largest = right;
		}
		if (largest != i) {
			std::swap(data[i], data[largest]);
			heapify(largest);
		}
	}

	template<class T>
	const T& BinaryHeap<T>::Top() const {
		if (!get_size()) throw EmptyHeapException();
		return data[1];
	}

	template<class T>
	T BinaryHeap<T>::Pop() {
		if (!get_size()) throw EmptyHeapException();

		int result = data[1];
		int size = get_size();

		std::swap(data[size], data[1]);
		data.pop_back();

		for (int i = 1; i << 1 < size;) {
			i <<= 1;
			if (i + 1 < size && data[i] < data[i + 1]) {
				i += 1;
			}
			if (data[i >> 1] < data[i]) {
				std::swap(data[i >> 1], data[i]);
			}
		}

		return result;
	}

	template<class T>
	int BinaryHeap<T>::get_size() const {
		return (int) data.size() - 1;
	}

	template<class T>
	void BinaryHeap<T>::Push(const T& value) {
		int size = get_size();
		data.push_back(value);
		for (int i = size + 1; i > 1;) {
			if (data[i] > data[i >> 1]) {
				std::swap(data[i], data[i >> 1]);
				i >>= 1;
			} else {
				break;
			}
		}
	}
}

/**
 * @brief Solves the problem
 * @param begin Iterator to the initial position of the fruits sequence
 * @param end Iterator to the final position of the fruits sequence
 * @param strength Strength
 * @return Solution
 */
template<class ITERATOR>
int CalcSolution(const ITERATOR& begin, const ITERATOR& end, const int strength) {
	if (begin == end) {
		return 0;
	}

	int result = 0;
	Heap::BinaryHeap<int> heap(begin, end);

	std::vector<int> picked_fruits;
	picked_fruits.reserve((unsigned int) heap.get_size());

	while (heap.get_size()) {
		int remaining_strength = strength;

		// weight of the current fruit.
		// the initial value must be less or equal then remaining strength (in another way loop will not start).
		// it will be changed in the following loop.
		int fruit = 0;

		// while fruits are exist and the boy has enough strength to pick the current fruit
		while (heap.get_size() && remaining_strength >= heap.Top()) {
			// getting the heaviest fruit
			remaining_strength -= fruit = heap.Pop();

			// if fruit weight more then 1
			if (fruit > 1) {
				// put the fruit in picked_fruits
				picked_fruits.push_back(fruit);
			}
		}

		// put back half part of each picked fruit
		while (picked_fruits.size()) {
			heap.Push(*(picked_fruits.end() - 1) >> 1);
			picked_fruits.pop_back();
		}

		++result;
	}

	return result;

}

int main() {
	int items_count;
	std::cin >> items_count;

	int* items = new int[items_count];
	for (int i = 0; i < items_count; ++i) {
		std::cin >> items[i];
	}

	int strength;
	std::cin >> strength;

	try {
		std::cout << CalcSolution(items, items + items_count, strength) << std::endl;
	} catch (Heap::EmptyHeapException& e) {
		std::cerr << "Error: Pop for empty heap is called." << std::endl;
	} catch (...) {
		std::cerr << "Error: An error occurred while calculating solution." << std::endl;
	}

	delete[] items;

	return 0;
}