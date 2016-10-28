#include <iostream>

class Solver {
	private:
		long** data;
		long size;

	public:
		Solver(long n) {
			data = new long* [n + 1];
			for (long i = 0; i <= n; ++i) {
				data[i] = new long[n + 1];
				data[i][0] = 0;
				for (long j = 1; j <= n; ++j) {
					data[i][j] = -1;
				}
			}
			data[0][0] = 1;
			size = n;
		}

		~Solver() {
			for (long i = 0; i <= size; ++i) {
				delete[] data[i];
			}
			delete data;
		}

		long Solve() {
			return solve(size, size);
		}

	private:
		long solve(long n, long k) {
			long& value = data[n][k];
			if (value < 0) {
				if (!n && !k) {
					value = 1;
				} else if (!k) {
					value = 0;
				} else if (k <= n) {
					value = solve(n, k - 1) + solve(n - k, k);
				} else {
					value = solve(n, n);
				}
			}

			return value;
		}
};

int main() {
	long n = 0;
	std::cin >> n;

	Solver s(n);
	std::cout << s.Solve() << '\n';

	return 0;
}