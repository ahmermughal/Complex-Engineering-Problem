//
//  main.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include <iostream>
#include "ReadWriteManager.h"
#include "Simulation.h"
ReadWriteManager readWriteManager;


using namespace std;
int main(int argc, const char * argv[]) {

    StudentDays* studentDays;
    stack<int> laptopStack;
    readWriteManager.readFromFile();
    studentDays = readWriteManager.studentDays;
    laptopStack = readWriteManager.laptopStack;
    Simulation simulation(studentDays, laptopStack, readWriteManager.taArray, readWriteManager.numberOfPrograms);
    
    // start the simulation
    simulation.startSimulation();

    readWriteManager.writeToFile(simulation.outputStrings);
    
    return 0;
}
