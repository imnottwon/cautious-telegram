
/*******************************************************************
*   File Name: CustomerList.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*
*   This program is entirely my own work
*******************************************************************/
#include "CustomerList.h"
#include "Store.h"
#include "EmployeeDatabase.h"
#include "EmployeeRecord.h"

#include <iostream>
#include <fstream>

using namespace std;

EmployeeDatabase::EmployeeDatabase() {

}

//default destructor
EmployeeDatabase::~EmployeeDatabase() {
	DestroyTree(m_pRoot);
}

//DestroyTree Function
void EmployeeDatabase::DestroyTree(EmployeeRecord *rt) {
	
	if (rt != NULL)
	{
		DestroyTree(rt->m_pLeft);
		DestroyTree(rt->m_pRight);
		free (rt);
	}
}


bool EmployeeDatabase::buildDatabase(char *dataFile)
{
	bool OK = true;
	int numEmp, id, dept, numStores, sID;
	double sal;
	EmployeeRecord *empRec;
	CustomerList *theList;
	Store *theStore;
	char inStr[128];
	char fName[32];
	char lName[32];
	char sName[64];
	char sAddr[64];
	char sSt[32];
	char sCity[32];
	char sZip[12];
	

	inFile.open(dataFile, ifstream::in); 
    if(!inFile.is_open())
    {
        // inFile.is_open() returns false if the file could not be found or
        //    if for some other reason the open failed.
        cout << "Unable to open file" << dataFile << "\nProgram terminating...\n";
		cout << "Press Enter to continue...";
		getc(stdin);
        return false;
    }

	// Get number of employees
	getNextLine(inStr, 128);
	numEmp = atoi(inStr);
	for(int i=0; i<numEmp; i++)
	{
		// Instantiate an EmployeeRecord
		empRec = new EmployeeRecord();
		// Read and set the ID
		getNextLine(inStr, 127);
		id = atoi(inStr);
		empRec->setID(id);
		// Read and set the name
		getNextLine(fName, 31);
		getNextLine(lName, 31);
		empRec->setName(fName, lName);
		// Read and set the Department ID
		getNextLine(inStr, 127);
		dept = atoi(inStr);
		empRec->setDept(dept);
		// Read and set the Salary
		getNextLine(inStr, 127);
		sal = atof(inStr);
		empRec->setSalary(sal);
		// Get the customer list
		theList = empRec->getCustomerList();
		// Get the number of stores
		getNextLine(inStr, 127);
		numStores = atoi(inStr);
		for(int j=0; j<numStores; j++)
		{
			// Read the store ID
			getNextLine(inStr, 127);
			sID = atoi(inStr);
			// Read the store name
			getNextLine(sName, 63);
			// Read the store address
			getNextLine(sAddr, 63);
			// Read the store city
			getNextLine(sCity, 31);
			// Read the store state
			getNextLine(sSt, 31);
			// Read the store zip
			getNextLine(sZip, 11);
			// Create a new Store object
			theStore = new Store(sID, sName, sAddr, sCity, sSt, sZip);
			theList->addStore(theStore);
		}
		cout.flush();
		addEmployee(empRec);
	}
	inFile.close();
	return true;	// Successfully built the database
}

bool EmployeeDatabase::getNextLine(char *line, int lineLen)
{
    int    done = false;
    while(!done)
    {
        inFile.getline(line, 128);
        
        if(inFile.good())    // If a line was successfully read
        {
            if(strlen(line) == 0)  // Skip any blank lines
                continue;
            else if(line[0] == '#')  // Skip any comment lines
                continue;
            else return true;    // Got a valid data line so return with this line
        }
        else
        {
            strcpy(line, "");
            return false;
        }
    } // end while
    return false;
}

bool EmployeeDatabase::addEmployee(EmployeeRecord *e) {
	EmployeeRecord *temp;
	EmployeeRecord *back;
	temp = m_pRoot;  //fix
	back = NULL;

	while (temp != NULL) {
		back = temp;
		if (e->getID() < back->getID())
			temp = temp->m_pLeft;
		else
			temp = temp->m_pRight;
	}

	if (back == NULL) {
		m_pRoot = e;
	} else {
		if (e->getID() < back->getID()) {
			back->m_pLeft = e;
		} else {
			back->m_pRight = e;
		}
	}

	return true;
}