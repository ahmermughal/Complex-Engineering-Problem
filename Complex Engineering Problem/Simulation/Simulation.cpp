//
//  Simulation.cpp
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#include "Simulation.h"
// Constructor
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

// This functions prints formatted time by the numbers given
// time = 0 is 12:00 PM
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
                    string output = formatTime(time)+"\t"+availableTAs.ta[i].name+" has began lab hours\n";
                    outputStrings.push(output);
                }
            }
        }
    }
};
// get all student from array and fill in a queue.
// students can then easily be poped from the front instead of keeping track of the position in an array
void Simulation::getStudentsInQueue(int num, int progNum){
    StudentsPerDay dayStudents = studentDays[progNum].dayStudents[num];
    if(time == 0){
        queue<Student> empty;
        swap(studentQueue, empty);
        
        for(int i = 0; i < dayStudents.size; i++){
            studentQueue.push(dayStudents.students[i]);
        }
    }
}
// Function moves student to the laptop queue from the main queue.
void Simulation::moveArrivedStudentsToLaptopQueue(){
    if(!studentQueue.empty()){
        Student currentStudent = studentQueue.front();
        if(currentStudent.enterTime == time){
            cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" "<<" has arrived in TA#007"<<endl;
            string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" "+" has arrived in TA#007\n";
            outputStrings.push(output);
            studentQueue.pop();// if student has arrived then remove from student queue.
            // add student to laptop queue
            laptopQueue.push(currentStudent);
        }
    }
}

// assign laptop To Student
void Simulation::assignLaptopToStudent(){
    if(time < lastTAEndTime){
        if(!laptopQueue.empty()){
            Student currentStudent = laptopQueue.front();
            
            if(time == currentStudent.timePassed+2){ // checks and sees if two mins have passed.
                currentStudent.laptopSerialNum = laptopStack.top();
                laptopStack.pop();
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has borrowed laptop "<<currentStudent.laptopSerialNum<<" and moved to TA line"<<endl;
                
                string output = formatTime(time) + "\t" + currentStudent.firstName + " " + currentStudent.lastName + " has borrowed laptop " + to_string(currentStudent.laptopSerialNum) + " and moved to TA line\n";
                outputStrings.push(output);

                currentStudent.timePassed += 2;
                laptopQueue.pop();
                // add student to TA queue
                taQueue.push(currentStudent);
            }
        }
    }
}

// assign TAs to students depending on if the TA is free.
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
                
                string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" is getting help from "+freeTA.name+"\n";
                 outputStrings.push(output);
                
            }
        }
    }
}
// deassign students from TA if their time is up
void Simulation::deassignTAFromStudent(int& expectedTimeLimit){
    if(!taQueue.empty()){
        Student currentStudent = taQueue.front();
        
        // adds more time to the lab end time if the current TA is with a student so their session can end.
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
            // if student has more questions then move student back in queue
            if(currentStudent.numQuestions > currentStudent.numAnswered){
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has one more question answered and gotten back in line."<<endl;
                taQueue.push(currentStudent);
                
                string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" has one more question answered and gotten back in line.\n";
                 outputStrings.push(output);
                
            }else{// if student is done with question then student goes home
                // giving the laptop back to the stack.
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has returned laptop "<<currentStudent.laptopSerialNum<<" and went home "<<"Happy"<<endl;
                laptopStack.push(currentStudent.laptopSerialNum);
                happy +=1;
                
                string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" has returned laptop "+to_string(currentStudent.laptopSerialNum)+" and went home Happy\n";
                 outputStrings.push(output);
            }
        }
    }
}

