//
//  Simulation.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "Simulation.h"

Simulation::Simulation(StudentDays studentD, stack<int> laptopS, TAArray tas){
    studentDays = studentD;
    laptopStack = laptopS;
    taArray = tas;
}

void Simulation::assignStudentToTA(Student student, int taIndex){
    
    taArray.ta[taIndex].studentWithTA = student;
    cout<<taArray.ta[taIndex].studentWithTA.firstName<<" is Assigned To "<< taArray.ta[taIndex].name<<endl;
    
}

void Simulation::addStudentToTAQueue(Student student){
    
    taQueue.push(student);
    
    if(taQueue.size() > 0){
        for(int i = 0; i < taArray.arraySize; i++){
            if(!taArray.ta[i].isStudentWithTA()){
                assignStudentToTA(taQueue.front(), i);
                taQueue.pop();
                break;
            }else{
                cout<<"Student With TA "<<taArray.ta[i].name<<endl;
            }
        }
    }
    cout<<"TA Queue Size: "<<taQueue.size()<<endl<<endl;
}

void Simulation::assignLaptopToStudent(){
    int laptopQueueSize = laptopQueue.size();
    for(int i = 0; i< laptopQueueSize; i++){
        //get student in front of queue
        Student student = laptopQueue.front();
        
        // assign laptop to student from stack
        student.laptopSerialNum = laptopStack.top();
        
        // it takes one min for student to get laptop assigned
        student.timePassedInLab += 1;
        
        
        
        //remove student from queue
        laptopQueue.pop();
        
        // pop assigned laptop from stack
        laptopStack.pop();
        
        addStudentToTAQueue(student);
        
    }
    
    cout<<"Laptop Queue Size is: "<<laptopQueue.size()<<endl;
}

void Simulation::addStudentsToLaptopQueue(){
    StudentsPerDay mondayStudents = studentDays.mondayStudents;
    for(int i = 0; i< mondayStudents.size; i++){
        Student student = mondayStudents.students[i];
        laptopQueue.push(student);
    }
    //cout<<"Laptop Queue Size: "<<laptopQueue.size()<<endl;
    assignLaptopToStudent();
}



