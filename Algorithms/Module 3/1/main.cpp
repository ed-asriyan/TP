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

	namespace hash {
		/**
		 * @brief Always returns 0;
		 * @param value Input value.
		 * @return 1.
		 */
		int BadHash(const std::string& value) {
			return 1;
		}

		/**
		 * @brief Calculates hash by hash algorithm 1.
		 * @param value Input value.
		 * @return Hash.
		 */
		int Hash1(const std::string& value) {
			int hash = 0;
			for (int i = static_cast<int>(value.size() - 1); i >= 0; i--) {
				hash += (17 * hash + value[i]);
			}
			return hash;
		}

		/**
		 * @brief Calculates hash by hash algorithm 2.
		 * @param value Input value.
		 * @return Hash.
		 */
		int Hash2(const std::string& value) {
			int hash = 0;
			for (int i = static_cast<int>(value.size() - 1); i >= 0; i--) {
				hash += (19 * hash + value[i]);
			}
			return 2 * hash + 1;
		}
	}

	/**
	 * @brief Hash table of strings.
	 * @tparam HashFunc1 Hash function int(const std::string&).
	 * @tparam HashFunc2 Hash function int(const std::string&).
	 */
	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	class StringHashTable {
		public:
			/**
			 * @brief Default constructor.
			 */
			StringHashTable();

			/**
			 * @brief Destructor.
			 */
			~StringHashTable();

			/**
			 * @brief Adds value to the hash table.
			 * @param value Value to add.
			 */
			void add(const std::string& value);

			/**
			 * @brief Removes value from the hash table.
			 * @param value Value to remove.
			 */
			void remove(const std::string& value);

			/**
			 * @brief Determines whether an element is in the hash table.
			 * @param value The value to locate in the hash table.
			 * @return if value is found in the hash table; otherwise, false.
			 */
			bool contains(const std::string& value) const;

			/**
			* @brief Returns number of elements.
			* @return Number of elements.
			*/
			int get_size() const;

		private:
			struct Node {
				std::string value;
				bool deleted = false;

				Node(const std::string& value);
			};

			void rehash();
			void rehash(int new_size);

			Node*& findToInsert(const std::string& value);
			Node* const& findToInsert(const std::string& value) const;

			int calcHash1(const std::string& string) const;
			int calcHash1(const std::string& string, int size) const;

			int calcHash2(const std::string& string) const;
			int calcHash2(const std::string& string, int size) const;

			double alpha() const;

			Node** data = nullptr;
			int buffer_size = 8;
			int size = 0;

	};

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	StringHashTable<HashFunc1, HashFunc2>::Node::Node(const std::string& value) : value(value) {

	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	StringHashTable<HashFunc1, HashFunc2>::StringHashTable() {
		rehash(8);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	StringHashTable<HashFunc1, HashFunc2>::~StringHashTable() {
		for (int i = 0; i < buffer_size; ++i) {
			delete data[i];
		}
		delete[] data;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	int StringHashTable<HashFunc1, HashFunc2>::get_size() const {
		return size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	int StringHashTable<HashFunc1, HashFunc2>::calcHash1(const std::string& string) const {
		return calcHash1(string, buffer_size);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	int StringHashTable<HashFunc1, HashFunc2>::calcHash1(const std::string& string, int size) const {
		return HashFunc1(string) % size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	int StringHashTable<HashFunc1, HashFunc2>::calcHash2(const std::string& string) const {
		return calcHash2(string, buffer_size);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	int StringHashTable<HashFunc1, HashFunc2>::calcHash2(const std::string& string, int size) const {
		return HashFunc2(string) % size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	void StringHashTable<HashFunc1, HashFunc2>::add(const std::string& value) {
		if (alpha() >= 0.75) rehash();

		auto& item = findToInsert(value);
		if (item == nullptr) {
			item = new Node(value);
		} else if (item->deleted) {
			item->value = value;
			item->deleted = false;
		} else {
			throw exceptions::KeyAlreadyExistsException();
		}

		++size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	bool StringHashTable<HashFunc1, HashFunc2>::contains(const std::string& value) const {
		auto& item = findToInsert(value);
		return item != nullptr && !item->deleted;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	void StringHashTable<HashFunc1, HashFunc2>::remove(const std::string& value) {
		auto& item = findToInsert(value);

		if (item == nullptr || item->deleted) {
			throw exceptions::KeyNotExistsException();
		} else {
			item->deleted = true;
			--size;
		}
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	double StringHashTable<HashFunc1, HashFunc2>::alpha() const {
		return static_cast<double>(size) / buffer_size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	void StringHashTable<HashFunc1, HashFunc2>::rehash() {
		rehash(buffer_size << 1);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	void StringHashTable<HashFunc1, HashFunc2>::rehash(int new_size) {
		auto old_data = data;
		auto old_buffer_size = buffer_size;

		buffer_size = new_size;
		data = new Node* [new_size];
		for (int i = 0; i < buffer_size; ++i) {
			data[i] = nullptr;
		}

		if (old_data != nullptr) {
			for (int i = 0; i < old_buffer_size; ++i) {
				const auto& item = old_data[i];
				if (item != nullptr) {
					if (!item->deleted) {
						findToInsert(item->value) = item;
					}
				}
			}
			delete[] old_data;
		}
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	typename StringHashTable<HashFunc1, HashFunc2>::Node*& StringHashTable<HashFunc1, HashFunc2>::findToInsert(const std::string& value) {
		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		int i = 0;
		while ((data[h1] != nullptr && !data[h1]->deleted && data[h1]->value != value) && i < buffer_size) {
			h1 = (h1 + h2) % buffer_size;
			++i;
		}

		assert(i != buffer_size);
		return data[h1];
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	typename StringHashTable<HashFunc1, HashFunc2>::Node* const& StringHashTable<HashFunc1, HashFunc2>::findToInsert(
		const std::string& value) const {
		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		int i = 0;
		while ((data[h1] != nullptr && !data[h1]->deleted && data[h1]->value != value) && i < buffer_size) {
			h1 = (h1 + h2) % buffer_size;
			++i;
		}

		assert(i != buffer_size);
		return data[h1];
	}

}

int main() {
	hash_table::StringHashTable<hash_table::hash::Hash1, hash_table::hash::Hash2> hash_table;

	char command;
	std::string str;
	while (std::cin >> command >> str) {
		try {
			switch (command) {
				case '+': hash_table.add(str);
					break;
				case '-': hash_table.remove(str);
					break;
				case '?': if (!hash_table.contains(str)) throw 0;
					break;
				default: break;
			}

			std::cout << "OK" << std::endl;
		} catch (hash_table::exceptions::HashTableOverflowException& e) {
			assert(false);
		} catch (...) {
			std::cout << "FAIL" << std::endl;
		}
	}

	return 0;
}