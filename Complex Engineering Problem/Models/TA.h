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

using namespace std;
typedef struct teachingAssistant {
    string name; // only use first names for the TAs
    int startTimes[3];
    int endTimes[3];
    Student studentWithTA;
    int minute;
    
    bool isStudentWithTA(){
        if(studentWithTA.firstName == ""){
            return false;
        }else{
            return true;
        }
    }
} TA;

#endif /* TA_h */
