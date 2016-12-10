/**
 * @file
 *
 * 1_2.​ Для разрешения коллизий используйте двойное хеширование.
 */

#include <iostream>
#include <array>
#include <cassert>
#include <string>

namespace hash_table {
	namespace exceptions {
		/**
		 * @brief Exception that means that the key is already exists in the hash table.
		 */
		class KeyAlreadyExistsException : public std::exception {};

		/**
		 * @brief Exception that means that key does not exist in the hash table.
		 */
		class KeyNotExistsException : public std::exception {};

		/**
		 * @brief Exception that means that hash table is full.
		 */
		class HashTableOverflowException : public std::exception {};
	}

	/**
	 * @brief Hash table.
	 * @tparam HashFunc1 Hash function int(const T&).
	 * @tparam HashFunc2 Hash function int(const T&).
	 */
	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	class HashTable {
		public:
			/**
			 * @brief Default constructor.
			 */
			HashTable() = default;

			/**
			 * @brief Destructor.
			 */
			~HashTable();

			/**
			 * @brief Adds value to the hash table.
			 * @param value Value to add.
			 */
			void add(const T& value);

			/**
			 * @brief Removes value from the hash table.
			 * @param value Value to remove.
			 */
			void remove(const T& value);

			/**
			 * @brief Determines whether an element is in the hash table.
			 * @param value The value to locate in the hash table.
			 * @return if value is found in the hash table; otherwise, false.
			 */
			bool contains(const T& value) const;

			/**
			* @brief Returns number of elements.
			* @return Number of elements.
			*/
			int get_size() const;

		private:
			struct Node {
				T value;
				bool deleted = false;

				Node(const T& value);
			};

			void rehash();
			void rehash(int new_size);

			Node*& findToInsert(const T& value);
			Node* const& find(const T& value) const;

			int calcHash1(const T& string) const;
			int calcHash1(const T& string, int size) const;

			int calcHash2(const T& string) const;
			int calcHash2(const T& string, int size) const;

			double buffer_fill_factor() const;

			Node** data = nullptr;
			int buffer_size = 0;
			int size = 0;

			Node* NULL_NODE = nullptr;

	};

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	HashTable<T, HashFunc1, HashFunc2>::Node::Node(const T& value) : value(value) {

	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	HashTable<T, HashFunc1, HashFunc2>::~HashTable() {
		for (int i = 0; i < buffer_size; ++i) {
			delete data[i];
		}
		delete[] data;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	int HashTable<T, HashFunc1, HashFunc2>::get_size() const {
		return size;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	int HashTable<T, HashFunc1, HashFunc2>::calcHash1(const T& string) const {
		return calcHash1(string, buffer_size);
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	int HashTable<T, HashFunc1, HashFunc2>::calcHash1(const T& string, int size) const {
		return (std::abs(HashFunc1(string)) + 1) % size;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	int HashTable<T, HashFunc1, HashFunc2>::calcHash2(const T& string) const {
		return calcHash2(string, buffer_size);
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	int HashTable<T, HashFunc1, HashFunc2>::calcHash2(const T& string, int size) const {
		return (std::abs(HashFunc2(string)) + 1) % size;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	void HashTable<T, HashFunc1, HashFunc2>::add(const T& value) {
		if (buffer_fill_factor() >= 0.75) rehash();

		auto& item = findToInsert(value);
		if (item == NULL_NODE) {
			item = new Node(value);
		} else if (item->deleted) {
			item->value = value;
			item->deleted = false;
		}

		++size;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	bool HashTable<T, HashFunc1, HashFunc2>::contains(const T& value) const {
		try {
			find(value);
		} catch (exceptions::KeyNotExistsException&) {
			return false;
		}
		return true;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	void HashTable<T, HashFunc1, HashFunc2>::remove(const T& value) {
		auto& item = find(value);
		item->deleted = true;
		--size;

	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	double HashTable<T, HashFunc1, HashFunc2>::buffer_fill_factor() const {
		if (!buffer_size) return 1;
		return static_cast<double>(size) / buffer_size;
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	void HashTable<T, HashFunc1, HashFunc2>::rehash() {
		rehash(buffer_size ? buffer_size << 1 : 8);
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	void HashTable<T, HashFunc1, HashFunc2>::rehash(int new_size) {
		if (new_size <= buffer_size) {
			return;
		}
		auto old_data = data;
		auto old_buffer_size = buffer_size;

		buffer_size = new_size;
		data = new Node* [new_size];
		for (int i = 0; i < buffer_size; ++i) {
			data[i] = NULL_NODE;
		}

		if (old_data != nullptr) {
			for (int i = 0; i < old_buffer_size; ++i) {
				auto& item = old_data[i];

				// if node has been accessed
				if (item != NULL_NODE) {
					// if node is not deleted
					// copy to the new buffer
					if (!item->deleted) {
						findToInsert(item->value) = item;
					} else { // if not, remove it
						delete item;
					}
				}
			}
			delete[] old_data;
		}
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	typename HashTable<T, HashFunc1, HashFunc2>::Node*& HashTable<T, HashFunc1, HashFunc2>::findToInsert(
		const T& value) {
		if (buffer_fill_factor() >= 0.75) {
			rehash();
		}
		assert(data != nullptr);

		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		int i = 0;
		int result_index = -1;
		while (i < buffer_size) {
			Node*& node = data[h1];

			// if current node has been never accessed
			if (node == NULL_NODE) {
				// if it is first node that is valid for value
				if (result_index < 0) {
					result_index = h1;
				}

				// all forward nodes are invalid for value
				break;
			} else { // if current node has been already accessed
				// is node exists, but was deleted
				if (node->deleted) {
					// if it is first node that is valid for value
					if (result_index < 0) {
						result_index = h1;
					}
				} else if (node->value == value) { // if node has not been deleted and node's value is equal to value
					throw exceptions::KeyAlreadyExistsException();
				}
			}

			h1 = (h1 + h2 + 1) % buffer_size;
			++i;
		}

		assert(result_index >= 0);
		return data[result_index];
	}

	template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
	typename HashTable<T, HashFunc1, HashFunc2>::Node* const& HashTable<T, HashFunc1, HashFunc2>::find(
		const T& value) const {
		if (data == nullptr) {
			throw exceptions::KeyNotExistsException();
		}

		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		int i = 0;
		while (i < buffer_size) {
			Node*& node = data[h1];

			// if current node has been never accessed
			// all forward nodes are invalid for value
			if (node == NULL_NODE) {
				break;
			}

			// is node exists, has been never deleted and node's value is equal to value
			if (!node->deleted && node->value == value) {
				return node;
			}

			h1 = (h1 + h2 + 1) % buffer_size;
			++i;
		}

		// after iteration over the buffer the value was not found
		throw exceptions::KeyNotExistsException();
	}

}

namespace hash {
	/**
	 * @brief Always returns 1;
	 * @param value Input value.
	 * @return 1.
	 */
	template<class T>
	int BadHash(const T& value) {
		return 1;
	}

	/**
	 * @brief Calculates hash by hash algorithm 1.
	 * @param value Input value.
	 * @return Hash.
	 */
	int StringHash1(const std::string& value) {
		int hash = 0;
		for (auto& c: value) {
			hash += 17 * hash + c;
		}
		return hash;
	}

	/**
	 * @brief Calculates hash by hash algorithm 2.
	 * @param value Input value.
	 * @return Hash.
	 */
	int StringHash2(const std::string& value) {
		int hash = 0;
		for (auto& c: value) {
			hash += 19 * hash + c;
		}
		return 2 * hash + 1;
	}
}

/**
 * @brief Run code for testing system.
 * @param in Input stream.
 * @param out Output stream.
 */
template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
void Run(std::istream& in, std::ostream& out) {
	hash_table::HashTable<T, HashFunc1, HashFunc2> hash_table;

	char command;
	T value;
	while (in >> command >> value) {
		try {
			switch (command) {
				case '+':
					hash_table.add(value);
					break;
				case '-':
					hash_table.remove(value);
					break;
				case '?':
					if (!hash_table.contains(value)) throw 0;
					break;
				default:
					break;
			}
			out << "OK" << std::endl;
		} catch (hash_table::exceptions::HashTableOverflowException& e) {
			assert(false);
		} catch (...) {
			out << "FAIL" << std::endl;
		}
	}
};

/**
 * @brief Run code for testing system.
 */
template<class T, int HashFunc1(const T&), int HashFunc2(const T&)>
void Run() {
	Run<T, HashFunc1, HashFunc2>(std::cin, std::cout);
};

int main() {
	Run<std::string, hash::StringHash1, hash::StringHash2>();
	return 0;
}