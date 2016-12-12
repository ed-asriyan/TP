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
		auto diff = static_cast<int>(get_height(node->right)) - static_cast<int>(get_height(node->left));
		assert(-2 <= diff && diff <= 2);
		return diff;
	}

	template<class T>
	void AvlTree<T>::fixHeight(Node* node) {
		if (node == nullptr) return;
		auto h_left = get_height(node->left);
		auto h_right = get_height(node->right);
		node->height = std::max(h_left, h_right) + 1;
	}

	template<class T>
	void AvlTree<T>::fixSize(Node* node) {
		if (node == nullptr) return;
		auto s_left = get_size(node->left);
		auto s_right = get_size(node->right);
		node->size = s_left + s_right + 1;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::rotateRight(AvlTree::Node* p) {
		if (p == nullptr) return nullptr;

		Node* q = p->left;
		p->left = p->right;
		q->right = p;

		fixHeight(p);
		fixSize(p);
		fixHeight(q);
		fixSize(q);

		return q;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::rotateLeft(Node* q) {
		if (q == nullptr) return nullptr;

		Node* p = q->right;
		q->right = p->left;
		p->left = q;

		fixHeight(q);
		fixSize(q);
		fixHeight(p);
		fixSize(p);

		return p;
	}

	template<class T>
	typename AvlTree<T>::Node* AvlTree<T>::balance(Node* p) {
		if (p == nullptr) {
			return nullptr;
		}

		fixHeight(p);
		fixSize(p);

		if (calcBalanceFactor(p) == 2) {
			if (calcBalanceFactor(p->right) < 0) {
				p->right = rotateRight(p->right);
			}
			return rotateLeft(p);
		}
		if (calcBalanceFactor(p) == -2) {
			if (calcBalanceFactor(p->left) > 0) {
				p->left = rotateLeft(p->left);
			}
			return rotateRight(p);
		}

		return p;
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
				Node* temp = node->left == nullptr ? node->right : node->left;

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
		remove(root, value);
	}

	template<class T>
	const T& AvlTree<T>::CalcKStats(size_t k) const {
		T* result = nullptr;

		if (k < get_size(root)) {
			Node* p = root;
			auto k_index = get_size(p->left);

			while (k_index != k) {
				if (k > k_index) {
					p = p->right;
					k_index += get_height(p->left) + 1;
				} else {
					p = p->left;
					k_index -= get_height(p->right) + 1;
				}
			}

			result = &p->value;
		} else {
			assert(false);
		};

		return *result;
	}

	template<class T>
	AvlTree<T>::Node::Node(const T& value) : value(value) {
	}

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