//
//  ReadWriteManager.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef ReadWriteManager_h
#define ReadWriteManager_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <cstdlib>
#include "TA.h"
#include "StudentDays.h"
#include "TAsPerDay.h"
using namespace std;
// This class is used to manage the IO of the simulation
// Reading from the file to get the data
// Writing back to the file
class ReadWriteManager{
private:
    stack<int> readLaptopStack(ifstream& inFile);
    void readTAArray(ifstream& inFile);
    Student* readStudentArray(ifstream& inFile, int& size);
    
public:
    ReadWriteManager();
    StudentDays* studentDays;
    stack<int> laptopStack;
    TAArray taArray;
    void readFromFile();
    int numberOfPrograms;
    void writeToFile(queue<string> outputStrings);
};

#endif /* ReadWriteManager_h */
