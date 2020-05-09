//
//  Student.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef Student_h
#define Student_h
#include <stdio.h>
#include <string>

using namespace std;
typedef struct DataStructuresStudent {
    string firstName;
    string lastName;
    int enterTime;
    int numQuestions;
    int numAnswered;
    int laptopSerialNum;
    int timePassedInLab;
    bool withTA = false;
} Student;

#endif /* Student_h */
