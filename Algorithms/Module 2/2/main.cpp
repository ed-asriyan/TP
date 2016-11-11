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
#include <vector>

namespace BinaryHeap {
	/**
	 * @brief Heap.
	 */
	template<class T>
	class Heap {
		private:
			std::vector<T> data;

			void heapify(int i);
			void heapifyAll();

		public:
			/**
			 * @brief Exception which tells that the required Node does not exists.
			 */
			class NodeNotExistsException : public std::exception {};

			/**
			 * @brief Exception that tells that the value os the node is invalid.
			 */
			class InvalidNodeValueException : public std::exception {};

			/**
			 * @brief Exception that tells that the node do not belong to current Heap (current container).
			 */
			class ForeignNodeException : public std::exception {};

			/**
			 * @brief Node of the binary heap tree.
			 */
			class Node {
				private:
					int index;
					const std::vector<T>& data;

					Node(const std::vector<T>& data, int index);

					int get_left_index() const;
					int get_right_index() const;
				public:
					/**
					 * @brief Exception which tells that the Node have not a required child.
					 */
					class ChildNotExistsException : public std::exception {};

					/**
					 * @brief Returns a value that indicates whether the node has a right child.
					 * @return true if the node has a right child; otherwise, false.
					 */
					bool HaveLeft() const;

					/**
					 * @brief Returns a value that indicates whether the node has a left child.
					 * @return true if the node has a left child; otherwise, false.
					 */
					bool HaveRight() const;

					const T& operator*() const;

					/**
					 * @brief Returns the left child if it exists; otherwise, thows ChildNotExistsException.
					 * @return The left child of the node.
					 */
					Node LeftChild() const;

					/**
					* @brief Returns the right child if it exists; otherwise, thows ChildNotExistsException.
					* @return The right child of the node.
					*/
					Node RightChild() const;

					friend Node Heap<T>::get_max() const;
					friend void Heap<T>::ChangeNodeValue(Node, const T& value);
					friend T Heap<T>::Extract(Heap<T>::Node node);
			};

			template<class ITERATOR>
			Heap(const ITERATOR& begin, const ITERATOR& end);

			Heap(const std::initializer_list<T>&);

			/**
			 * @brief Rewrites heap element with new value.
			 * @param value Value that is necessary to replace with.
			 */
			void ChangeNodeValue(Node, const T& value);

			/**
			 * @brief Extracts element from heap.
			 */
			T Extract(Heap<T>::Node node);

			/**
			 * Returns the max element of the heap if it exists; otherwise, trows NodeNotExistsException.
			 * @return The max element of the heap.
			 */
			Node get_max() const;

			/**
			 * @brief Returns heap size.
			 * @return Heap size.
			 */
			int get_size() const;

	};

	template<class T>
	Heap<T>::Node::Node(const std::vector<T>& data, int index) :data(data), index(index) {

	}

	template<class T>
	bool Heap<T>::Node::HaveLeft() const {
		return get_left_index() < data.size();
	}

	template<class T>
	bool Heap<T>::Node::HaveRight() const {
		return get_right_index() < data.size();
	}

	template<class T>
	const T& Heap<T>::Node::operator*() const {
		return data[index];
	}

	template<class T>
	typename Heap<T>::Node Heap<T>::Node::LeftChild() const {
		if (!HaveLeft()) throw ChildNotExistsException();
		return Heap::Node(data, get_left_index());
	}

	template<class T>
	int Heap<T>::Node::get_left_index() const {
		return (index << 2) + 1;
	}

	template<class T>
	int Heap<T>::Node::get_right_index() const {
		return (index << 2) + 2;
	}

	template<class T>
	typename Heap<T>::Node Heap<T>::Node::RightChild() const {
		if (!HaveRight()) throw ChildNotExistsException();
		return Heap::Node(data, get_right_index());
	}

	template<class T>
	template<class ITERATOR>
	Heap<T>::Heap(const ITERATOR& begin, const ITERATOR& end) {
		data.insert(data.begin(), begin, end);
		heapifyAll();
	}

	template<class T>
	Heap<T>::Heap(const std::initializer_list<T>& init_list) {
		data = init_list;
		heapifyAll();
	}

	template<class T>
	void Heap<T>::heapify(int i) {
		if (i >= data.size()) {
			return;
		}
		int left = i << 1;
		int right = left + 1;
		int largest = i;

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
	void Heap<T>::heapifyAll() {
		for (int i = (int) data.size() - 1; i >= 0; --i) {
			heapify(i);
		}
	}

	template<class T>
	typename Heap<T>::Node Heap<T>::get_max() const {
		if (!data.size()) throw NodeNotExistsException();
		return Heap<T>::Node(data, 0);
	}

	template<class T>
	void Heap<T>::ChangeNodeValue(Heap<T>::Node node, const T& value) {
		if (&node.data != &data) throw ForeignNodeException();

		if (value > data[node.index]) {
			data[node.index] = value;
			while (node.index > 0 && data[node.index / 2] < data[node.index]) {
				std::swap(data[node.index], data[node.index >> 1]);
				node.index >>= 1;
			}
		} else if (value < data[node.index]) {
			data[node.index] = value;
			heapify(node.index);
		}
	}

	template<class T>
	T Heap<T>::Extract(Heap<T>::Node node) {
		if (!data.size()) throw NodeNotExistsException();

		T result = data[node.index];
		data.erase(data.begin() + node.index);
		heapify(node.index);
		return result;
	}

	template<class T>
	int Heap<T>::get_size() const {
		return (int) data.size();
	}

}

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}