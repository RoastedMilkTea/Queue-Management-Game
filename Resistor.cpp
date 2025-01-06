//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author: Jessie
// Date:

#include "Resistor.h"

#include <iomanip>

void Resistor::print() {
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

string Resistor::getName() {
  return name;
}

double Resistor::getResistance() {
  return resistance;
}   

void Resistor::setResistance(double resistance_) {
    resistance = resistance_;
}

int Resistor::getOtherEndpoint(int nodeIndex) {
    if ((endpointNodeIDs[0] != nodeIndex) && (endpointNodeIDs[1] != nodeIndex)) {
        return 1; 
    } else if (endpointNodeIDs[0] == nodeIndex) {
        return endpointNodeIDs[1];
    } else if (endpointNodeIDs[1] == nodeIndex) {
        return endpointNodeIDs[0];
    }
    return 1;
}

Resistor::Resistor(string name_, double resistance_, int endpoints[2]) {
    name = name_;
    resistance = resistance_;
    
    endpointNodeIDs[0] = endpoints[0];
    endpointNodeIDs[1] = endpoints[1];
}