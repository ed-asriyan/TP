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
		private:
			T value;
			BinaryTreeNode* _left = nullptr;
			BinaryTreeNode* _right = nullptr;

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

			BinaryTreeNode& operator=(const BinaryTreeNode&);

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
	const T& BinaryTreeNode::get_value() const {
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
		size_t depth = 1;
		if (has_right()) {
			depth += _right->calcDepth();
		}
		if (has_left()) {
			depth += _left->calcDepth();
		}
		return depth;
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

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}