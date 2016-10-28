#include <iostream>
#include <string>

class ComparableString : public std::string {
	public:
		bool operator<(const ComparableString& s) const;
		bool operator>(const ComparableString& s) const;
		bool operator<=(const ComparableString& s) const;
		bool operator>=(const ComparableString& s) const;
		bool operator==(const ComparableString& s) const;
};

bool ComparableString::operator<(const ComparableString& s) const {
	const_iterator it1 = begin();
	const_iterator it2 = s.begin();

	const_iterator it1_end = end();
	const_iterator it2_end = s.end();

	while (it1 != it1_end && it2 != it2_end) {
		if (*(it1++) < *(it2++)) {
			return true;
		} else if (*it1 > *it2) {
			return false;
		}
	}

	return size() < s.size();
}

bool ComparableString::operator>(const ComparableString& s) const {
	return s.operator<(*this);
}

bool ComparableString::operator<=(const ComparableString& s) const {
	return !s.operator<(*this);
}

bool ComparableString::operator>=(const ComparableString& s) const {
	return !operator<(s);
}

bool ComparableString::operator==(const ComparableString& s) const {
	return !operator<(s) && !s.operator<(*this);
}

/**
 * Sorts elements of the array by insertion method
 * @param array Pointer to the first object of the array to be sorted
 * @param length Number of elements in the array
 */
template<class T>
void insertion_sort(T* array, int length) {
	if (array == NULL) {
		return;
	}

	for (int i = 1; i < length; ++i) {
		T tmp = array[i];
		int j = i;
		while (j > 0 && array[j - 1] > tmp) {
			array[j] = array[j - 1];
			--j;
		}
		array[j] = tmp;
	}
}

int main() {
	int n = 0;
	std::cin >> n;

	ComparableString* lines = new ComparableString[n];
	for (int i = 0; i < n; ++i) {
		std::getline(std::cin, lines[i]);
		std::cin >> lines[i];
	}

	// if last line is empty
	n -= !lines[n - 1].size();

	insertion_sort(lines, n);

	for (int i = 0; i < n; ++i) {
		std::cout << lines[i] << std::endl;
	}

	delete[] lines;

	return 0;
}