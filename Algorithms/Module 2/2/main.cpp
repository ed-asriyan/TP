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
			std::vector<T> data;

			void heapify(int i);
			void heapify();

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
	};

	template<class T>
	template<class ITERATOR>
	BinaryHeap<T>::BinaryHeap(ITERATOR begin, ITERATOR end) {
		for (; begin != end; ++begin) {
			Push(*begin);
		}
	}

	template<class T>
	BinaryHeap<T>::BinaryHeap(const std::initializer_list<T>& init_list) :BinaryHeap(init_list.begin(),
	                                                                                 init_list.end()) {}

	template<class T>
	void BinaryHeap<T>::heapify(int i) {
		if (i >= (int) data.size()) {
			return;
		}
		int left = i << 1;
		int right = left + 1;
		int largest = i;

		if (left < (int) data.size() && data[left] > data[largest]) {
			largest = left;
		}
		if (right < (int) data.size() && data[right] > data[largest]) {
			largest = right;
		}
		if (largest != i) {
			std::swap(data[i], data[largest]);
			heapify(largest);
		}
	}

	template<class T>
	void BinaryHeap<T>::heapify() {
		for (int i = (int) data.size() - 1; i >= 0; --i) {
			heapify(i);
		}
	}

	template<class T>
	const T& BinaryHeap<T>::Top() const {
		if (!data.size()) throw EmptyHeapException();
		return data[0];
	}

	template<class T>
	T BinaryHeap<T>::Pop() {
		if (!data.size()) throw EmptyHeapException();

		T result = data[0];
		data.erase(data.begin());
		heapify();
		return result;
	}

	template<class T>
	int BinaryHeap<T>::get_size() const {
		return (int) data.size();
	}

	template<class T>
	void BinaryHeap<T>::Push(const T& value) {
		data.push_back(value);
		heapify();
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
int CalcSolution(const ITERATOR& begin, const ITERATOR& end, int strength) {
	if (begin == end) {
		return 0;
	}

	Heap::BinaryHeap<int> heap(begin, end);

	int result = 0;
	while (heap.get_size()) {
		int remaining_strength = strength;

		// weight of the current fruit.
		// the initial value must be less or equal then remaining strength (in another way loop will not start).
		// it will be changed in the following loop.
		int fruit = 0;

		// while fruits are exist and the boy has enough strength to pick the current fruit
		while (remaining_strength >= fruit && heap.get_size()) {
			// getting the heaviest fruit
			fruit = heap.Pop();

			// if the boy can pick this fruit
			if (remaining_strength >= fruit) {
				remaining_strength -= fruit;
				// if fruit weight more then 1
				if (fruit > 1) {
					// put back half of the fruit
					heap.Push(fruit >> 1);
				}
			}
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

	std::cout << CalcSolution(items, items + items_count, strength) << std::endl;

	return 0;
}