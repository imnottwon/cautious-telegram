/*******************************************************************
*   File Name: EmployeeRecord.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*   
*   This program is entirely my own work
*******************************************************************/
#pragma once
#include "CustomerList.h"


class EmployeeRecord 
{
private:
	int m_iEmployeeID;
	char m_sLastName[32];
	char m_sFirstName[32];
	int m_iDeptID;
	double m_dSalary;
	CustomerList * m_pCustomerList; //new

public:
	EmployeeRecord();
	EmployeeRecord(int ID, char* fName, char* lName, int deptId, double sal);
	~EmployeeRecord();
	int getID();
	void setID(int ID);
	void getName(char *fname, char *lname);
	void setName(char *fname, char *lname);
	void removeCustomerList();
	int getDept();
	void setDept(int d);
	double getSalary();
	void setSalary(double sal);
	void printRecord();
	void destroyCustomerList();
	EmployeeRecord *m_pLeft;  //new
	EmployeeRecord *m_pRight; //new 

	CustomerList *getCustomerList();
	
};