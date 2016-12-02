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

		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		for (int i = 0; i < buffer_size; ++i) {
			auto& item = data[h1];

			if (item == nullptr) {
				item = new Node(value);

				++size;
				return;
			} else if (item->deleted) {
				item->value = value;
				item->deleted = false;

				++size;
				return;
			} else if (item->value == value) {
				throw exceptions::KeyAlreadyExistsException();
			}

			h1 = (h1 + h2) % buffer_size;
		}

		assert(false);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	bool StringHashTable<HashFunc1, HashFunc2>::contains(const std::string& value) const {
		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		for (int i = 0; i < buffer_size; ++i) {
			if (data[h1] != nullptr) {
				if (!data[h1]->deleted && data[h1]->value == value) {
					return true;
				}
			}

			h1 = (h1 + h2) % buffer_size;
		}

		return false;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&)>
	void StringHashTable<HashFunc1, HashFunc2>::remove(const std::string& value) {
		auto h1 = calcHash1(value);
		auto h2 = calcHash2(value);

		for (int i = 0; i < buffer_size; ++i) {
			auto& item = data[h1];

			if (item != nullptr) {
				if (!item->deleted) {
					if (item->value == value) {
						item->deleted = true;
						--size;
						return;
					}
				}
			} else {
				break;
			}

			h1 = (h1 + h2) % buffer_size;
		}

		throw exceptions::KeyNotExistsException();
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
		Node** new_data = new Node* [new_size];

		for (int i = 0; i < new_size; ++i) {
			new_data[i] = nullptr;
		}

		if (data != nullptr) {
			for (int i = 0; i < buffer_size; ++i) {
				auto& item = data[i];

				if (item != nullptr && !item->deleted) {
					auto h1 = calcHash1(item->value, new_size);
					auto h2 = calcHash2(item->value, new_size);

					for (int j = 0; j < new_size && new_data[j] != nullptr; ++j) {
						h1 += (h1 + h2) % new_size;
					}

					new_data[h1] = data[i];
				}
			}

			delete[] data;
		}

		buffer_size = new_size;
		data = new_data;
	}
}

int main() {
	hash_table::StringHashTable<hash_table::hash::BadHash, hash_table::hash::BadHash> hash_table;

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
		} catch (...) {
			std::cout << "FAIL" << std::endl;
		}
	}

	return 0;
}