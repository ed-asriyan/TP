/**
 * @file
 *
 * 4_2. Порядковые статистики.​ Дано число N и N строк. Каждая строка содержащит команду добавления или удаления
 * натуральных чисел, а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается
 * положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой
 * порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n).
 */

#include <cassert>
#include <algorithm>
#include <iostream>

namespace binarytree {
	/**
	 * @brief AVL tree.
	 */
	template<class T>
	class AvlTree {
		public:
			/**
			 * @brief Default constructor.
			 */
			AvlTree() = default;

			/**
			 * @brief Destructor.
			 */
			~AvlTree();

			/**
			 * @brief Inserts new value to the tree.
			 * @param value Value to insert.
			 */
			void Insert(const T& value);

			/**
			 * @brief Removes the value from the tree.
			 * @param value Value to remove.
			 */
			void Remove(const T& value);

			/**
			 * @brief Calculates K Statistics.
			 * @param k K parameter.
			 * @return K Statistics
			 */
			const T& CalcKStats(size_t k) const;

		protected:
			struct Node {
				Node(const T& value);
				~Node();

				T value;

				size_t height = 1;
				size_t size = 1;
				Node* left = nullptr;
				Node* right = nullptr;
			};

			size_t get_height(const Node* node) const;
			size_t get_size(const Node* node) const;
			int calcBalanceFactor(const Node* node) const;
			void fixHeight(Node* node);
			void fixSize(Node* node);

			Node* rotateRight(Node* p);
			Node* rotateLeft(Node* q);
			Node* balance(Node* p);

			Node* findMin(Node* node);

			Node* insert(Node* node, const T& value);
			Node* remove(Node* node, const T& value);

			Node* removeMin(Node* node);

		private:
			Node* root = nullptr;
	};

	template<class T>
	void AvlTree<T>::Insert(const T& value) {
		root = insert(root, value);

	}

	template<class T>
	size_t AvlTree<T>::get_height(const Node* node) const {
		return node == nullptr ? 0 : node->height;
	}

	template<class T>
	size_t AvlTree<T>::get_size(const Node* node) const {
		return node == nullptr ? 0 : node->size;
	}

	template<class T>
	int AvlTree<T>::calcBalanceFactor(const Node* node) const {
		if (node == nullptr) {
			return 0;
		}
		auto diff = static_cast<int>(get_height(node->right) - get_height(node->left));
		assert(-2 <= diff && diff <= 2);
		return diff;
	}

	template<class T>
	void AvlTree<T>::fixHeight(Node* node) {
		size_t h_left = get_height(node->left);
		size_t h_right = get_height(node->right);
		node->height = std::max(h_left, h_right) + 1;
	}

	template<class T>
	void AvlTree<T>::fixSize(Node* node) {
		size_t l_size = get_size(node->left);
		size_t r_size = get_size(node->right);
		node->size = l_size + r_size + 1;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::rotateRight(AvlTree::Node* node) {
		Node* left(node->left);
		node->left = left->right;
		left->right = node;

		fixHeight(node);
		fixSize(node);
		fixHeight(left);
		fixSize(left);

		return left;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::rotateLeft(Node* node) {
		Node* right(node->right);
		node->right = right->left;
		right->left = node;

		fixHeight(node);
		fixSize(node);
		fixHeight(right);
		fixSize(right);

		return right;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::balance(Node* node) {
		fixHeight(node);
		fixSize(node);

		if (calcBalanceFactor(node) == 2) {
			if (calcBalanceFactor(node->right) < 0) {
				node->right = rotateRight(node->right);
			}
			return rotateLeft(node);
		}
		if (calcBalanceFactor(node) == -2) {
			if (calcBalanceFactor(node->left) > 0) {
				node->left = rotateLeft(node->left);
			}
			return rotateRight(node);
		}
		return node;
	}

	template<class T>
	AvlTree<T>::~AvlTree() {
		delete root;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::insert(Node* node, const T& value) {
		if (node == nullptr) {
			return new Node(value);
		} else if (value < node->value) {
			node->left = insert(node->left, value);
		} else {
			node->right = insert(node->right, value);
		}
		return balance(node);
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::remove(Node* node, const T& value) {
		if (node == nullptr) {
			return nullptr;
		}

		if (value < node->value) {
			node->left = remove(node->left, value);
		} else if (value > node->value) {
			node->right = remove(node->right, value);
		} else {
			if (node->left == nullptr || node->right == nullptr) {
				Node* temp = node->left ? node->left : node->right;

				if (temp == nullptr) {
					temp = node;
					node = nullptr;
				} else {
					*node = *temp;
				}
				delete temp;
			} else {
				Node* temp = findMin(node->right);
				node->value = temp->value;
				node->right = remove(node->right, temp->value);
			}
		}

		if (node == nullptr) {
			return node;
		}

		return balance(node);
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::findMin(Node* node) {
		return node->left == nullptr ? node : findMin(node->left);
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::removeMin(Node* node) {
		if (node == nullptr) {
			return nullptr;
		} else if (node->left == nullptr) {
			return node->right;
		}
		node->left = removeMin(node->left);
		return balance(node);
	}

	template<class T>
	void AvlTree<T>::Remove(const T& value) {
		root = remove(root, value);
	}

	template<class T>
	const T& AvlTree<T>::CalcKStats(size_t k) const {
		T* result = nullptr;

		if (k < get_size(root)) {
			Node* node = root;
			size_t index = get_size(root->left);

			while (index != k) {
				if (k > index) {
					node = node->right;
					index += 1 + get_size(node->left);
				} else {
					node = node->left;
					index -= 1 + get_size(node->right);
				}
			}
			result = &node->value;
		} else {
			assert(false);
		}

		return *result;
	}

	template<class T>
	AvlTree<T>::Node::Node(const T& value) : value(value) {}

	template<class T>
	AvlTree<T>::Node::~Node() {
		delete left;
		delete right;
	}
}

int main() {
	size_t count;
	std::cin >> count;

	binarytree::AvlTree<int> tree;

	for (size_t i = 0; i < count; ++i) {
		int value;
		size_t k;

		std::cin >> value >> k;

		if (value < 0) {
			tree.Remove(-value);
		} else {
			tree.Insert(value);
		}

		std::cout << tree.CalcKStats(k) << std::endl;
	}

	return 0;
}