//
//  Simulation.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "Simulation.h"

Simulation::Simulation(StudentDays* studentD, stack<int> laptopS, TAArray tas, int numberOfPrograms){
    studentDays = studentD;
    laptopStack = laptopS;
    taArray = tas;
    availableTAs.arraySize = 0;
    availableTAs.ta = new TA[tas.arraySize];
    time = 0;
    lastTAEndTime = 0;
    numberOfProg = numberOfPrograms;
    
}


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
            while (time >= 60)
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

void Simulation::getAvailableTAs(int num){
    // getting TAs according to their timing
    // and adding to list of avaiable TA during this day
    if(availableTAs.arraySize != taArray.arraySize){
        for(int i = 0; i < taArray.arraySize; i++){
            if(taArray.ta[i].endTimes[num] != 0){
                if(time == taArray.ta[i].startTimes[num]){
                    availableTAs.arraySize += 1;
                    availableTAs.ta[i] = taArray.ta[i];
                    cout<< formatTime(time) <<"\t"<<availableTAs.ta[i].name<<" has began lab hours"<<endl;
                }
            }
        }
    }
};

void Simulation::getStudentsInQueue(int num, int progNum){
    StudentsPerDay dayStudents = studentDays[progNum].dayStudents[num];
    // get all student and fill in a queue.
    if(time == 0){
        queue<Student> empty;
        swap(studentQueue, empty);
        
        for(int i = 0; i < dayStudents.size; i++){
            studentQueue.push(dayStudents.students[i]);
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
    if(time < lastTAEndTime){
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

void Simulation::deassignTAFromStudent(int& expectedTimeLimit){
    if(!taQueue.empty()){
        Student currentStudent = taQueue.front();
        
        for(int i = 0; i < availableTAs.arraySize; i++){
            TA currentTA = availableTAs.ta[i];
            if(time == expectedTimeLimit && currentTA.isStudentWithTA()){
                expectedTimeLimit +=1;
            }
        }
        
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
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has returned laptop "<<currentStudent.laptopSerialNum<<" and went home "<<"Happy"<<endl;
                laptopStack.push(currentStudent.laptopSerialNum);
                happy +=1;
            }
        }
    }
}

void Simulation::setExpectedLabRunTime(int& expectedRunTime, int num){
    if(time == 0){
        int maxTime = 0;
        for(int i=0; i<availableTAs.arraySize; i++){
            if(maxTime <= availableTAs.ta[i].endTimes[num]) maxTime = availableTAs.ta[i].endTimes[num];
        }
        expectedRunTime = maxTime;
        lastTAEndTime = maxTime;
    }
}

void Simulation::endTAShift(){
    if(availableTAs.arraySize != 0){
        for(int i=0; i<availableTAs.arraySize; i++){
            if(time == availableTAs.ta[i].endTimes[0]){
                // time for TA to leave
                availableTAs.arraySize -=1;
                cout<<formatTime(time)<<"\t"<<availableTAs.ta[i].name<<" has  finished lab hours."<<endl;
                if(i == 0){
                    availableTAs.ta[0] = availableTAs.ta[1];
                }
            }
        }
    }
    
}

void Simulation::sendAllStudentsInLaptopQueueHome(int expectedTimeLimit){
    if(time == expectedTimeLimit){
        if(laptopQueue.size() > 0){
            for(int i = laptopQueue.size(); laptopQueue.size() > 0; i--){
                Student currentStudent = laptopQueue.front();
                laptopQueue.pop();
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" never even got a laptop and went home FRUSTRATED."<<endl;
            }
        }
    }
}

void Simulation::sendAllStudentsInTAQueueHome(int& expectedTimeLimit){
    if(time == expectedTimeLimit){
        if(taQueue.size() > 0){
            Student currentStudent = taQueue.front();
            string mood;
            double num = ((double)currentStudent.numQuestions * 0.75) ;
            double numOfQAnswered = (double) currentStudent.numAnswered;
            //cout<<currentStudent.firstName<<" "<<currentStudent.lastName<<" got "<<numOfQAnswered<<" answered but needed "<<num<<" to be happy"<<endl<<endl;
            if(numOfQAnswered >= num){
                mood = "HAPPY.";
                happy +=1;
            }else{
                mood = "FRUSTRATED.";
                frustrated += 1;
            }
            cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has returned laptop "<<currentStudent.laptopSerialNum<<" and went home "<<mood<<endl;
            expectedTimeLimit = time+1;
            taQueue.pop();
        }
    }
}

void Simulation::printDaySummary(int expectedTimeLimit, int num, string day, int progNum){
    if(time == expectedTimeLimit){
        cout<<endl;
        int hours = time/60;
        double min = ((double)time/60.0 - (double)hours) * 60;
        cout<<day<<"'s Lab Summary:"<<endl;
        cout<<"The TA Lab was open for "<<hours<<" hours and "<<min<<" minutes."<<endl;
        cout<<studentDays[progNum].dayStudents[num].size<<" students visited the lab. Out of those students, only "<<happy<<" left happy."<<endl;
        if(num == 2){
            cout<<"NO ONE LIKES WEDNESDAYS"<<endl;
        }
        cout<<"The remaining left frustrated."<<endl<<endl;
        
        cout<<"Lesson Learned:  Do not procrastinate!  Start programs early!"<<endl<<endl<<endl;

        
    }
    
}

void Simulation::startSimulation(){    
    
    
    for(int p = 0; p< numberOfProg; p++){
        
        cout<<"**********"<<endl;
        cout<<"Program "<<p+1<<endl;
        cout<<"**********"<<endl;
        
        for(int i =0; i<3; i++){
            
            string day;
            switch (i) {
                case 0:
                    day = "Monday";
                    break;
                case 1:
                    day = "Tuesday";
                    break;
                default:
                    day = "Wednesday";
                    break;
            }
            
            happy = 0;
            frustrated = 0;

            
            int expectedTimeLimit = 240;
            cout<<day<<":"<<endl<<endl;
            
            for(time = 0; time <= expectedTimeLimit; time++){
                getAvailableTAs(i);
                setExpectedLabRunTime(expectedTimeLimit, i);
                getStudentsInQueue(i, p);
                assignLaptopToStudent();
                assignTAToStudent();
                deassignTAFromStudent(expectedTimeLimit);
                moveArrivedStudentsToLaptopQueue();
                assignTAToStudent();
                sendAllStudentsInLaptopQueueHome(expectedTimeLimit);
                endTAShift();
                sendAllStudentsInTAQueueHome(expectedTimeLimit);
                printDaySummary(expectedTimeLimit, i, day, p);
            }
            
        }
    }
};
