//
//  Node.cpp
//  Lab 3 The Resistor Network Program
// Author: Jessie Zhou
// Date: Oct 5, 2024

#include <sstream>
#include "Node.h"
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

Node::Node() {
    numRes = 0;
    voltage = 0;
    voltageIsSet = false;
}

bool Node::canAddResistor() {
    if (numRes < MAX_RESISTORS_PER_NODE) {
        return true;
    }
    else {
        return false;
    }
}

void Node::addResistor(int rIndex) {
    resIDArray[numRes] = rIndex;
    numRes += 1;
}

double Node::getVoltage() {
    return voltage;
}

void Node::setVoltage(double voltage_) {
    voltage = voltage_;
    voltageIsSet = true;
}

// sets voltage temporarily during iterations for solve command
void Node::setVoltageInternally(double voltage_) {
    voltage = voltage_;
}

bool Node::isVoltageSet() {
    return voltageIsSet;
}

int Node::getNumRes() {
    return numRes;
}

int* Node::getResIDArray() {
    return resIDArray;
}
