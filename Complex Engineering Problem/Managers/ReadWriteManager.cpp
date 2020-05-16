//
//  ReadWriteManager.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "ReadWriteManager.h"

ReadWriteManager::ReadWriteManager(){
    
}
// passing by refence to make code more modular and easy to modify
stack<int> ReadWriteManager::readLaptopStack(ifstream& inFile){
    string nextItem;
    stack <int> laptopStack;
    
    // get number of laptops
    if(inFile >> nextItem){
        int numberOfLaptops = stoi(nextItem);
        
        for(int i = 0; i < numberOfLaptops; i++){
            inFile >> nextItem;
            laptopStack.push(stoi(nextItem));
        }
        //cout<<"Size Of Laptop Stack: "<<laptopStack.size()<<endl;
    }
    return laptopStack;
}

void ReadWriteManager::readTAArray(ifstream& inFile){
    string nextItem;
    
    if(inFile>>nextItem){
        int numberOfTA = stoi(nextItem);
        //cout<<numberOfTA<<endl;
        taArray.arraySize =numberOfTA;
        taArray.ta = new TA[numberOfTA];
        //TA taArr[numberOfTA];
        
        for(int i = 0; i < numberOfTA; i++){
            inFile >> nextItem;
            taArray.ta[i].name = nextItem;
            //cout<<taArr[i].name<<endl;
            
            inFile >> nextItem;
            taArray.ta[i].startTimes[0] = stoi(nextItem);
            
            inFile >> nextItem;
            taArray.ta[i].endTimes[0] = stoi(nextItem);
            
            inFile >> nextItem;
            taArray.ta[i].startTimes[1] = stoi(nextItem);
            
            inFile >> nextItem;
            taArray.ta[i].endTimes[1] = stoi(nextItem);
            
            inFile >> nextItem;
            taArray.ta[i].startTimes[2] = stoi(nextItem);
            
            inFile >> nextItem;
            taArray.ta[i].endTimes[2] = stoi(nextItem);
        }
        
//        cout<<"Size of TA Array: "<<numberOfTA<< endl;
//
//        for(int i = 0; i < numberOfTA; i++){
//            cout<<taArray.ta[i].name<< endl;
//        }
    }
}

Student* ReadWriteManager::readStudentArray(ifstream& inFile, int& size){
    string nextItem;
    
    if(inFile>>nextItem){
        int numberOfStudent = stoi(nextItem);
        Student* studentArr = new Student[numberOfStudent];
        
        for(int i = 0; i < numberOfStudent; i++){
            inFile >> nextItem;
            studentArr[i].enterTime = stoi(nextItem);
            studentArr[i].timePassed = studentArr[i].enterTime;
            
            inFile >> nextItem;
            studentArr[i].firstName = nextItem;

            inFile >> nextItem;
            studentArr[i].lastName = nextItem;

            inFile >> nextItem;
            studentArr[i].numQuestions = stoi(nextItem);
        }
        
//        for(int i = 0; i < numberOfStudent; i++){
//            cout<<"Enter Time: "<<studentArr[i].enterTime<< endl;
//            cout<<"First Name: "<<studentArr[i].firstName<< endl;
//            cout<<"Last Name: "<<studentArr[i].lastName<< endl;
//            cout<<"Number Of Questions: "<<studentArr[i].numQuestions<< endl;
//            cout<<"\t ------------------- \n";
//        }
//        cout<<"Next Day \n\n\n";
        size = numberOfStudent;
        return studentArr;
    }
    return nullptr;
}

void ReadWriteManager::readFromFile(){
    string fileName = "input.txt";
    ifstream inFile(fileName);
    
    // get all the laptop stack
    laptopStack = readLaptopStack(inFile);
    //cout<<"Size Of Laptop Stack: "<<laptopStack.size()<<endl;

    // get all the TA
    readTAArray(inFile);
    
    // get Number Of Programs Per Semester
    string nextItem;
    if(inFile >> nextItem){
        numberOfPrograms = stoi(nextItem);
    }
    int size = 0;

    studentDays = new StudentDays[numberOfPrograms];
    
    // get all Monday Students
    studentDays[0].dayStudents = new StudentsPerDay[3];
    studentDays[0].dayStudents[0].students = readStudentArray(inFile, size);
    studentDays[0].dayStudents[0].size = size;
    
    // get all Tuesday Students
    studentDays[0].dayStudents[1].students = readStudentArray(inFile, size);
    studentDays[0].dayStudents[1].size = size;
    
    // get All Wednesday Students;
    studentDays[0].dayStudents[2].students = readStudentArray(inFile, size);
    studentDays[0].dayStudents[2].size = size;

    studentDays[1].dayStudents = new StudentsPerDay[3];
    studentDays[1].dayStudents[0].students = readStudentArray(inFile, size);
    studentDays[1].dayStudents[0].size = size;

    // get all Tuesday Students
    studentDays[1].dayStudents[1].students = readStudentArray(inFile, size);
    studentDays[1].dayStudents[1].size = size;

    // get All Wednesday Students;
    studentDays[1].dayStudents[2].students = readStudentArray(inFile, size);
    studentDays[1].dayStudents[2].size = size;
    
}
