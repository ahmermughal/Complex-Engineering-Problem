//
//  StudentDays.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef StudentDays_h
#define StudentDays_h
#include "StudentsPerDay.h"
// Struct that contains an array of StudentPerDay stuck and the size of that array
// size is hardcoded because the problem statement said there will only be 3 days.
typedef struct StudentDays {
    StudentsPerDay* dayStudents;
    int size = 3;
} StudentDays;

#endif /* StudentDays_h */
