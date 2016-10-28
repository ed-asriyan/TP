#include <iostream>
#include <string>
#include <fstream>
#include <functional>

#include "customer.h"

using namespace std;

template<typename T> void swap(T* a, T* b){
	T tmp = *a;
	*a = *b;
	*b = tmp;
}

void readFromStream(istream& stream, Customer* array, int count){
	for (int i = 0; i < count; i++, array++){
		if (&stream == &cin) {
			cout << "Enter customer (first name, last name, middle name, ";
			cout << "phone, card, bank account, purchases):\n";
		}

		string firstName,
			   lastName,
			   middleName,
			   phone, address;
		unsigned int card, bank, purchases;

		stream >> lastName >> firstName >> middleName >> phone >> address;
		stream >> card >> bank >> purchases;

		array->SetFirstName(firstName.c_str());
		array->SetLastName(lastName.c_str());
		array->SetMiddleName(middleName.c_str());
		array->SetPhone(phone.c_str());
		array->SetAddress(address.c_str());
		array->SetCard(card);
		array->SetBankAccount(bank);
		array->SetPurchases(purchases);
	}
}

void sort(Customer* array, int count){
	for (int i = 0; i < count - 1; i++){
		Customer* w = array;
		for (int j = 0; j < count - i - 1; j++){
			if (*w > *(w + 1)){
				swap<Customer>(w, w + 1);
			}

			w++;
		}
	}
}

void Show(Customer* customers, int count, const function<bool(const Customer*)>& filter = NULL){
	int empty = true;
	for (int i = 0; i < count; i++, customers++){
		if (!filter || filter(customers)){
			cout << "- ";
			customers->Show();
			cout << '\n';
			empty = false;
		}
	}

	if (empty){
		cout << " [ Empty list ]\n";
	}
}


int main(int argc, char* argv[]){
	Customer* base;
	int count;
	if (argc != 2){
		cout << "Enter count of customers: ";
		cin >> count;
		base = new Customer[count];
		readFromStream(cin, base, count);
	} else {
		ifstream stream;
		stream.open(argv[1]);
		stream >> count;
		base = new Customer[count];
		readFromStream(stream, base, count);
		stream.close();
	}

	cout << "\nBase has been loaded.\n";

	sort(base, count);
	cout << "Base has been sorted.\n";

	cout << "\nCustomer list (" << count << "):\n";
	Show(base, count);


	int min, max;
	cout << "\nEnter lower card number border: ";
	cin >> min;
	cout << "Enter highter card number border: ";
	cin >> max;
	if (min > max){
		swap(&min, &max);
	}

	cout << "Filtered by card customer list:\n";
	Show(base, count, [min, max] (const Customer* customer) -> bool {
		int card = customer->GetCard();
		return (min <= card) && (card <= max);
	});


	int maxPurchase;
	cout << "\nEnter lower purchase border: ";
	cin >> maxPurchase;

	cout << "Filtered by purchases customer list:\n";
	Show(base, count, [maxPurchase] (const Customer* customer) -> bool {
		return customer->GetPurchases() > maxPurchase;
	});

	return 0;
}