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
    TAArray availableTAs;
    stack<int> laptopStack;
    queue<Student> laptopQueue;
    queue<Student> taQueue;
    int time;
    int lastTAEndTime;
    int happy;
    int frustrated;
    queue<Student> studentQueue;
    void getStudentsInQueue(int num);
    void getAvailableTAs(int num);
    void moveArrivedStudentsToLaptopQueue();
    void assignLaptopToStudent();
    void assignTAToStudent();

    void setExpectedLabRunTime(int& expectedRunTime, int num);
    void endTAShift();
    void sendAllStudentsInLaptopQueueHome(int expectedTimeLimit);
    void sendAllStudentsInTAQueueHome(int& expectedTimeLimit);
    void deassignTAFromStudent(int& expectedTimeLimit);
    void printDaySummary(int expectedTimeLimit, int num, string day);
    
public:
    Simulation(StudentDays studentD, stack<int> laptopS, TAArray tas);
    void startSimulation();
   

};


#endif /* Simulation_h */
