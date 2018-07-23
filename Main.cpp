/*******************************************************************
*   File Name: Main.cpp
*	Name: Antoine Lynch
*   Programming Assignment 2
*
*   This program is entirely my own work
*******************************************************************/
#include <cstdlib>
#include "EmployeeRecord.h"
#include "Store.h"
#include "CustomerList.h"

//forward declarations
char * getRandomAddress();
char * getRandomStoreName();
char * getRandomCity();
int    getRandomId();
char * getRandomState();
char * getRandomZip();
Store * generateStore();

void testGenerateStore();

int main(int argc, char *argv[]) {
	char firstName[32] = "M.\0";
	char lastName[32] = "Manson\0";
	Store * t;
	Store * store = generateStore();
	store->setStoreID(101); //out of bounds of random geneator;
	EmployeeRecord *record = new EmployeeRecord();
	record->setID(2222);
	record->setName(firstName, lastName);
	record->setDept(666);
	record->setSalary(1111.00);
	for(int i = 0; i < 5; i++) {
		record->getCustomerList()->addStore(generateStore());
	}
	record->printRecord();
	cout << endl;
	cout << endl;
	cout << "============GetStoreTest==================" << endl;
	t = record->getCustomerList()->getStore(101);
	cout << "store not in list" << endl;
	if (t == NULL) {
		cout << "correct" << endl;
	}
	else {
		cout << "incorrect" << endl;
	}

	record->getCustomerList()->addStore(store);
	t = record->getCustomerList()->getStore(101);
	cout << "store in list" << endl;
	if (t == NULL) {
		cout << "incorrect" << endl;
	}
	else {
		cout << "correct" << endl;
	}

	cout << endl;
	cout << endl;
	cout << "============RemoveStoreTest==================" << endl;
	record->getCustomerList()->removeStore(101);
	cout << "store delete with valid store" << endl;
	if (t == NULL) {
		cout << "incorrect" << endl;
	}
	else {
		if (t->getStoreID() == 101) {
			cout << "correct" << endl;
		}
		else {
			cout << "incorrect" << endl;
		}
	}

	record->getCustomerList()->removeStore(101);
	cout << "store delete with invalid store" << endl;
	if (t == NULL) {
		cout << "correct" << endl;
	}
	else {
		cout << "incorrect" << endl;
	}


	delete record;
	return 0;
}