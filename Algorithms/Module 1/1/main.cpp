#include <iostream>
#include <cstring>

template<class T>
const T& min(const T& a, const T& b) {
	return a < b ? a : b;
}

template<class T>
class Vector {
	public:
		Vector() {
			init();
		}

		explicit Vector(int size) {
			init();
			prepareData(size);
			length = size;
		}

		Vector(const Vector<T>& vector) {
			init();
			prepareData(vector.length);
			for (int i = 0; i < vector.length; ++i) {
				data[i] = vector.data[i];
			}
		}

		~Vector() {
			Clear();
		}

		void PushBack(const T& value) {
			prepareData(length + 1);
			data[length++] = value;
		}

		void Clear() {
			if (data != NULL && length > 0) {
				delete[] data;
				data = NULL;
				length = 0;
				data_length = 0;
			}
		}

		T& operator[](int index) {
			return data[index];
		}

		int get_size() {
			return length;
		}

		template<class I>
		friend std::ostream& operator<<(std::ostream& out, const Vector<I>& vector) {
			for (int i = 0; i < vector.length; ++i) {
				out << vector.data[i] << ' ';
			}

			return out;
		}
	private:
		static const int RESIZE_FACTOR = 3;

		T* data;
		int length;
		int data_length;

		void init() {
			data = NULL;
			length = 0;
			data_length = 0;
		}

		void prepareData(int size) {
			if (size <= 0) {
				Clear();
			} else {
				if (size > data_length) {
					T* new_data = new T[data_length = size * RESIZE_FACTOR];
					if (data != NULL) {
						std::memcpy(new_data, data, sizeof(T) * min(length, size));
						delete[] data;
					}
					data = new_data;
				}
			}
		}
};

Vector<int> Factorize(int n) {
	Vector<int> result;

	int factor = 2;
	while (n > 1) {
		if ((n % factor)) {
			++factor;
		} else {
			n /= factor;
			result.PushBack(factor);
		}
	}

	return result;
}

int main() {
	int n = 0;
	std::cin >> n;

	std::cout << Factorize(n);

	return 0;
}