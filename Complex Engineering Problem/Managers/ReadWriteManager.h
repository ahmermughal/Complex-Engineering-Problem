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
#include <cstdlib>
#include "TA.h"
#include "StudentDays.h"
#include "TAsPerDay.h"
using namespace std;

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

};

#endif /* ReadWriteManager_h */
