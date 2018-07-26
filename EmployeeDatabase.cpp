/*******************************************************************
*   File Name: CustomerList.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*
*   This program is entirely my own work
*******************************************************************/


/*******************************************************************
1. Create a new EmployeeRecord. This will also create its' own instance of CustomerList which is not needed. So after creating it call destroyCustomerList on this new instance of EmployeeRecord.

2. Copy all data from the node to be deleted into this new EmployeeRecord. This will also copy the pointer to the CustomerList object. Just briefly you will have two instances of EmployeeRecord both with pointers to the same instance of CustomerList.

3. Search the left sub-tree of the node to be "removed" to find the node with the largest key. This one will be used to overwrite the node to be "removed."

4. Copy all data from the node in the left sub-tree with the largest key into the node to be "removed". This will also copy the pointer to its' CustomerList leaving both nodes with a pointer to the same CustomerList object.

5. Call removeCustomerList() on the EmployeeRecord that you copied FROM. It will set its' m_pCustomerList pointer to null, but will not delete the CustomerList object. This will leave that instance of CustomerList with the node you are overwriting.

6. Remove from the tree the node you just copied FROM and delete it. Since it's pointer to CustomerList is now NULL it will not try to delete its' CustomerList.

7. Return the new EmployeeRecord that is now a duplicate of the one "removed" from the tree.
*******************************************************************/


#include "CustomerList.h"
#include "Store.h"
#include "EmployeeDatabase.h"
#include "EmployeeRecord.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

EmployeeDatabase::EmployeeDatabase() {
	m_pRoot = NULL;
}

//default destructor
EmployeeDatabase::~EmployeeDatabase() {
	DestroyTree(m_pRoot);
    m_pRoot = NULL;
	cout<<"Tree Destroyed"<<endl;
}

//DestroyTree Function
void EmployeeDatabase::DestroyTree(EmployeeRecord *rt) {

	if (rt != NULL)
	{
		DestroyTree(rt->m_pLeft);
		delete rt;
		DestroyTree(rt->m_pRight);
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
	if (!inFile.is_open())
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
	for (int i = 0; i < numEmp; i++)
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
		for (int j = 0; j < numStores; j++)
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
	while (!done)
	{
		inFile.getline(line, 128);

		if (inFile.good())    // If a line was successfully read
		{
			if (strlen(line) == 0)  // Skip any blank lines
				continue;
			else if (line[0] == '#')  // Skip any comment lines
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

	if (m_pRoot == NULL) {
		m_pRoot = e;
	}

	while (temp != NULL) {
		back = temp;
		if (e->getID() < temp->getID())
			temp = temp->m_pLeft;
		else
			temp = temp->m_pRight;
	}

	if (back == NULL) {
		m_pRoot = e;
	}
	else {
		if (e->getID() < back->getID()) {
			back->m_pLeft = e;
		}
		else {
			back->m_pRight = e;
		}
	}

	return true;
}

EmployeeRecord * EmployeeDatabase::getEmployee(int id) {
	EmployeeRecord * temp;
	temp = m_pRoot;
	int key = id;

	while ((temp != NULL) && (temp->getID() != key)) {
		if (key < temp->getID()) {
			temp = temp->m_pLeft;
		}
		else {
			temp = temp->m_pRight;
		}
	}

	if (temp == NULL) {
		return NULL;
	}
	else {
		return temp;
	}
}

void EmployeeDatabase::printEmployeeRecords() {
	printEmployeeRecords(m_pRoot);
}

void EmployeeDatabase::printEmployeeRecords(EmployeeRecord *rt) {

	if (rt != NULL) {
		printEmployeeRecords(rt->m_pLeft);
		rt->printRecord();
		printEmployeeRecords(rt->m_pRight);
	}
}

EmployeeRecord * EmployeeDatabase::removeEmployee(int key) {
	EmployeeRecord * back;
	EmployeeRecord * temp;
	EmployeeRecord * delParent;
	EmployeeRecord * delNode, *parent_replacement, *replacement;

	temp = m_pRoot;
	back = NULL;
	cout << "Remove Employee Function Reached" << endl;
	while ((temp != NULL) && (temp->getID() != key)) {
		back = temp;
		if (key < temp->getID()) {
			temp = temp->m_pLeft;
		}
		else {
			temp = temp->m_pRight;
		}
	}

	if (temp == NULL) {
		return NULL;
	}
	else {
		delNode = temp;
		delParent = back;
	}

	if (delNode->m_pRight == NULL) {
		if (delParent == NULL) {
			m_pRoot = delNode->m_pLeft;
			delNode->m_pLeft = NULL;
			return delNode;
		}
		else {
			if (delParent->m_pLeft == delNode) {
				delParent->m_pLeft = delNode->m_pLeft;
			}
			else {
				delParent->m_pRight = delNode->m_pLeft;
			}
			delNode->m_pLeft = NULL;
			return delNode;
		}
	}
	else {
		if (delNode->m_pLeft == NULL) {
			if (delParent == NULL) {
				m_pRoot = delNode->m_pRight;
				delNode->m_pRight = NULL;
				return delNode;
			}
			else {
				if (delParent->m_pLeft == delNode) {
					delParent->m_pLeft = delNode->m_pRight;
				}
				else {
					delParent->m_pRight = delNode->m_pRight;
				}
				delNode->m_pRight = NULL;
				return delNode;
			}
		}
		else // DELETING NODE WITH 2 CHILDREN
		{
			char fName[32];
			char lName[32];
			temp->getName(fName, lName);
			EmployeeRecord * t = new EmployeeRecord(temp->getID(), fName, lName, temp->getDept(), temp->getSalary());
			parent_replacement = temp;
			replacement = temp->m_pLeft;
			int is_left = 1; /* Replacement is left child of parent */

			while (replacement->m_pRight != NULL)
			{
				parent_replacement = replacement;
				replacement = replacement->m_pRight;
				is_left = 0; // Replacement is right child of parent
			}


			/* Copy data */
			if (temp->getID() == m_pRoot->getID()) {
				replacement->m_pRight = temp->m_pRight;
			}
			else {
				temp->m_pLeft = replacement->m_pLeft;
				temp->m_pRight = replacement->m_pRight;
			}
			temp->setID(replacement->getID());

			if (is_left)
			{
				temp->m_pLeft = replacement->m_pLeft;
				return t;
			}
			else
			{
				parent_replacement->m_pRight = replacement->m_pLeft;
				return t;
			}
		}
		return NULL;
	}
	return NULL;
}

void EmployeeDatabase::postorder(EmployeeRecord * p, int indent) {
	if (p != NULL) {
		if (p->m_pRight) {
			postorder(p->m_pRight, indent + 4);
		}
		if (indent) {
			std::cout << std::setw(indent) << ' ';
		}
		if (p->m_pRight) std::cout << " /\n" << std::setw(indent) << ' ';
		std::cout << p->getID() << "\n ";
		if (p->m_pLeft) {
			std::cout << std::setw(indent) << ' ' << " \\\n";
			postorder(p->m_pLeft, indent + 4);
		}
	}
}

void EmployeeDatabase::printTree() {
	postorder(m_pRoot, 10);
}