// set the lab run time based on the TA that leaves the lab the last.
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
// ends TAs shift when it is over
void Simulation::endTAShift(){
    if(availableTAs.arraySize != 0){
        for(int i=0; i<availableTAs.arraySize; i++){
            if(time == availableTAs.ta[i].endTimes[0]){
                // time for TA to leave
                availableTAs.arraySize -=1;
                cout<<formatTime(time)<<"\t"<<availableTAs.ta[i].name<<" has finished lab hours."<<endl;
                
                string output = formatTime(time)+"\t"+availableTAs.ta[i].name+" has finished lab hours.\n";
                 outputStrings.push(output);
                if(i == 0){
                    availableTAs.ta[0] = availableTAs.ta[1];
                }
            }
        }
    }
    
}
// When Lab time is over and there are students left in the laptop queue they go home.
void Simulation::sendAllStudentsInLaptopQueueHome(int expectedTimeLimit){
    if(time == expectedTimeLimit){
        if(laptopQueue.size() > 0){
            for(int i = laptopQueue.size(); laptopQueue.size() > 0; i--){
                Student currentStudent = laptopQueue.front();
                laptopQueue.pop();
                cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" never even got a laptop and went home FRUSTRATED."<<endl;
                
                string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" never even got a laptop and went home FRUSTRATED.\n";
                 outputStrings.push(output);
            }
        }
    }
}
// if lab time is over send students home
// checks to see if 75% of their questions are answered
void Simulation::sendAllStudentsInTAQueueHome(int& expectedTimeLimit){
    if(time == expectedTimeLimit){
        if(taQueue.size() > 0){
            Student currentStudent = taQueue.front();
            string mood;
            double num = ((double)currentStudent.numQuestions * 0.75) ;
            double numOfQAnswered = (double) currentStudent.numAnswered;
            if(numOfQAnswered >= num){
                mood = "HAPPY.";
                happy +=1;
            }else{
                mood = "FRUSTRATED.";
                frustrated += 1;
            }
            cout<<formatTime(time)<<"\t"<<currentStudent.firstName<<" "<<currentStudent.lastName<<" has returned laptop "<<currentStudent.laptopSerialNum<<" and went home "<<mood<<endl;
            
            string output = formatTime(time)+"\t"+currentStudent.firstName+" "+currentStudent.lastName+" has returned laptop "+ to_string(currentStudent.laptopSerialNum) +" and went home "+mood+"\n";
             outputStrings.push(output);
            
            expectedTimeLimit = time+1;
            taQueue.pop();
        }
    }
}

// prints the summary of the day.
void Simulation::printDaySummary(int expectedTimeLimit, int num, string day, int progNum){
    if(time == expectedTimeLimit){
        cout<<endl;
        int hours = time/60;
        double min = ((double)time/60.0 - (double)hours) * 60;
        cout<<day<<"'s Lab Summary:"<<endl;
        
        string output = "\n"+day+"'s Lab Summary:\n";
          outputStrings.push(output);
        
        cout<<"The TA Lab was open for "<<hours<<" hours and "<<round(min)<<" minutes."<<endl;
        
        //min = min + 0.5 - (min<0);
        output = "The TA Lab was open for "+to_string(hours)+" hours and "+to_string((int)round(min))+" minutes.\n";
          outputStrings.push(output);
        
        cout<<studentDays[progNum].dayStudents[num].size<<" students visited the lab. Out of those students, only "<<happy<<" left happy."<<endl;
        output = to_string(studentDays[progNum].dayStudents[num].size)+" students visited the lab. Out of those students, only "+ to_string(happy) +" left happy.\n";
          outputStrings.push(output);
        
        if(num == 2){
            cout<<"NO ONE LIKES WEDNESDAYS"<<endl;
            output = "NO ONE LIKES WEDNESDAYS\n";
              outputStrings.push(output);
        }
        cout<<"The remaining left frustrated."<<endl<<endl;
        output = "The remaining left frustrated.\n\n";
          outputStrings.push(output);
        
        cout<<"Lesson Learned:  Do not procrastinate!  Start programs early!"<<endl<<endl<<endl;
        output = "Lesson Learned:  Do not procrastinate!  Start programs early!\n\n\n";
          outputStrings.push(output);
    }
    
}

// starts the simulation
void Simulation::startSimulation(){
    
    // loop to run for the number of programs
    for(int p = 0; p< numberOfProg; p++){
        
        cout<<"**********"<<endl;
        cout<<"Program "<<p+1<<endl;
        cout<<"**********"<<endl;
        
        string output = "**********\n";
          outputStrings.push(output);
        output = "Program "+to_string((p+1))+"\n";
          outputStrings.push(output);
        output = "**********\n";
          outputStrings.push(output);
        
        // loop to run for number of days
        // hardcoded 3 as three days are mentioned in the Problem Statement.
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
            // sets a default limit to lab time
            int expectedTimeLimit = 240;
            cout<<day<<":"<<endl<<endl;
            output = day+":\n\n";
            outputStrings.push(output);
            
            // lab running from 0 = 12:00
            // end of the lab timing when the last TA's shift gets over.
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
