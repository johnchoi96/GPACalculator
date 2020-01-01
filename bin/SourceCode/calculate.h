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

/**
  * Calculates the cumulative GPA based on the courses in the data
  * struct.
  *
  * @param data pointer to the data
  * @return gpa the cumulative gpa
  */
double calculateGPA(Data *data);

/**
  * Calculates the major GPA given by the subject code.
  *
  * @param data pointer to the data
  * @param major subject code
  * @param totalCoursework total hours of this subject. This value will be
  *   changed by this function.
  * @return gpa the major gpa
  */
double calculateMajorGPA(Data *data, const char *major, int *totalCoursework);

#endif
