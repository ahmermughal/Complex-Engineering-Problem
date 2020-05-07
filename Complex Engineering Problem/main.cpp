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
    // insert code here...
    StudentDays studentDays;
    stack<int> laptopStack;
    readWriteManager.readFromFile();
    studentDays = readWriteManager.studentDays;
    laptopStack = readWriteManager.laptopStack;
    Simulation simulation(studentDays, laptopStack);
    
    simulation.assignLaptopToStudent();

//    mondayStudentArr = readWriteManager.mondayStudentArray;
//    
//    for(int i = 0; i < 9; i++){
//        cout<<"Enter Time: "<<mondayStudentArr[i].enterTime<< endl;
//        cout<<"First Name: "<<mondayStudentArr[i].firstName<< endl;
//        cout<<"Last Name: "<<mondayStudentArr[i].lastName<< endl;
//        cout<<"Number Of Questions: "<<mondayStudentArr[i].numQuestions<< endl;
//        cout<<"\t ------------------- \n";
//    }
    
    
    
    return 0;
}
