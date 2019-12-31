/**
  * @file calculate.h
  * @author John Choi
  * @version 12302019
  *
  * Header file that defines function prototypes required for
  * calculating the cumulative GPA.
  */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef _CALCULATEH_
#define _CALCULATEH_

/** Counts the hour of credit only classes */
extern int creditOnlyHours;

/**
  * Calculates the cumulative GPA based on the courses in the data
  * struct.
  *
  * @param data - pointer to the data
  * @return gpa - the cumulative gpa
  */
double calculateGPA(Data *data);

#endif
