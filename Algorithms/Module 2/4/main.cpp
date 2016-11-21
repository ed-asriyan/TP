/**
 * @file
 *
 * 4_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию `Partition` реализуйте методом
 * прохода двумя итераторами от конца массива к началу.
 */

#include <iostream>

/**
 * @brief Splits the sequence to two parts.
 * @param begin Iterator to the initial position in the sequence.
 * @param end Iterator to the final position in the sequence.
 * @return Iterator to the pivot element.
 */
template<class ITERATOR>
ITERATOR Partition(ITERATOR begin, ITERATOR end) {
	// todo: implement
	return begin;
}

/**
 * @brief calculates K statistics in the sequence.
 * @param begin Iterator to the initial position in the sequence.
 * @param end Iterator to the final position in the sequence.
 * @return Value on the k-th place in the sorted sequence.
 */
template<class ITERATOR>
auto CalcStatistics(ITERATOR begin, ITERATOR end, decltype(*begin) k) -> decltype(*begin) {
	// todo: implement
	return *begin;
}

int main() {
	int n, k;
	std::cin >> n >> k;

	int* data = new int[n];
	for (int i = 0; i < n; ++i) {
		std::cin >> data[i];
	}

	std::cout << CalcStatistics(data, data + n, k);

	delete[] data;

	return 0;
}