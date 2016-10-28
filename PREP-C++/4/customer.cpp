#include "customer.h"

#define coalesce(a, b) a ? a : b;

// Local Members
void strReplace(char*& destination, const char* source){
	if (!source) return;

	delete destination;
	
	destination = new char[strlen(source)];
	strcpy(destination, source);
}


int cstcmp(const Customer& c1, const Customer& c2){
	int lastName = strcmp(c1.GetLastName(), c2.GetLastName());
	if (lastName){
		return lastName;
	}

	int firstName = strcmp(c1.GetFirstName(), c2.GetFirstName());
	if (firstName){
		return firstName;
	}

	int middleName = strcmp(c1.GetMiddleName(), c2.GetMiddleName());
	if (middleName){
		return middleName;
	}

	int bankAccount = c1.GetBankAccount() - c2.GetBankAccount();
	if (bankAccount){
		return bankAccount;
	}

	int card = c1.GetCard() - c2.GetCard();
	return card;
}
// Private Methods

void Customer::freeValues(){
	delete firstName;
	delete lastName;
	delete middleName;
	delete address;
	delete phone;

	resetValues();
}

void Customer::resetValues(){
	firstName = NULL;
	lastName = NULL;
	middleName = NULL;
	address = NULL;
	phone = NULL;
	card = 0;
	bankAccount = 0;
	purchases = 0;
}

// Constructors & Desructors
Customer::Customer(){
	resetValues();
}

Customer::Customer(const char* firstName, 
				   const char* lastName,
				   unsigned int card) : Customer(){
	SetFirstName(firstName);
	SetLastName(lastName);
	SetCard(card);
}

Customer::Customer(const char* firstName, 
		 const char* lastName,
		 const char* middleName,
		 const char* address, 
		 const char* phone,
		 unsigned int card,
		 unsigned int bankAccount,
		 unsigned int purchases) : Customer(firstName, 
		 										lastName,
		 										card){
	SetMiddleName(middleName);
	SetBankAccount(bankAccount);
	SetPurchases(purchases);
	SetPhone(phone);
	SetAddress(address);
}

Customer::Customer(const Customer& c) : Customer()
{
	SetFirstName(c.firstName);
	SetLastName(c.lastName);
	SetMiddleName(c.middleName);
	SetPhone(c.phone);
	SetAddress(c.address);
	card = c.card;
	bankAccount = c.bankAccount;
	purchases = c.purchases;
}

Customer::~Customer(){
	freeValues();
}


// Operators Overloading
std::ostream& operator<<(std::ostream& ostream, const Customer& customer){
	ostream << customer.GetLastName() << ' ' <<
			   customer.GetFirstName() << ' ' <<
			   customer.GetMiddleName() << ' ' <<
			   customer.GetPhone() << ' ' <<
			   customer.GetAddress() << ' ' <<
			   customer.GetCard() << ' ' <<
			   customer.GetBankAccount() << ' ' <<
			   customer.GetPurchases();
	return ostream;
}

Customer& Customer::operator=(const Customer& customer){
	freeValues();

	SetFirstName(customer.firstName);
	SetLastName(customer.lastName);
	SetMiddleName(customer.middleName);
	SetPhone(customer.phone);
	SetAddress(customer.address);
	SetCard(customer.card);
	SetBankAccount(customer.bankAccount);
	SetPurchases(customer.purchases);

	return *this;
}

bool Customer::operator==(const Customer& customer) const{
	return cstcmp(*this, customer) == 0;
}

bool Customer::operator<(const Customer& customer) const{
	return cstcmp(*this, customer) < 0;
}

bool Customer::operator>(const Customer& customer) const{
	return cstcmp(*this, customer) > 0;
}

bool Customer::operator>=(const Customer& customer) const{
	return cstcmp(*this, customer) > 0;
}

bool Customer::operator<=(const Customer& customer) const{
	return cstcmp(*this, customer) > 0;
}

// Public Methods
void Customer::Show(std::ostream& ostream) const{
	ostream << *this;
}

void Customer::Show() const{
	Customer::Show(std::cout);
}

// Getters & Setters
void Customer::SetFirstName(const char* value){
	strReplace(firstName, value);
}

const char* Customer::GetFirstName() const{
	return coalesce(firstName, "No_First_Name");
}

void Customer::SetLastName(const char* value){
	strReplace(lastName, value);
}

const char* Customer::GetLastName() const{
	return coalesce(lastName, "No_Last_Name")
}

void Customer::SetMiddleName(const char* value){
	strReplace(middleName, value);
}

const char* Customer::GetMiddleName() const{
	return coalesce(middleName, "")
}

void Customer::SetAddress(const char* value){
	strReplace(address, value);
}

const char* Customer::GetAddress() const{
	return coalesce(address, "");
}

void Customer::SetPhone(const char* value){
	strReplace(phone, value);
}

const char* Customer::GetPhone() const{
	return coalesce(phone, "");
}

void Customer::SetCard(unsigned int value){
	Customer::card = value;
}

unsigned int Customer::GetCard() const{
	return card;
}

void Customer::SetBankAccount(unsigned int value){
	Customer::bankAccount = value;
}

unsigned int Customer::GetBankAccount() const{
	return bankAccount;
}

void Customer::SetPurchases(unsigned int value){
	Customer::purchases = value;
}

unsigned int Customer::GetPurchases() const{
	return purchases;
}