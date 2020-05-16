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
    availableTAs.arraySize = 0;
    availableTAs.ta = new TA[tas.arraySize];
    time = 0;
}

//void Simulation::assignStudentToTA(Student student, int taIndex){
//    taArray.ta[taIndex].studentWithTA = student;
//    cout<<taArray.ta[taIndex].studentWithTA.firstName<<" is Assigned To "<< taArray.ta[taIndex].name<<endl;
//    deassignStudentFromTA(student, taIndex);
//    addStudentToTAQueue(student);
//}
//
//void Simulation::deassignStudentFromTA(Student student, int taIndex){
//    taArray.ta[taIndex].studentWithTA = Student();
//}
//
//
//void Simulation::deassignLaptopFromStudent(Student student){
//    cout<<student.firstName<<" "<<student.lastName<<" gave back laptop and went"<<endl<<endl;
//}
//
//void Simulation::addStudentToTAQueue(Student student){
//    if(student.numQuestions > 0){
//        student.numQuestions -= 1;
//        taQueue.push(student);
//    }else{
//        deassignLaptopFromStudent(student);
//    }
//}
//
//void Simulation::assigningStudentToTAQueue(Student student){
//    cout<<student.firstName<<" "<<student.lastName<<" has "<<student.numQuestions<<" questions."<<endl;
//
//    addStudentToTAQueue(student);
//
//    if(taQueue.size() > 0){
//        while(taQueue.size() != 0){
//            for(int i = 0; i < taArray.arraySize; i++){
//                if(!taArray.ta[i].isStudentWithTA()){
//                    assignStudentToTA(taQueue.front(), i);
//                    taQueue.pop();
//                    break;
//                }else{
//                    cout<<taArray.ta[i].studentWithTA.firstName<<" "<<taArray.ta[i].studentWithTA.lastName<<" is with TA "<<taArray.ta[i].name<<endl;
//                }
//            }
//        }
//    }
//    //cout<<"TA Queue Size: "<<taQueue.size()<<endl<<endl;
//}
//
//void Simulation::assignLaptopToStudent(){
//    int laptopQueueSize = laptopQueue.size();
//    for(int i = 0; i< laptopQueueSize; i++){
//        //get student in front of queue
//        Student student = laptopQueue.front();
//
//        // assign laptop to student from stack
//        student.laptopSerialNum = laptopStack.top();
//
//        // it takes one min for student to get laptop assigned
//        student.timePassedInLab += 1;
//
//        //remove student from queue
//        laptopQueue.pop();
//
//        // pop assigned laptop from stack
//        laptopStack.pop();
//
//        assigningStudentToTAQueue(student);
//    }
//    //cout<<"Laptop Queue Size is: "<<laptopQueue.size()<<endl;
//}
//
//void Simulation::addStudentsToLaptopQueue(){
//    StudentsPerDay mondayStudents = studentDays.mondayStudents;
//    for(int i = 0; i< mondayStudents.size; i++){
//        Student student = mondayStudents.students[i];
//        laptopQueue.push(student);
//    }
//    //cout<<"Laptop Queue Size: "<<laptopQueue.size()<<endl;
//    assignLaptopToStudent();
//}

string formatTime(int time)
{
    
    int hour = 0, min = 0;
    string formattedTime = "", h, m;
    
    if (time != 0){
        if (time < 60)
        {
            hour    = 12;
            min        = time;
        }else{
            while (time > 60)
            {
                time = time - 60;
                if (hour == 12)
                {
                    hour = 0;
                }
                hour++;
            }
            min = time;
        }
    }else{
        hour    = 12;
        min        = 00;
    }
    
    if (hour < 10){
        h = "0" + to_string(hour);
    }else{
        h = to_string(hour);
    }
    
    if (min < 10){
        m = "0" + to_string(min);
    }else{
        m = to_string(min);
    }
    
    if (min == 0){
        formattedTime= h+ ":00" + " PM:";
    }else{
        formattedTime= h + ":" + m + " PM:";
    }
    return formattedTime;
}

