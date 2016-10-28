// Author: Eduard Asriyan
//
// The problem:
// Следует написать структуру данных, обрабатывающую команды push* и pop*.
// Формат входных данных.
// В первой строке количество команд n. n ≤ 1000000. Каждая команда задаётся
// как 2 целых числа: a b.
// a = 1 ­ push front
// a = 2 ­ pop front
// a = 3 ­ push back
// a = 4 ­ pop back
// Для очереди используются команды 2 и 3. Для дека используются все четыре
// команды. Если дана команда pop*, то число b ­ ожидаемое значение. Если
// команда pop вызвана для пустой структуры данных, то ожидается “­1”.
// Формат выходных данных.
// Требуется напечатать YES ­ если все ожидаемые значения совпали. Иначе,
// если хотя бы одно ожидание не оправдалось, то напечатать NO.


#include <cstdlib>
#include <cassert>
#include <iostream>

// Looped array.
// begin - 1 == end - 1
// (end - 1) + 1 == begin
template<class T>
class LoopedArray {
	private:
		T* data_begin;
		T* data_end;

		int size;

	public:

		class iterator {
			private:
				LoopedArray* parent;
				T* ptr;

			public:
				iterator() {

				}

				iterator(LoopedArray* parent_, T* ptr_) {
					parent = parent_;
					ptr = ptr_;
				}

				T& operator*() {
					return *ptr;
				}

				iterator operator++(int) {
					iterator result(*this);
					operator++();
					return result;
				}

				iterator& operator++() {
					T* next = ptr + 1;
					if (next == parent->data_end) {
						next = parent->data_begin;
					}
					this->ptr = next;

					return *this;
				}

				iterator operator--(int) {
					iterator result(*this);
					operator--();
					return result;
				}

				iterator& operator--() {
					T* prev = ptr - 1;
					if (prev == parent->data_begin - 1) {
						prev = parent->data_end - 1;
					}
					this->ptr = prev;
					return *this;
				}

				bool operator==(const iterator& it) const {
					return ptr == it.ptr;
				}

				bool operator!=(const iterator& it) const {
					return ptr != it.ptr;
				}

				friend iterator LoopedArray<T>::begin();
				friend iterator LoopedArray<T>::end();
		};

		typedef const iterator const_iterator;

		LoopedArray(int size_) {
			data_begin = new T[size = size_];
			data_end = data_begin + size;
		}

		~LoopedArray() {
			delete data_begin;
		}

		iterator begin() {
			return iterator(this, data_begin);
		}

		const_iterator begin() const {
			return iterator(this, data_begin);
		}

		iterator end() {
			return iterator(this, data_end);
		}

		const_iterator end() const {
			return iterator(this, data_end - 1);
		}

		int get_size() const {
			return size;
		}
};

template<class T>
class Dequeue {
	private:
		typedef typename LoopedArray<T>::iterator iterator;

		const static int SIZE_FACTOR = 4;
		LoopedArray<T>* data;

		iterator front;
		iterator back;

		int size;
	public:
		Dequeue();

		~Dequeue();

		void PushBack(const T& value);

		T PopBack();

		void PushFront(const T& value);

		T PopFront();

		int get_size() const;

	private:
		// sets initial values for fields
		void init();

		// clears all stack data
		void clear();

		// increases buff size (by creating new LoopedArray)
		void reallocate();
};

template<class T>
Dequeue<T>::Dequeue() {
	init();
}

template<class T>
Dequeue<T>::~Dequeue() {
	clear();
}

template<class T>
void Dequeue<T>::PushBack(const T& value) {
	// if stack is empty or buffer is full
	if (data == NULL || (size && front == back)) {
		reallocate();
	}

	++size;
	*(back++) = value;
}

template<class T>
T Dequeue<T>::PopBack() {
	assert(size);

	--size;
	return *(--back);
}

template<class T>
void Dequeue<T>::PushFront(const T& value) {
	// if stack is empty or buffer is full
	if (data == NULL || (size && front == back)) {
		reallocate();
	}

	++size;
	*(--front) = value;
}

template<class T>
T Dequeue<T>::PopFront() {
	--size;
	return *(front++);
}

template<class T>
int Dequeue<T>::get_size() const {
	return size;
}

// sets the initial stack values
// (recasts to empty stack)
template<class T>
void Dequeue<T>::init() {
	data = NULL;
	size = 0;
}

// clears all data_begin
template<class T>
void Dequeue<T>::clear() {
	delete data;
	init();
}

template<class T>
void Dequeue<T>::reallocate() {
	// new values
	int new_size = (size) * SIZE_FACTOR + 1;
	LoopedArray<T>* new_data = new LoopedArray<T>(new_size);
	iterator new_front = new_data->begin();
	iterator new_back = new_front;

	// if stack is not empty
	// copy items into new_data & delete old data
	if (data != NULL) {
		iterator it = front;
		do {
			*(new_back++) = *(it++);
		} while (it != back);

		delete data;
	}

	// accepting new values
	data = new_data;
	front = new_front;
	back = new_back;
}

int main() {
	int n = 0;
	std::cin >> n;

	Dequeue<int> dequeue;

	bool is_good = 1;
	for (int i = 0; i < n; ++i) {
		// the command type
		int a = 0;
		std::cin >> a;

		// the command argument
		int b = 0;
		std::cin >> b;

		switch (a) {
			case 1: dequeue.PushFront(b);
				break;
			case 2: is_good = b == (dequeue.get_size() ? dequeue.PopFront() : -1);
				break;
			case 3: dequeue.PushBack(b);
				break;
			case 4: is_good = b == (dequeue.get_size() ? dequeue.PopBack() : -1);
				break;
			default: break;

		}

		if (!is_good) {
			break;
		}
	}

	std::cout << (is_good ? "YES" : "NO");

	return 0;
}
