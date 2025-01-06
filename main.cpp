//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors = nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors
int nodeCount = 0;  // count the number of nodes

string errorArray[10] = {
    "invalid command",                                  // 0
    "invalid argument",                                 // 1
    "negative resistance",                              // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);


void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);

bool checkResistorExists(int resistorCount, Resistor** resistorArray, const string& resistorNameID);

int main() {
    string line;
    cout << ">>> ";
    cout.flush();
    
    while (getline(cin, line)) {
        if (line.empty() || line == "exit") {
            break;
        }
        
        stringstream ss(line);
        string command;
        ss >> command;  
    
        if (command == "maxVal") {
            handleMaxVal(ss);  
        } 
        else if (command == "insertR") {
            handleInsertR(ss);
        } 
        else if (command == "modifyR") {
            handleModifyR(ss);
        } 
        else if (command == "printR") {
            handlePrintR(ss);
        } 
        else if (command == "deleteR") {
            handleDeleteR(ss);
        } 
        else if (command == "setV") {
            handleSetV(ss);
        } 
        else {
            cout << "Error: " << errorArray[0] << endl;
        }

        cout << ">>> ";
        cout.flush();
    }

    // clean up dynamically allocated memory
    if (nodes != nullptr) {
        delete[] nodes;
        nodes = nullptr;
    }

    if (resistors != nullptr) {
        for (int i = 0; i < resistorsCount; ++i) {
            if (resistors[i] != nullptr) {
                delete resistors[i];
                resistors[i] = nullptr;
            }
        }
        delete[] resistors;
        resistors = nullptr;
    }

    return 0;
}

bool checkResistorExists(int resistorCount, Resistor** resistorArray, const string& resistorNameID) {
    int currentResistorIndex = 0;

    // check for nullptr
    if (resistorArray == nullptr) {
        // cout << "Error: nothing inside asjdnfiwefnwfe" << endl;
        return false; 
    }

    while (currentResistorIndex < resistorCount) {
        if (resistors[currentResistorIndex] != nullptr && resistorArray[currentResistorIndex]->getName() == resistorNameID) {
            return true;  
        }
        currentResistorIndex++;
    }

    return false;  
}


// TODO: Implement functions here
bool getInteger(stringstream& ss, int& x) {
    if (ss.eof()) {
        cout << "Error: " << errorArray[6] << endl;
        return false;
    }

    int tempInt;
    ss >> tempInt;

    if (ss.fail()) {
        if (ss.eof()) {
            cout << "Error: " << errorArray[6] << endl;
            return false;
        } else {
            cout << "Error: " << errorArray[1] << endl;
            ss.clear();
            return false;
        }
    } else {
        x = tempInt;
        return true;
    }
}

bool getString(stringstream& ss, string& s) {
    if (ss.eof()) {
        cout << "Error: " << errorArray[6] << endl;
        return false;
    }

    string tempString;
    ss >> tempString;

    if (ss.fail()) {
        if (ss.eof()) {
            cout << "Error: " << errorArray[6] << endl;
            return false;
        } else {
            cout << "Error: " << errorArray[1] << endl;
            ss.clear();
            return false;
        }
    } else {
        s = tempString;
        return true;
    }
}

bool getDouble(stringstream& ss, double& s) {
    if (ss.eof()) {
        cout << "Error: " << errorArray[6] << endl;
        return false;
    }

    double tempDouble;
    ss >> tempDouble;

    if (ss.fail()) {
        if (ss.eof()) {
            cout << "Error: " << errorArray[6] << endl;
            return false;
        } else {
            cout << "Error: " << errorArray[1] << endl;
            ss.clear();
            return false;
        }
    } else {
        s = tempDouble;
        return true;
    }
}

void handleMaxVal(stringstream& ss) { //GOOD
    int maxNode = 0;
    int maxRes = 0;

    if (!getInteger(ss, maxNode)) {
        return;
    }
    if (!getInteger(ss, maxRes)) {
        return;
    }

    // reset memory if handleMaxVal is called more than once
    if (nodes != nullptr) {
        delete[] nodes;
        nodes = nullptr;
    }

    if (resistors != nullptr) {
        for (int i = 0; i < resistorsCount; ++i) {
            delete resistors[i];
        }
        delete[] resistors;
        resistors = nullptr;
    }

    maxNodeNumber = maxNode;      
    maxResistors = maxRes;
    nodes = new Node[maxNodeNumber];
    resistors = new Resistor*[maxResistors];
    resistorsCount = 0;
    nodeCount = 0;

    cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;
}

