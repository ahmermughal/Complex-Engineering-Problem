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
#include "cmath"
using namespace std;
// This class is used to run the simulation from the given data
class Simulation{
private:
    StudentDays* studentDays;
    TAArray taArray;
    TAArray availableTAs;
    stack<int> laptopStack;
    queue<Student> laptopQueue;
    queue<Student> taQueue;
    int numberOfProg;
    int time;
    int lastTAEndTime;
    int happy;
    int frustrated;
    queue<Student> studentQueue;
    
    void getStudentsInQueue(int num, int progNum);
    void getAvailableTAs(int num);
    void moveArrivedStudentsToLaptopQueue();
    void assignLaptopToStudent();
    void assignTAToStudent();
    void setExpectedLabRunTime(int& expectedRunTime, int num);
    void endTAShift();
    void sendAllStudentsInLaptopQueueHome(int expectedTimeLimit);
    void sendAllStudentsInTAQueueHome(int& expectedTimeLimit);
    void deassignTAFromStudent(int& expectedTimeLimit);
    void printDaySummary(int expectedTimeLimit, int num, string day, int progNum);
    
public:
    queue<string> outputStrings;

    Simulation(StudentDays* studentD, stack<int> laptopS, TAArray tas, int numberOfPrograms);
    void startSimulation();
};


#endif /* Simulation_h */
