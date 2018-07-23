/*******************************************************************
*   File Name: CustomerList.h
*	Name: Antoine Lynch
*   Programming Assignment 2
*
*   This program is entirely my own work
*******************************************************************/
#pragma once

#include "Store.h"

class CustomerList {
private:
	Store * m_pHead;

public:
	CustomerList();
	bool addStore(Store *s);
	Store *removeStore(int ID);
	Store *getStore(int ID);
	bool updateStore(int ID, char *name, char *addr, char *city, char *st, char *zip);
	void printStoresInfo();
};