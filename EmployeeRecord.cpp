/*******************************************************************
*   File Name: EmployeeRecord.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*
*   This program is entirely my own work
*******************************************************************/

#include "EmployeeRecord.h"
#include <iostream>

using namespace std;


EmployeeRecord::EmployeeRecord() {
	m_iEmployeeID = 0;
	strcpy(m_sLastName, "");
	strcpy(m_sFirstName, "");
	m_iDeptID = 0;
	m_dSalary = 0.0;
	m_pCustomerList = new CustomerList();
	m_pLeft = NULL;
	m_pRight = NULL;
}

EmployeeRecord::EmployeeRecord(int ID, char* fName, char* lName, int deptId, double sal) {
	m_iEmployeeID = ID;
	strcpy(m_sFirstName, fName);
	strcpy(m_sLastName, lName);
	m_iDeptID = deptId;
	m_dSalary = sal;
	m_pCustomerList = new CustomerList();

}

EmployeeRecord::~EmployeeRecord() {
	if (m_pCustomerList != NULL) {
		delete m_pCustomerList;
	}
	else return;
}

int EmployeeRecord::getID() {
	return m_iEmployeeID;
}
void EmployeeRecord::setID(int ID) {
	m_iEmployeeID = ID;
}

void EmployeeRecord::getName(char *fName, char *lName) {
	strcpy(fName, m_sFirstName);
	strcpy(lName, m_sLastName);
}

void EmployeeRecord::setName(char *fName, char *lName) {
	strcpy(m_sFirstName, fName);
	strcpy(m_sLastName, lName);
}


int EmployeeRecord::getDept() {
	return m_iDeptID;
}

void EmployeeRecord::setDept(int d) {
	m_iDeptID = d;
}

double EmployeeRecord::getSalary() {
	return m_dSalary;
}

void EmployeeRecord::setSalary(double sal) {
	m_dSalary = sal;
}

CustomerList * EmployeeRecord::getCustomerList() {
	return m_pCustomerList;
}

void EmployeeRecord::printRecord() {
	Store * cur;
	cout << "================================" << endl;
	cout << "Employee ID is    : " << m_iEmployeeID << endl;
	cout << "First Name is     : " << m_sFirstName << endl;
	cout << "Last Name is      : " << m_sLastName << endl;
	cout << "Deptartment ID is : " << m_iDeptID << endl;
	cout << "Salary is         : " << m_dSalary << endl;
	cout << "Customer List     : { " << endl;
	m_pCustomerList->printStoresInfo();
	cout << "}" << endl;
	cout << "================================" << endl;

}
	void EmployeeRecord::removeCustomerList() { //new
		
		if(m_pCustomerList != NULL) {
			m_pCustomerList = NULL;
		}
	}

	/*	2.2.2 The public function void removeCustomerList() will be added to the EmployeeRecord class. 
	This function sets the pointer to a CustomerList object to NULL. This function is used by the removeEmployee() 
	function in the EmployeeDatabase class. See details of how this function is used in the hints section below. 
	*/
	
	void EmployeeRecord::destroyCustomerList() { //new 
		delete m_pCustomerList;
	}

	/*2.2.3 The public function void destroyCustomerList() will be added to the EmployeeRecord class. 
	This function deletes the CustomerList object and sets the pointer to a CustomerList object to NULL.
	It is used by the removeEmployee() function in the EmployeeDatabase class. See details of how this function 
	is used in the hints section below. NOTE: You will have to modify the destructor of EmployeeRecord to check 
	to see if m_pCustomerList is not NULL before calling delete m_pCustomerList. 
	*/