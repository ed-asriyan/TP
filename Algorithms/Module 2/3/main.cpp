/**
 * @file
 *
 * @brief Задача №3 (3 балла). Реклама
 *
 * В супермаркете решили оптимизировать показ рекламы. Известно расписание прихода и ухода покупателей (два целых
 * числа). Каждому покупателю необходимо показать минимум 2 рекламы. Рекламу можно транслировать только в
 * целочисленные моменты времени. Покупатель может видеть рекламу от момента прихода до момента ухода из магазина. В
 * каждый момент времени может показываться только одна реклама. Считается, что реклама показывается мгновенно. Если
 * реклама показывается в момент ухода или прихода, то считается, что посетитель успел её посмотреть. Требуется
 * определить минимальное число показов рекламы.
 *
 * Необходимо реализовать и использовать **​локальную пирамидальную сортировку** ​(без использования дополнительной
 * памяти). Общее время работы алгоритма `O(n log n)`.
 *
 * @date 06.11.2016
 */

#include <iostream>
#include <algorithm>

/**
 * @brief Represents shopping time span
 */
class ShoppingTimeSpan {
	private:
		int in_time = 0;
		int out_time = 0;

	public:
		/**
		 * @brief ShoppingTimeSpan constructor.
		 * @param in_time Time when shopper comes in.
		 * @param out_time Time when shopper goes out.
		 */
		ShoppingTimeSpan(int in_time, int out_time);

		bool CanWatch(int ad_time) const;

		bool operator<(const ShoppingTimeSpan& rhs) const;
		bool operator>(const ShoppingTimeSpan& rhs) const;
		bool operator<=(const ShoppingTimeSpan& rhs) const;
		bool operator>=(const ShoppingTimeSpan& rhs) const;
		bool operator==(const ShoppingTimeSpan& rhs) const;
		bool operator!=(const ShoppingTimeSpan& rhs) const;

		/**
		 * @brief Time when shopper comes in.
		 */
		int get_out_time() const;

		/**
		 * @brief Time when shopper goes out.
		 */
		int get_in_time() const;
};

ShoppingTimeSpan::ShoppingTimeSpan(int in_time, int out_time) : in_time(in_time), out_time(out_time) {}

bool ShoppingTimeSpan::operator<(const ShoppingTimeSpan& rhs) const {
	if (out_time < rhs.out_time) {
		return true;
	}
	if (rhs.out_time < out_time) {
		return false;
	}
	return in_time < rhs.in_time;
}

bool ShoppingTimeSpan::operator>(const ShoppingTimeSpan& rhs) const {
	return rhs < *this;
}

bool ShoppingTimeSpan::operator<=(const ShoppingTimeSpan& rhs) const {
	return !(rhs < *this);
}

bool ShoppingTimeSpan::operator>=(const ShoppingTimeSpan& rhs) const {
	return !(*this < rhs);
}

bool ShoppingTimeSpan::operator==(const ShoppingTimeSpan& rhs) const {
	return out_time == rhs.out_time &&
		in_time == rhs.in_time;
}

bool ShoppingTimeSpan::operator!=(const ShoppingTimeSpan& rhs) const {
	return !(rhs == *this);
}

int ShoppingTimeSpan::get_out_time() const {
	return out_time;
}

int ShoppingTimeSpan::get_in_time() const {
	return in_time;
}

bool ShoppingTimeSpan::CanWatch(int ad_time) const {
	return in_time <= ad_time && ad_time <= out_time;
}

/**
 * @brief Calculates reuqired number of ad impressions.
 * @param begin Iterator to the ititial position of the sorted sequence of ShoppingTimeSpan.
 * @param end Iterator to the final position of the sorted sequence of ShoppingTimeSpan.
 * @return Mininal reuqired number of ad impressions
 */
template<class ITERATOR>
int CalcRequiredAdNumber(const ITERATOR begin, const ITERATOR end) {
	// the exceptional case
	if (begin == end) {
		return 0;
	}

	// store only two last ad impressions
	int ad_time1 = begin->get_out_time();
	int ad_time2 = ad_time1 - 1;
	int result = 2;

	for (auto shopper = begin + 1; shopper != end; ++shopper) {
		const int shopper_out_time = shopper->get_out_time();

		// if the current shopper can not watch ad_time1
		if (!shopper->CanWatch(ad_time1)) {
			// if shopper_out_time is available for new ad, ad_time1 = shopper_out_time
			// if not, ad_time1 = shopper_out_time - 1
			ad_time1 = shopper_out_time - (ad_time2 == shopper_out_time);
			++result;
		}

		// if the current shopper can not watch ad_time2
		if (!shopper->CanWatch(ad_time2)) {
			// if shopper_out_time is available for new ad, ad_time2 = shopper_out_time
			// if not, ad_time2 = shopper_out_time - 1
			ad_time2 = shopper_out_time - (ad_time1 == shopper_out_time);
			++result;
		}
	}

	return result;
}

int main() {
	int shopper_count = 0;
	std::cin >> shopper_count;

	// create shoppers array
	ShoppingTimeSpan*
		shoppers = static_cast<ShoppingTimeSpan*>(operator new[](sizeof(ShoppingTimeSpan) * shopper_count));
	for (int i = 0; i < shopper_count; ++i) {
		int in = 0;
		int out = 0;
		std::cin >> in >> out;

		new(shoppers + i)ShoppingTimeSpan(in, out);
	}

	// todo: implement the sort function and use it instead of std::sort
	std::sort(shoppers, shoppers + shopper_count);
	std::cout << CalcRequiredAdNumber(shoppers, shoppers + shopper_count) << std::endl;

	// free shoppers array
	for (int i = shopper_count - 1; i >= 0; --i) {
		shoppers[i].~ShoppingTimeSpan();
	}
	operator delete[](shoppers);

	return 0;
}