// Author: Eduard Asriyan
//
// The problem:
// 2_4.
// “Считалочка”. В круг выстроено N человек, пронумерованных числами от 1 до N.
// Будем исключать каждого k­ого до тех пор, пока не уцелеет только один человек.
// (Например, если N=10, k=3, то сначала умрет 3­й, потом 6­й, затем 9­й,
// затем 2­й, затем 7­й, потом 1­й, потом 8­й, за ним ­ 5­й, и потом 10­й.
// Таким образом, уцелеет 4­й.) Необходимо определить номер уцелевшего.
// N, k ≤ 10000.


#include <iostream>

int calc_survive_number(int N, int k) {
	bool* people = new bool[N];
	for (int i = 0; i < N; ++i) {
		people[i] = true;
	}

	int curr_person = 0;
	for (int i = 0; i < N; ++i) {
		int skipped = 1;
		while (skipped < k || !people[curr_person]) {
			skipped += people[curr_person];
			curr_person = (curr_person + 1) % N;
		}

		people[curr_person] = false;
	}

	delete[] people;

	return curr_person + 1;
}

int main() {
	int N = 0;
	std::cin >> N;
	int k = 0;
	std::cin >> k;

	std::cout << calc_survive_number(N, k);

	return 0;
}