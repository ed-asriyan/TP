/**
 * @file
 *
 * 2_2. Выведите элементы в порядке pre-order (сверху вниз).
 */

#include <iostream>
#include <memory>

namespace binarytree {
	namespace exceptions {
		class ChildNotExists : public std::exception {
			public:
				virtual const char* what() const noexcept;
		};

		const char* ChildNotExists::what() const noexcept {
			return "Required child does not exists.";
		}
	}

	/**
	 * @brief Binary tree node.
	 */
	template<class T>
	class BinaryTreeNode {
		public:
			/**
			 * @brief Default constructor.
			 */
			BinaryTreeNode() = default;

			/**
			 * @brief Constructor.
			 * @param value Node value.
			 *
			 * Creates node without children.
			 */
			BinaryTreeNode(const T& value);

			/**
			 * @brief Copy constructor.
			 */
			BinaryTreeNode(const BinaryTreeNode&);

			/**
			 * @brief Destructor.
			 */
			~BinaryTreeNode();

			/**
			 * @brief Sets node value.
			 * @param value Value to set.
			 */
			void set_value(const T& value);

			/**
			 * @brief Returns node value.
			 * @return Node value.
			 */
			const T& get_value() const;

			/**
			 * @brief Returns reference to the left child.
			 * @return Reference to the left child.
			 */
			BinaryTreeNode& left();

			/**
			 * @brief Returns const reference to the left child.
			 * @return Const reference to the left child.
			 */
			const BinaryTreeNode& left() const;

			/**
			 * @brief Sets left node.
			 * @param left_node Left child.
			 */
			void set_left(const BinaryTreeNode& left_node);

			/**
			 * @brief Removes left child.
			 */
			void removeLeft();

			/**
			 * @brief Returns true if node has left child, false otherwise.
			 * @return True if node has left child, false otherwise.
			 */
			bool has_left() const;

			/**
			 * @brief Returns reference to the right child.
			 * @return Reference to the right child.
			 */
			BinaryTreeNode& right();

			/**
			 * @brief Returns const reference to the right child.
			 * @return Const reference to the right child.
			 */
			const BinaryTreeNode& right() const;

			/**
			 * @brief Sets right node.
			 * @param right_node Right child.
			 */
			void set_right(const BinaryTreeNode& right_node);

			/**
			 * @brief Removes right child.
			 */
			void removeRight();

			/**
			 * @brief Returns true if node has right child, false otherwise.
			 * @return True if node has right child, false otherwise.
			 */
			bool has_right() const;

			/**
			 * @brief Calculates tree depth.
			 * @return Tree depth.
			 */
			size_t calcDepth() const;

			/**
			 * @brief Calculates number of nodes in the tree.
			 * @return Number of nodes in the tree.
			 */
			size_t calcSize() const;

			BinaryTreeNode& operator=(const BinaryTreeNode&);

		private:
			T value;
			BinaryTreeNode* _left = nullptr;
			BinaryTreeNode* _right = nullptr;

	};

	template<class T>
	BinaryTreeNode<T>::BinaryTreeNode(const T& _value) : value(_value) {}

