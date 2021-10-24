#include <Python.h>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

// Call CalculateAndPrintItemTotals from Python
//  with the filename parameter.
void pyCalculateAndPrintItemTotals(const char* filename)
{
	PyObject* pName, * pModule, * pDict, * pFunc, * pValue;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, "CalculateAndPrintItemTotals");
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", filename);
		PyErr_Print();
		PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();
}

// Call CalculateSingleItemFrequeny from Python with a given filename
//  and itemname parameters.
int pyCalculateSingleItemFrequency(const char* filename, const char* itemname)
{
	PyObject* pName, * pModule, * pDict, * pFunc, * pValue, * pResult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, "CalculateSingleItemFrequency");
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(zz)", filename, itemname);
		PyErr_Print();
		pResult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	return _PyLong_AsInt(pResult);
}

// Call CalculateAndSaveItemTotals from Python
//  with the filename and outfilename parameters.
void pyCalculateAndSaveItemTotals(const char* filename, const char* outfilename)
{
	PyObject* pName, * pModule, * pDict, * pFunc, * pValue;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, "CalculateAndSaveItemTotals");
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(zz)", filename, outfilename);
		PyErr_Print();
		PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();
}

// Print a number with explanation.
void printNumber(int number)
{
	cout << "The number is " << number << endl;
}

// Program entry point.
void main()
{
	// display menu until user selects exit
	while (true) {
		cout << "1: Calculate Item Totals" << endl;
		cout << "2: Frequency of Specific Item" << endl;
		cout << "3: Histogram" << endl;
		cout << "4: Exit" << endl;

		// get selection from user
		int selection;
		cin >> selection;

		if (selection == 1) {
			pyCalculateAndPrintItemTotals("input.dat");
		}
		else if (selection == 2) {
			cout << "What item do you want to search for?" << endl;
			
			string selection;
			cin >> selection;

			printNumber(pyCalculateSingleItemFrequency("input.dat", selection.c_str()));
		}
		else if (selection == 3) {
			string frequencydat = "frequency.dat";

			// save item frequency to file
			pyCalculateAndSaveItemTotals("input.dat", frequencydat.c_str());

			// read item frequency and output as histogram
			fstream datfile(frequencydat, ios::in);
			if (datfile.is_open()) {
				string line;
				while (getline(datfile, line)) {
					//locate space in frequency.dat line to get item name and frequency
					size_t space = line.find(' ');
					string itemname = line.substr(0, space);
					int frequency = stoi(line.substr(space + 1));

					// print as a histogram by printing '*'
					cout << itemname << " ";
					for (int i = 0; i < frequency; ++i) {
						cout << "*";
					}
					cout << endl;
				}
				datfile.close();
			}
		}
		else if (selection == 4) {
			// exit program
			break;
		}
		else {
			cout << "Error: Invalid selection" << endl;
		}
	}
}
