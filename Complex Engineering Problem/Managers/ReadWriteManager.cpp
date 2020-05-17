//
//  ReadWriteManager.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "ReadWriteManager.h"

// This class is used to manage the IO of the simulation
// Reading from the file to get the data
ReadWriteManager::ReadWriteManager(){
    
}
// function reads the laptops from the file and returns a stack.
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
    }
    return laptopStack;
}

// function reads TAs from the file and saved them in an object TAArray
void ReadWriteManager::readTAArray(ifstream& inFile){
    string nextItem;
    
    if(inFile>>nextItem){
        int numberOfTA = stoi(nextItem);
        taArray.arraySize =numberOfTA;
        taArray.ta = new TA[numberOfTA];
        
        for(int i = 0; i < numberOfTA; i++){
            inFile >> nextItem;
            taArray.ta[i].name = nextItem;
            
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
        
    }
}
// Function takes in two parameters to read students from the file and return a student array
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
