/*******************************************************************
*   File Name: Main.cpp
*	Name: Antoine Lynch
*   Programming Assignment 3
*
*   This program is entirely my own work
*******************************************************************/
#include "EmployeeDatabase.h"
using namespace std;

//forward declarations
char * getRandomAddress();
char * getRandomStoreName();
char * getRandomCity();
int    getRandomId();
char * getRandomState();
char * getRandomZip();
Store * generateStore();
void testGenerateStore();

int main(int argc, char * argv[])
{

	//Testing the buildDatabase, addEmployee,
	//and printEmployeeRecords functions

	EmployeeDatabase *db = new EmployeeDatabase();
	db->buildDatabase("Prog3Data.txt");
	db->printEmployeeRecords();

	//Testing the getEmployee function

	EmployeeRecord *e;
	e = db->getEmployee(5678);
	if ((e != NULL) && (e->getID() == 5678))
		cout << "test for getEmployee successful" << endl;

	EmployeeRecord *eT;
	eT = db->getEmployee(8765);
	if ((eT != NULL) && (eT->getID() == 8765))
		cout << "test for getEmployee successful" << endl;


	//Testing removeEmployee
	EmployeeRecord *e2;
	

	e = db->removeEmployee(9999);
	if (e == NULL)
		cout << "1. Test for nonexistent node success" << endl;
	system ("pause");
	e = db->removeEmployee(8765);
	if (e->getID() == 8765)
		cout << "2. Test for leaf node removal successful" << endl;
	system ("pause");
	e = db->removeEmployee(7890);
	if (e->getID() == 7890)
		cout << "3. Test for non root node with 2 children successful" << endl;
	system ("pause");
	db->removeEmployee(4567);
	//e = db->removeEmployee(1234);
	//if (e->getID() == 1234)
	//	cout << "4. Test for non root right child successful" << endl;
	//system ("pause");
	e = db->removeEmployee(3456);
	if (e->getID() == 3456)
		cout << "5. Test for non root left child successful" << endl;
	system ("pause");
	db->printEmployeeRecords();		
	e = db->removeEmployee(5678);
	if (e->getID() == 5678)
		cout << "6. Test for root node with 2 children successful" << endl;
	system ("pause");
	
	e = db->removeEmployee(2345);
	if (e->getID() == 2345)
		cout << "7. Test for root node with right child successful" << endl;
	system ("pause");
    
	//db->removeEmployee(7654);
	//db->removeEmployee(9876);
	//db->addEmployee(e2);

	e = db->removeEmployee(6789);
	if (e->getID() == 6789)
		cout << "8. Test for root node with left child successful" << endl;
	system ("pause");
	e = db->removeEmployee(2345);
	if (e->getID() == 2345)
		cout << "9. Test for root, leaf, last node in tree successful" << endl;
	system ("pause");

	//Testing the destructor and destroyTree functions

	EmployeeDatabase *db2 = new EmployeeDatabase();
	db2->buildDatabase("Prog3Data.txt");
	db2->printEmployeeRecords();
	delete db2;
	delete e;
	delete e2;
		
	return 0;


}