	template<class T>
	BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode& node) {
		*this = node;
	}

	template<class T>
	BinaryTreeNode<T>::~BinaryTreeNode() {
		if (has_left()) {
			delete _left;
		}
		if (has_right()) {
			delete _right;
		}
	}

	template<class T>
	void BinaryTreeNode<T>::set_value(const T& _value) {
		value = _value;
	}

	template<class T>
	const T& BinaryTreeNode<T>::get_value() const {
		return value;
	}

	template<class T>
	BinaryTreeNode<T>& BinaryTreeNode<T>::left() {
		if (!has_left()) throw exceptions::ChildNotExists();
		return *_left;
	}

	template<class T>
	const BinaryTreeNode<T>& BinaryTreeNode<T>::left() const {
		if (!has_left()) throw exceptions::ChildNotExists();
		return *_left;
	}

	template<class T>
	void BinaryTreeNode<T>::set_left(const BinaryTreeNode& left_node) {
		if (has_left()) {
			removeLeft();
		}
		_left = new BinaryTreeNode(left_node);
	}

	template<class T>
	void BinaryTreeNode<T>::removeLeft() {
		if (!has_left()) throw exceptions::ChildNotExists();
		delete _left;
	}

	template<class T>
	bool BinaryTreeNode<T>::has_left() const {
		return _left != nullptr;
	}

	template<class T>
	BinaryTreeNode<T>& BinaryTreeNode<T>::right() {
		if (!has_right()) throw exceptions::ChildNotExists();
		return *_right;
	}

	template<class T>
	const BinaryTreeNode<T>& BinaryTreeNode<T>::right() const {
		if (!has_right()) throw exceptions::ChildNotExists();
		return *_right;
	}

	template<class T>
	void BinaryTreeNode<T>::set_right(const BinaryTreeNode& right_node) {
		if (has_right()) {
			removeRight();
		}
		_right = new BinaryTreeNode(right_node);
	}

	template<class T>
	void BinaryTreeNode<T>::removeRight() {
		if (!has_right()) throw exceptions::ChildNotExists();
		delete _right;
	}

	template<class T>
	bool BinaryTreeNode<T>::has_right() const {
		return _right != nullptr;
	}

	template<class T>
	size_t BinaryTreeNode<T>::calcDepth() const {
		size_t depth_left = 0;
		size_t depth_right = 0;
		if (has_right()) {
			depth_right = _right->calcDepth();
		}
		if (has_left()) {
			depth_left = _left->calcDepth();
		}
		return std::max(depth_right, depth_left) + 1;
	}

	template<class T>
	size_t BinaryTreeNode<T>::calcSize() const {
		size_t depth_left = 0;
		size_t depth_right = 0;
		if (has_right()) {
			depth_right = _right->calcDepth();
		}
		if (has_left()) {
			depth_left = _left->calcDepth();
		}
		return depth_left + depth_right + 1;
	}

	template<class T>
	BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode& node) {
		value = node.value;
		if (node.has_left()) {
			set_left(node.left());
		}
		if (node.has_right()) {
			set_right(node.left());
		}
		return *this;
	}
}

namespace binarysearchtree {
	using binarytree::BinaryTreeNode;

	template<class T>
	class BinarySearchTree {
		public:
			/**
			 * @brief Default constructor.
			 *
			 * Root node is default.
			 */
			BinarySearchTree() = default;

			/**
			 * @brief Constructor.
			 * @param root_value Root node.
			 */
			BinarySearchTree(const T& root_value);

			/**
			 * @brief Searchs node with required value.
			 * @param value Value to search for.
			 * @return Node.
			 */
			const BinaryTreeNode<T>& find(const T& value) const;

			/**
			 * @brief Adds new node with value to the binary search tree.
			 * @param value Value to add.
			 */
			void add(const T& value);

			/**
			 * @brief Finds minimal element in the tree.
			 * @return Minimal element in the tree.
			 */
			const BinaryTreeNode<T>& findMin() const;

			/**
			 * @brief Finds minimal element in the tree.
			 * @return Minimal element in the tree.
			 */
			const BinaryTreeNode<T>& findMax() const;

			/**
			 * @brief Calculates tree depth.
			 * @return Tree depth.
			 */
			size_t calcDepth() const;

			/**
			 * @brief Returns const reference to root node.
			 * @return Const reference to root node.
			 */
			const BinaryTreeNode<T>& get_root() const;

		private:
			BinaryTreeNode<T> root;

			static void AddToSubSearchTree(BinaryTreeNode<T>& root, const T& value);
	};

	template<class T>
	BinarySearchTree<T>::BinarySearchTree(const T& root_value) : root(BinaryTreeNode<T>(root_value)) {}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::get_root() const {
		return root;
	}

	template<class T>
	size_t BinarySearchTree<T>::calcDepth() const {
		return root.calcDepth();
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::find(const T& value) const {
		auto* node = &root;
		while (node->get_value() != value) {
			bool has_left = node->has_left();
			bool has_right = node->has_right();
			if (!has_left && !has_right) {
				throw binarytree::exceptions::ChildNotExists();
			}
			if (value < node->get_value()) {
				node = &node->left();
			} else {
				node = &node->right();
			}
		}
		return *node;
	}

	template<class T>
	void BinarySearchTree<T>::add(const T& value) {
		AddToSubSearchTree(root, value);
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::findMin() const {
		auto* node = &root;
		while (node->has_left()) {
			node = &node->left();
		}
		return *node;
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::findMax() const {
		auto* node = &root;
		while (node->has_right()) {
			node = &node->right();
		}
		return *node;
	}

	template<class T>
	void BinarySearchTree<T>::AddToSubSearchTree(BinaryTreeNode<T>& root, const T& value) {
		auto& root_value = root.get_value();

		if (value < root_value) {
			if (root.has_left()) {
				AddToSubSearchTree(root.left(), value);
			} else {
				root.set_left(BinaryTreeNode<T>(value));
			}
		} else {
			if (root.has_right()) {
				AddToSubSearchTree(root.right(), value);
			} else {
				root.set_right(BinaryTreeNode<T>(value));
			}
		}
	}
}

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}