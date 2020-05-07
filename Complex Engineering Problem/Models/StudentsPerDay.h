//
//  StudentsPerDay.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 08/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef StudentsPerDay_h
#define StudentsPerDay_h
#include <stdio.h>
#include <string>
#include "Student.h"

typedef struct StudentsPerDay {
    Student* students;
    int size;          
} StudentsPerDay;

#endif /* StudentsPerDay_h */
