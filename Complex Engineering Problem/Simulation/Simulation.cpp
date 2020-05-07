//
//  Simulation.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "Simulation.h"

Simulation::Simulation(StudentDays studentD, stack<int> laptopS){
    studentDays = studentD;
    laptopStack = laptopS;
}

void Simulation::assignLaptopToStudent(){
    
    StudentsPerDay mondayStudents = studentDays.mondayStudents;
    
    for(int i = 0; i< mondayStudents.size; i++){
        
        mondayStudents.students[i].laptopSerialNum = laptopStack.top();
        cout<<"Student Serial Number: "<<mondayStudents.students[i].laptopSerialNum<<endl;
        laptopStack.pop();
    }
    
    
    
}

