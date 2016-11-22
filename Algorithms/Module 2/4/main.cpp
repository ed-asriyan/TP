/**
 * @file
 *
 * 4_4. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию `Partition` реализуйте методом
 * прохода двумя итераторами от конца массива к началу.
 */

#include <random>
#include <ctime>
#include <iostream>
#include <algorithm>

/**
 * @brief Generates random integer in range from min to max.
 * @param min Lower border.
 * @param max Highter border.
 * @return Random integer in range from min to max.
 */
int GetRandom(int min, int max) {
	return std::rand() % (max - min + 1) + min;

	// the following code raises runtime error on the server :(
//	std::random_device rd;
//	std::mt19937 e2(rd());
//	std::uniform_int_distribution<> dist(min, max);
//	return dist(e2);
}

/**
 * @brief Splits the sequence to two parts.
 * @param begin Iterator to the initial position in the sequence.
 * @param end Iterator to the final position in the sequence.
 * @return Iterator to the pivot position in the sequence.
 */
template<class ITERATOR>
ITERATOR Partition(ITERATOR begin, ITERATOR end) {
	if (begin == end) {
		return begin;
	}

	auto pivot = begin + GetRandom(0, static_cast<int>(std::distance(begin, end)) - 1);
	std::iter_swap(begin, pivot);

	auto it = end - 1;
	auto jt = end - 1;
	while (jt != begin) {
		if (*jt >= *begin) {
			std::iter_swap(it, jt);
			--it;
		}
		--jt;
	}
	std::iter_swap(begin, it);

	return it;
}

/**
 * @brief calculates K statistics in the sequence.
 * @param begin Iterator to the initial position in the sequence.
 * @param end Iterator to the final position in the sequence.
 * @return Value on the k-th place in the sorted sequence.
 */
template<class ITERATOR>
auto CalcStatistics(ITERATOR begin, ITERATOR end, int k) -> decltype(*begin) {
	auto first = begin;
	auto last = end;

	while (true) {
		auto pivot = Partition(first, last);
		int pivot_pos = pivot - begin;

		if (pivot_pos == k) {
			return *(begin + k);
		} else if (pivot_pos > k) {
			last = pivot;
		} else {
			first = pivot + 1;
		}
	}
}

int main() {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

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