void handleInsertR(stringstream& ss) { // GOOD
    string nameID = "";
    double resistance = 0;
    int node1 = 0;
    int node2 = 0;

    if (!getString(ss, nameID)) {
        return;
    }

    // check if resistor name is 'all'
    if (nameID == "all") {
        cout << "Error: " << errorArray[4] << endl;
        return;
    }

    // check if resistor name already exists
    if (checkResistorExists(resistorsCount, resistors, nameID)) {
        cout << "Error: resistor " << nameID << " already exists" << endl;
        return;
    }

    if (!getDouble(ss, resistance)) {
        return;
    }

    // check for negative resistance
    if (resistance < 0) {
        cout << "Error: " << errorArray[2] << endl;
        return;
    }

    if (!getInteger(ss, node1)) {
        return;
    }
    if (!getInteger(ss, node2)) {
        return;
    }


    // check if both terminals connect to the same node
    if (node1 == node2) {
        cout << "Error: " << errorArray[5] << endl;
        return;
    }

    // Add or update nodes
    bool node1Exists = false;
    bool node2Exists = false;

    for (int i = 0; i < nodeCount; i++) {
        if (nodes[i].canAddResistor()) {
            node1Exists = true;
        } 
        if (nodes[i].canAddResistor()) {
            node2Exists = true;
        }
    }

    if (!node1Exists) {
        if (nodeCount >= maxNodeNumber) {
            cout << "Error: max number of nodes reached" << endl;
            return;
        }
        // nodes[nodeCount++] = Node(node1);
    }

    if (!node2Exists) {
        if (nodeCount >= maxNodeNumber) {
            cout << "Error: max number of nodes reached" << endl;
            return;
        }
        // nodes[nodeCount++] = Node(node2);
    }

    //insert resistor
    if (resistorsCount < maxResistors) {
        int endpoints[2] = {node1, node2};
        resistors[resistorsCount] = new Resistor(nameID, resistance, endpoints);
        resistorsCount++;
        nodeCount = nodeCount + 2;

        cout << "Inserted: resistor " << nameID << " " << fixed << setprecision(2) << resistance << " Ohms " << node1 << " -> " << node2 << endl;
    } 
    else {
        cout << "Error: max number of resistors reached" << endl;
    }
}


void handleModifyR(stringstream& ss) { //fixed
    string nameID = "";
    double resistance = 0;
    double oldResistance = 0;

    if (!getString(ss, nameID)) {
        return;
    }

    //check if resistor name is 'all'
    if (nameID == "all") {
        cout << "Error: " << errorArray[4] << endl;
        return;
    }

    //check if resistor name exists
    if (!checkResistorExists(resistorsCount, resistors, nameID)) {
        cout << "Error: resistor " << nameID << " not found" << endl;
        return;
    }
    
    if (!getDouble(ss, resistance)) {
        return;
    }

    //check for negative resistance of resistor
    if (resistance < 0) {
        cout << "Error: " << errorArray[2] << endl;
        return;
    }

    for (int i = 0; i < resistorsCount; i++) {
        if (resistors[i]->getName() == nameID) {
            oldResistance = resistors[i]->getResistance();
            resistors[i]->setResistance(resistance);
            cout << "Modified: resistor " << nameID << " from " << fixed << setprecision(2) << oldResistance << "Ohms" << " to " << fixed << setprecision(2) << resistance << " Ohms" << endl;
            return;
        }
    }

    //if resistor name DOES NOT exist
    cout << "Error: resistor " << nameID << " not found" << endl;


}


void handlePrintR(stringstream& ss) {
    string nameID;
    bool Rfound = false;

    if (!getString(ss, nameID)) {
        return;
    }

    if (nameID.empty()) {
        return;
    }

    if (nameID == "all") {
        cout << "Error: resistor " << nameID << " not found" << endl;
        return;
    }

    Rfound = false;
    for (int i = 0; i < resistorsCount; i++) {
        if (resistors[i] != nullptr && resistors[i]->getName() == nameID) {
            resistors[i]->print();
            Rfound = true;
            break;
        }
    }

    if (!Rfound) {
        cout << "Error: resistor " << nameID << " not found" << endl;
    }
}

void handleDeleteR(stringstream& ss) {
    string nameID;

    if (!getString(ss, nameID)) {
        return;
    }

    if (nameID == "all") {
        for (int i = 0; i < resistorsCount; i++) {
            if (resistors[i] != nullptr) {
                delete resistors[i];
                resistors[i] = nullptr;
            }
        }
        resistorsCount = 0;

        delete []nodes;
        nodes = nullptr;

        nodeCount = 0;

        cout << "Deleted: all resistors" << endl;
    } else {
        cout << "Error: " << errorArray[1] << endl;
    }
}

void handleSetV(stringstream& ss) { 
    int nodeID;
    double voltage;

    if (!getInteger(ss, nodeID)) {
        return;
    }

    //checking if node value is out of permitted range
    if (nodeID < 0 || nodeID > maxNodeNumber) {
        cout << errorArray[3] << endl;
        return;
    }

    if (!getDouble(ss, voltage)) {
        return;
    }

    if (nodes == nullptr) {
        // cout << "Error: no nodes" << endl;
        return;
    }

    nodes[nodeID - 1].setVoltage(voltage);
    cout << "Set: node " << nodeID << " to " << fixed << setprecision(2) << voltage << " Volts" << endl;
}