/**
 * @file
 *
 * 3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
 */

#include <iostream>
#include <functional>

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
			 * @brief Move constructor.
			 */
			BinaryTreeNode(BinaryTreeNode&&);

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

			/**
			 * @brief Traverses from up to down.
			 * @param func Function which is call on each step.
			 */
			void traverseDfsPreOrder(std::function<void(const BinaryTreeNode<T>&)> func) const;

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
	BinaryTreeNode<T>::BinaryTreeNode(BinaryTreeNode&& node)
		: value(std::move(node.value)), _left(node._left), _right(node._right) {}

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

	template<class T>
	void BinaryTreeNode<T>::traverseDfsPreOrder(std::function<void(const BinaryTreeNode&)> func) const {
		func(*this);
		if (has_left()) {
			left().traverseDfsPreOrder(func);
		}
		if (has_right()) {
			right().traverseDfsPreOrder(func);
		}
	}
}

namespace binarytree {
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
			 * @brief Searches node with required value.
			 * @param value Value to search for.
			 * @return Node.
			 */
			const BinaryTreeNode<T>& find(const T& value) const;

			/**
			 * @brief Searches node with required value.
			 * @param value Value to search for.
			 * @param node Subtree.
			 * @return Node.
			 */
			const BinaryTreeNode<T>& find(const T& value, const BinaryTreeNode<T>& node) const;

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
			void throwIfEmpty() const;

			BinaryTreeNode<T>* root = nullptr;

	};

	template<class T>
	BinarySearchTree<T>::BinarySearchTree(const T& root_value) : root(new BinaryTreeNode<T>(root_value)) {}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::get_root() const {
		throwIfEmpty();
		return *root;
	}

	template<class T>
	size_t BinarySearchTree<T>::calcDepth() const {
		throwIfEmpty();
		return root->calcDepth();
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::find(const T& value) const {
		throwIfEmpty();
		return find(value, root);
	}

	template<class T>
	void BinarySearchTree<T>::add(const T& value) {
		if (root == nullptr) {
			root = new BinaryTreeNode<T>(value);
			return;
		}

		BinaryTreeNode<T>* current = root;
		while (true) {
			if (value < current->get_value()) {
				if (current->has_left()) {
					current = &current->left();
				} else {
					current->set_left(BinaryTreeNode<T>(value));
					break;
				}
			} else {
				if (current->has_right()) {
					current = &current->right();
				} else {
					current->set_right(BinaryTreeNode<T>(value));
					break;
				}
			}
		}

	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::findMin() const {
		throwIfEmpty();
		auto* node = root;
		while (node->has_left()) {
			node = &node->left();
		}
		return *node;
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::findMax() const {
		throwIfEmpty();

		auto* node = root;
		while (node->has_right()) {
			node = &node->right();
		}
		return *node;
	}

	template<class T>
	const BinaryTreeNode<T>& BinarySearchTree<T>::find(const T& value, const BinaryTreeNode<T>& _node) const {
		throwIfEmpty();

		auto* node = &_node;
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
	void BinarySearchTree<T>::throwIfEmpty() const {
		if (root == nullptr) {
			throw exceptions::ChildNotExists();
		}
	}

}

namespace binarytree {
	template<class X, class Y>
	class Treap {
		public:
			/**
			 * @brief Default constructor;
			 */
			Treap() = default;

			/**
			 * @brief Destructor.
			 */
			~Treap();

			/**
			 * @brief Adds new node with value to the treep.
			 * @param value Value to add.
			 */
			void add(const X& key, const Y& priority);

			/**
			 * @brief Calculates treap depth.
			 * @return Treap depth.
			 */
			size_t calcDepth() const;

		private:
			struct Node {
				X key;
				Y priority;

				Node* left = nullptr;
				Node* right = nullptr;

				Node(X key, Y priority);
				~Node();
			};

			Node* merge(Node* left, Node* right);

			void split(Node* current_node, const X& key, Node*& left, Node*& right);

			size_t depth(const Node* node) const;

			Node* root = nullptr;
	};

	template<class X, class Y>
	Treap<X, Y>::Node::Node(X key, Y priority) : key(key), priority(priority) {}

	template<class X, class Y>
	Treap<X, Y>::Node::~Node() {
		delete left;
		delete right;
	}

	template<class X, class Y>
	typename Treap<X, Y>::Node* Treap<X, Y>::merge(Treap<X, Y>::Node* left, Treap<X, Y>::Node* right) {
		if (left == nullptr || right == nullptr) {
			return left == nullptr ? right : left;
		}

		if (left->priority > right->priority) {
			left->right = merge(left->right, right);
			return left;
		} else {
			right->left = merge(left, right->left);
			return right;
		}
	}

	template<class X, class Y>
	void Treap<X, Y>::split(Treap<X, Y>::Node* current_node,
	                        const X& key,
	                        Node*& left,
	                        Node*& right) {
		if (current_node == nullptr) {
			left = nullptr;
			right = nullptr;
		} else if (current_node->key <= key) {
			split(current_node->right, key, current_node->right, right);
			left = current_node;
		} else {
			split(current_node->left, key, left, current_node->left);
			right = current_node;
		}
	}

	template<class X, class Y>
	Treap<X, Y>::~Treap() {
		delete root;
	}

	template<class X, class Y>
	void Treap<X, Y>::add(const X& key, const Y& priority) {
		auto* node = new Node(key, priority);
		Node* split_left = nullptr;
		Node* split_right = nullptr;
		split(root, key, split_left, split_right);
		root = merge(merge(split_left, node), split_right);
	}

	template<class X, class Y>
	size_t Treap<X, Y>::calcDepth() const {
		return depth(root);
	}

	template<class X, class Y>
	size_t Treap<X, Y>::depth(const Treap<X, Y>::Node* node) const {
		if (node == nullptr) {
			return 0;
		} else {
			return std::max(depth(node->left), depth(node->right)) + 1;
		}
	}
}

int main() {
	size_t n;
	std::cin >> n;

	binarytree::BinarySearchTree<int> tree;
	binarytree::Treap<int, int> treap;

	for (size_t i = 0; i < n; ++i) {
		int key, priority;
		std::cin >> key >> priority;

		tree.add(key);
		treap.add(key, priority);
	}

	std::cout << (static_cast<int>(tree.calcDepth()) - static_cast<int>(treap.calcDepth())) << std::endl;
	return 0;
}