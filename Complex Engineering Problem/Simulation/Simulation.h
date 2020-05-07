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
#include <iostream>
#include "StudentDays.h"
using namespace std;

class Simulation{
private:
    StudentDays studentDays;
    stack<int> laptopStack;
    
public:
    Simulation(StudentDays studentD, stack<int> laptopS);
    void assignLaptopToStudent();
    
};


#endif /* Simulation_h */
