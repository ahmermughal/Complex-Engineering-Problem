//
//  Simulation.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef Simulation_h
#define Simulation_h

#include <stdio.h>
#include <stack>
#include <queue>
#include <iostream>
#include "StudentDays.h"
#include "Student.h"
#include "TA.h"
#include "TAsPerDay.h"
using namespace std;

class Simulation{
private:
    StudentDays studentDays;
    TAArray taArray;
    stack<int> laptopStack;
    queue<Student> laptopQueue;
    queue<Student> taQueue;
    
public:
    Simulation(StudentDays studentD, stack<int> laptopS, TAArray tas);
    void assignLaptopToStudent();
    void addStudentsToLaptopQueue();
    void addStudentToTAQueue(Student student);
    void assignStudentToTA(Student student, int taIndex);
};


#endif /* Simulation_h */
