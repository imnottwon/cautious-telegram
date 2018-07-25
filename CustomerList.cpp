
/*******************************************************************
*   File Name: CustomerList.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*
*   This program is entirely my own work
*******************************************************************/
#include "CustomerList.h"
#include "Store.h"
#include <iostream>


CustomerList::CustomerList() {
	m_pHead = NULL;
}

bool CustomerList::addStore(Store *s) {

	Store * cur = m_pHead;
	if (m_pHead == NULL || m_pHead->getStoreID() >= s->getStoreID())
	{
		s->m_pNext = m_pHead;
		m_pHead = s;
	} else {
		cur = m_pHead;
		while (cur->m_pNext != NULL && cur->m_pNext->getStoreID() < s->getStoreID())
		{
			cur = cur->m_pNext;
		}
		s->m_pNext= cur->m_pNext;
		cur->m_pNext = s;
		return true;
	}
	return false;
}

Store * CustomerList::removeStore(int ID) {
	
    Store * cur = m_pHead;
	Store * prev = NULL;

	if (m_pHead == NULL) {
		return NULL;
	}

	while (cur != NULL && cur->getStoreID() != ID) {
		prev = cur;
		cur = cur->m_pNext;
	}

	if (cur == NULL) {
		return NULL;
	}

    else if (prev == NULL){
        m_pHead = m_pHead->m_pNext;
        return cur;
    }
    
    else {
        prev->m_pNext = cur->m_pNext;
        return cur;
    }
    return NULL;
}

Store * CustomerList::getStore(int ID) {
	Store * cur = m_pHead;
	while (cur != NULL) {
		if (cur->getStoreID() == ID) {
			return cur;
		}
		cur = cur->m_pNext;
	}

	return NULL;
}

bool CustomerList::updateStore(int ID, char *name, char *addr, char *city, char *st, char *zip) {
	Store * cur = m_pHead;
	while (cur != NULL) {
		if (cur->getStoreID() == ID) {
			removeStore(ID); //remove it then add the next one so we dont have to reorder the whole list
			Store * s = new Store(ID, name, addr, city, st, zip);
			addStore(s); //add the new one in so we dont have to go through and reorder the whole list again
						 //just use the functions we already wrote.
			return true;
		}
	}
	return false;
}

void CustomerList::printStoresInfo() {
	Store * cur = m_pHead;
	if (m_pHead == NULL) {
		return;
	}

	while (cur != NULL) {
		cur->printStoreInfo();
		cur = cur->m_pNext;
	}

	return;
}



