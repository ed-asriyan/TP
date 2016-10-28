// Author: Eduard Asriyan
//
// The problem:
// 5_1. Скобочная последовательность.
// Дан фрагмент последовательности скобок, состоящей из символов (){}[].
// Требуется определить, возможно ли продолжить фрагмент в обе стороны,
// получив корректную последовательность.
// Длина исходной последовательности ≤ 200000.
// Формат входных данных. Строка, содержащая символы (){}[] и, возможно,
// перевод строки.
// Формат выходных данных. Если возможно ­ вывести минимальную корректную
// последовательность, иначе ­ напечатать " ​ IMPOSSIBLE​ ".


#include <iostream>
#include <string>

template<class T>
class Stack {
	private:
		struct Node {
			Node(Node* prev_, const T& value_) {
				prev = prev_;
				value = value_;
			}

			Node* prev;
			T value;
		};

		Node* top;
		int size;
	public:
		Stack() {
			init();
		}

		Stack(const Stack<T>& stack) {
			init();
			*this = stack;
		}

		~Stack() {
			clear();
		}

		T& Top() {
			return top->value;
		}

		const T& Top() const {
			return top->value;
		}

		void Push(const T& value) {
			Node* new_node = new Node(top, value);
			top = new_node;
			++size;
		}

		T Pop() {
			T result = top->value;
			Node* result_node = top;
			top = top->prev;
			delete result_node;

			--size;
			return result;
		}

		Stack<T> Reversed() const {
			Stack<T> result;

			Node* curr_node = top;
			for (int i = size - 1; i >= 0; --i) {
				result.Push(curr_node->value);
				curr_node = curr_node->prev;
			}

			return result;
		}

		int get_size() const {
			return size;
		}

		Stack<T>& operator=(const Stack<T>& stack) {
			clear();

			int stack_size = stack.get_size();

			Node** path = new Node* [stack_size];
			Node* curr_node = stack.top;
			for (int i = stack_size - 1; i >= 0; --i) {
				path[i] = curr_node;
				curr_node = curr_node->prev;
			}

			for (int i = 0; i < stack_size; ++i) {
				Push(path[i]->value);
			}

			delete[] path;
		}
	private:
		void init() {
			top = NULL;
			size = 0;
		}

		void clear() {
			while (top != NULL) {
				Pop();
			}
		}
};

namespace BracketRepairer {
	const char* RULE = "()[]{}";

	int FindInStr(char symb, const char* str) {
		for (int i = 0; *str; ++i, ++str) {
			if (symb == *str) {
				return i;
			}
		}
		return -1;
	}

	bool IsOpen(char c) {
		int search_result = FindInStr(c, RULE);
		return search_result >= 0 && !(search_result % 2);
	}

	bool IsClose(char c) {
		int search_result = FindInStr(c, RULE);
		return search_result >= 0 && (search_result % 2);
	}

	char FindPair(char c) {
		int search_result = FindInStr(c, RULE);
		if (search_result < 0) {
			return '\0';
		}

		search_result += search_result % 2 ? -1 : 1;
		return RULE[search_result];
	}

	std::string RepairSequence(const std::string& input) {
		Stack<char> stack;
		for (std::string::const_iterator it = input.begin(); it != input.end(); ++it) {
			char tmp = *it;

			int bracket_index = FindInStr(tmp, RULE);

			if (bracket_index < 0) {
				break;
			}

			if (bracket_index % 2 && stack.get_size() &&
				IsOpen(stack.Top())) {
				if (stack.Top() == FindPair(tmp)) {
					stack.Pop();
				} else {
					return "IMPOSSIBLE";
				}
			} else {
				stack.Push(tmp);
			}
		}

		std::string left;
		std::string right;

		while (stack.get_size()) {
			char tmp = FindPair(stack.Pop());

			if (IsOpen(tmp)) {
				left.push_back(tmp);
			} else {
				right.push_back(tmp);
			}
		}

		return left + input + right;
	}
}

int main() {
	std::string input;
	std::cin >> input;

	std::cout << BracketRepairer::RepairSequence(input);

	return 0;
}