/*
@Author
StudentName : Seyyid Osman Sevgili
StudentID : 504221565
Date : 26.10.2023
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

void addEmployee(const string &dataFilename, int &largestId, int salary, int department) {
    fstream file;
    file.open(dataFilename, ios::in | ios::out | ios::app); // These are indicates that the, we will usee this file for reading, writing and appending.

    string line;
    while (getline(file, line)); // Go to end of the file

    largestId++;
    file << largestId << ";" << salary << ";" << department << endl; // Write result

    file.close(); // Close file
}

void updateEmployee(const string &dataFilename, int id, int newSalary, int newDepartment) {
    fstream file(dataFilename, ios::in | ios::out); // Open file just reading and wrting
    ofstream tmp("tmp.csv"); // Create tmp file for output. Since we maybe wont found ID.
    bool found = false; // Boolean for the checking ID valid or not

    string line, currentId;
    getline(file, line);
    tmp << line << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, currentId, ';');
        if (stoi(currentId) == id) {
            tmp << id << ";" << newSalary << ";" << newDepartment << endl; // Write updated employee
            found = true;  // Set flag
        } else {
            tmp << line << endl; // Write original employee
        }
    }

    file.close(); // Close the file
    tmp.close(); // Close the tmp file

    // If id is valid, remove the original file. Rename the tmp file. Else throw an exception.
    if (found) {
        remove(dataFilename.c_str());
        rename("tmp.csv", dataFilename.c_str());
    } else {
        cerr << "ERROR: An invalid ID to update" << endl;
        remove("tmp.csv"); // Delete the tmp file
    }
}

void deleteEmployee(const string &dataFilename, int id) {
    fstream file(dataFilename, ios::in | ios::out);  // Open file just reading and wrting
    ofstream tmp("tmp.csv"); // Create tmp file for output. Since we maybe wont found ID.
    bool found = false; // Boolean for the checking ID valid or not

    string line, currentId;
    getline(file, line);
    tmp << line << endl;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, currentId, ';');
        if (stoi(currentId) == id) {
            found = true;  // Set found flag
        } else {
            tmp << line << endl; // Write original data
        }
    }

    file.close(); // Close the file
    tmp.close(); // Close the tmp file

    // If id is valid, remove the original file. Rename the tmp file. Else throw an exception.
    if (found) {
        remove(dataFilename.c_str());
        rename("tmp.csv", dataFilename.c_str());
    } else {
        cerr << "ERROR: An invalid ID to delete" << endl;
        remove("tmp.csv"); // Delete the tmp file
    }
}

void processOperations(const string &dataFilename, const string &operationsFilename, int &largestId) {
    // These codes same as the part 1
    ifstream file(operationsFilename);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string operation, id, salary, department;
        getline(ss, operation, ';');

        // cout << "OPERATION: " << operation << endl;

        if (operation == "ADD") {
            getline(ss, salary, ';');
            getline(ss, department, ';');

            addEmployee(dataFilename, largestId, stoi(salary), stoi(department));
        } else if (operation == "UPDATE") {
            getline(ss, id, ';');
            getline(ss, salary, ';');
            getline(ss, department, ';');

            updateEmployee(dataFilename, stoi(id), stoi(salary), stoi(department));
        } else if (operation == "DELETE") {
            getline(ss, id, ';');

            deleteEmployee(dataFilename, stoi(id));
        } 
    }

    file.close();
}

int setLargestId(const string &dataFilename){
    ifstream file(dataFilename);
    int numEmployees = 0;
    string line;

    getline(file, line);
    while (getline(file, line)) {
        numEmployees++;
    }

    file.close();
    
    return numEmployees;
}

int main(int argc, char** argv) {
    // clock_t start = clock (); 
    int largestId = setLargestId(argv[1]);

    processOperations(argv[1], argv[2], largestId);

    // clock_t end = clock (); 
    // double exec_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    // cout << "Execution time in sec:  " << exec_time << endl;
    return 0;
}