void Simulation::getAvailableTAs(){
    // getting TAs according to their timing
    // and adding to list of avaiable TA during this day
    if(availableTAs.arraySize != taArray.arraySize){
        for(int i = 0; i < taArray.arraySize; i++){
            if(taArray.ta[i].endTimes[0] != 0){
                if(time == taArray.ta[i].startTimes[0]){
                    availableTAs.arraySize += 1;
                    availableTAs.ta[i] = taArray.ta[i];
                    cout<< formatTime(time) <<"\t"<<availableTAs.ta[i].name<<" has began lab hours"<<endl;
                }
            }
        }
    }
};

void Simulation::getStudentsInQueue(){
    StudentsPerDay mondayStudents = studentDays.mondayStudents;
    // get all student and fill in a queue.
    if(time == 0){
        for(int i = 0; i < mondayStudents.size; i++){
            studentQueue.push(mondayStudents.students[i]);
        }
    }
}

void Simulation::moveArrivedStudentsToLaptopQueue(){
    if(!studentQueue.empty()){
        Student currentStudent = studentQueue.front();
        if(currentStudent.enterTime == time){
            cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" "<<" has arrived in TA#007"<<endl;
            studentQueue.pop();// if student has arrived then remove from student queue.
            // add student to laptop queue
            laptopQueue.push(currentStudent);
        }
    }
}

void Simulation::assignLaptopToStudent(){
    // assign laptop To Student
    if(!laptopQueue.empty()){
        Student currentStudent = laptopQueue.front();
        
        if(time == currentStudent.timePassed+2){
            currentStudent.laptopSerialNum = laptopStack.top();
            laptopStack.pop();
            cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has borrowed laptop "<<currentStudent.laptopSerialNum<<" and moved to TA line"<<endl;
            currentStudent.timePassed += 2;
            laptopQueue.pop();
            // add student to TA queue
            taQueue.push(currentStudent);
        }
    }
}

void Simulation::assignTAToStudent(){
    if(!taQueue.empty()){
        Student currentStudent = taQueue.front();
        // get TA that is free
        TA freeTA;
        for(int i = 0; i < availableTAs.arraySize; i++){
            TA currentTA = availableTAs.ta[i];
            if(!currentTA.isStudentWithTA()){
                freeTA = currentTA;
                availableTAs.ta[i].studentWithTA = currentStudent;
                // assigned current time to current student so student can be deassigned from TA
                taQueue.front().timePassed = time;
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" is getting help from "<<freeTA.name<<endl;
            }
        }
    }
}

void Simulation::deassignTAFromStudent(){
    if(!taQueue.empty()){
        Student currentStudent = taQueue.front();
        
        // deassign student from TA
//        cout<<"Current Time: "<< convertTime(time)<<endl;
//        cout<<currentStudent.firstName<<" Passed Time: "<<convertTime(currentStudent.timePassed)<<endl;
//
//        cout<<"Time when "<<currentStudent.firstName<<" is done with TA: "<<convertTime(currentStudent.timePassed+5)<<endl<<endl;
        if(time == currentStudent.timePassed+5){
            for(int i = 0; i < availableTAs.arraySize; i++){
                TA currentTA = availableTAs.ta[i];
                if(currentTA.studentWithTA.firstName == currentStudent.firstName){
                    availableTAs.ta[i].studentWithTA = Student();
                }
            }
            taQueue.pop();
            currentStudent.numAnswered +=1;
            currentStudent.timePassed += 5 ;
            if(currentStudent.numQuestions > currentStudent.numAnswered){
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has one more question answered and gotten back in line."<<endl;
                taQueue.push(currentStudent);
            }else{
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has no more questions and went home."<<endl;
            }
        }
    }
}

void Simulation::startSimulation(){
    
    
    for(time = 0; time <= 240; time++){
        
        getAvailableTAs();
        
        getStudentsInQueue();
        
        assignTAToStudent();
        
        deassignTAFromStudent();
        
        moveArrivedStudentsToLaptopQueue();
        
        assignLaptopToStudent();
        
        assignTAToStudent();
        
        
    }
};
