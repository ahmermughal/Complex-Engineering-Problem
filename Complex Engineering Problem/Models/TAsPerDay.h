//
//  TAsPerDay.h
//  Complex Engineering Problem
//
//  Created by Ahmer Mughal on 09/05/2020.
//  Copyright © 2020 iDevelopStudio. All rights reserved.
//

#ifndef TAsPerDay_h
#define TAsPerDay_h
#include <stdio.h>
#include <string>
#include "TA.h"
// Struct which contains an array of TAs and the size of that array
typedef struct TAsPerDay {
    TA* ta;
    int arraySize;
} TAArray;

#endif /* TAsPerDay_h */
