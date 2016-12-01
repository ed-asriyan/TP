/**
 * @file
 *
 * 1_2.​ Для разрешения коллизий используйте двойное хеширование.
 */

#include <iostream>
#include <array>
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
		 * @return 0
		 */
		int BadHash(const std::string& value) {
			return 0;
		}

	}

	/**
	 * @brief Hash table of strings.
	 * @tparam HashFunc1 Hash function int(const std::string&).
	 * @tparam HashFunc2 Hash function int(const std::string&).
	 */
	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&), int BufferSize>
	class StringHashTable {
		public:
			/**
			 * @brief Default constructor.
			 */
			StringHashTable();

			/**
			* @brief Returns number of elements.
			* @return Number of elements.
			*/
			size_t get_size() const;

		private:
			struct Node {
				std::string value;
				bool deleted = false;
			};

			int calcHash1(const std::string& string) const;
			int calcHash2(const std::string& string) const;

			std::array<Node*, BufferSize> data;

			size_t size = 0;

	};

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&), int BufferSize>
	StringHashTable<HashFunc1, HashFunc2, BufferSize>::StringHashTable() {
		data.fill(nullptr);
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&), int BufferSize>
	size_t StringHashTable<HashFunc1, HashFunc2, BufferSize>::get_size() const {
		return size;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&), int BufferSize>
	int StringHashTable<HashFunc1, HashFunc2, BufferSize>::calcHash1(const std::string& string) const {
		return HashFunc1(string) % BufferSize;
	}

	template<int HashFunc1(const std::string&), int HashFunc2(const std::string&), int BufferSize>
	int StringHashTable<HashFunc1, HashFunc2, BufferSize>::calcHash2(const std::string& string) const {
		return HashFunc2(string) % BufferSize;
	}

}

int main() {
	std::cout << "Hello, World!" << std::endl;
	return 0;
}