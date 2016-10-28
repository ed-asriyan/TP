#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string.h>
#include <iostream>
#include <string>

class Customer
{
private:
	// Privarte Members
	char* firstName;
	char* lastName;
	char* middleName;

	char* address;
	char* phone;
	unsigned int card;
	unsigned int bankAccount;

	unsigned int purchases;

	void freeValues();
	void resetValues();
public:
	// Constructors & Destructors
	Customer();
	Customer(const char* firstName, 
			 const char* lastName,
			 unsigned int card);
	Customer(const char* firstName, 
			 const char* lastName,
			 const char* middleName,
			 const char* address,
			 const char* phone,
			 unsigned int card,
			 unsigned int bankAccount,
			 unsigned int purchases = 0);
	Customer(const Customer&);
	~Customer();

	// Operators overloading
	friend std::ostream& operator<<(std::ostream&, const Customer&);
	Customer& operator=(const Customer&);
	bool operator==(const Customer&) const;
	bool operator<(const Customer&) const;
	bool operator>(const Customer&) const;
	bool operator>=(const Customer&) const;
	bool operator<=(const Customer&) const;

	// Public Members
	void Show(std::ostream&) const;
	void Show() const;


	// Getters & Setters
	void SetFirstName(const char*);
	const char* GetFirstName() const;

	void SetLastName(const char*);
	const char* GetLastName() const;

	void SetMiddleName(const char*);
 	const char* GetMiddleName() const;

	void SetAddress(const char*);
	const char* GetAddress() const;

	void SetPhone(const char*);
	const char* GetPhone() const;

	void SetCard(unsigned int);
	unsigned int GetCard() const;

	void SetBankAccount(unsigned int);
	unsigned int GetBankAccount() const;

	void SetPurchases(unsigned int);
	unsigned int GetPurchases() const;
};

#endif