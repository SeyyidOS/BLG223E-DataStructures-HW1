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

using namespace std;

void addEmployee(const string &dataFilename, int salary, int department) {
    fstream file;
    file.open(dataFilename, ios::in | ios::out | ios::app); // These are indicates that the, we will usee this file for reading, writing and appending.

    string line, lastID = 0;
    while (getline(file, line)); // Go to end of the file
    if (!line.empty()) {
        stringstream ss(line);
        getline(ss, lastID, ';');
    }

    int newID = stoi(lastID) + 1; // Find new ID
    file << newID << ";" << salary << ";" << department << endl; // Write result

    file.close(); // Close file
}

void updateEmployee(const string &dataFilename, int id, int newSalary, int newDepartment) {
    fstream file(dataFilename, ios::in | ios::out); // Open file just reading and wrting
    ofstream tmp("tmp.csv"); // Create tmp file for output. Since we maybe wont found ID.
    bool found = false; // Boolean for the checking ID valid or not

    string line, currentId;
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
        cout << "ERROR: An invalid ID to update" << endl;
        remove("tmp.csv"); // Delete the tmp file
    }
}

void deleteEmployee(const string &dataFilename, int id) {
    fstream file(dataFilename, ios::in | ios::out);  // Open file just reading and wrting
    ofstream tmp("tmp.csv"); // Create tmp file for output. Since we maybe wont found ID.
    bool found = false; // Boolean for the checking ID valid or not

    string line, currentId;
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
        cout << "ERROR: An invalid ID to delete" << endl;
        remove("tmp.csv"); // Delete the tmp file
    }
}

void processOperations(const string &dataFilename, const string &operationsFilename) {
    // These codes same as the part 1
    ifstream file(operationsFilename);

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string operation, id, salary, department;
        getline(ss, operation, ';');

        if (operation == "ADD") {
            getline(ss, salary, ';');
            getline(ss, department, ';');

            addEmployee(dataFilename, stoi(salary), stoi(department));
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

int main() {

    processOperations("employees.csv", "operations.txt");

    return 0;
}
