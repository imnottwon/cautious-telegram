/*******************************************************************
*   File Name: EmployeeRecord.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3 
*   
*   This program is entirely my own work
*******************************************************************/

//new file

#pragma once
#include "CustomerList.h"
#include "EmployeeRecord.h"

class EmployeeDatabase 
{
private:
	EmployeeRecord *m_pRoot;
	ifstream inFile; 
	void DestroyTree(EmployeeRecord *rt);
	void printEmployeeRecords(EmployeeRecord *rt);

public:
	EmployeeDatabase();
	~EmployeeDatabase();
	bool addEmployee(EmployeeRecord *e);
	EmployeeRecord *getEmployee(int ID);
	EmployeeRecord *removeEmployee(int ID);
	void printEmployeeRecords();
	bool buildDatabase(char *dataFile);  //included from instructor
	bool getNextLine(char *line, int LineLen); //included from instructor
};

/*******************************************************************
	// If the call to getNextLine() is returning string data such as an employee's 
	// first or last name then you can use strcpy() to copy directly from inStr to
	// another character array. Assume
	// char name[32]; has been declared.
	strcpy(name, inStr);

	// If the call to getNextLine() is returning an integer as a string, for example "1234"
	// you can convert it to an integer with atoi() which means "ASCII to Integer".  Assume
	// int ID; has been declared. 
	ID = atoi(inStr); 

	// If the call to getNextLine() is returning a double as a string, for example "65536.00"
	// you can convert it to a double with atof() which means "ASCII to Float".  Assume
	// double sal; has been declared. 
	sal = atof(inStr); 

	// In the case of adding data to a Store or EmployeeRecord call the appropriate set function
	// for strings, e.g. st->setStoreName(inStr) and for values st->setStoreID(atoi(inStr); 
	*******************************************************************/
