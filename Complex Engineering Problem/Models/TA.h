//
//  TA.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 07/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef TA_h
#define TA_h

#include <stdio.h>
#include <string>
#include "Student.h"
// sturct that defines what a TA contains
using namespace std;
typedef struct teachingAssistant {
    string name; // only use first names for the TAs
    int startTimes[3]; // starting time of the 3 days
    int endTimes[3]; // ending time of the 3 days
    Student studentWithTA;
    
    // checks weather there is a student with TA or not.
    bool isStudentWithTA(){
        if(studentWithTA.firstName == ""){
            return false;
        }else{
            return true;
        }
    }
} TA;

#endif /* TA_h */
