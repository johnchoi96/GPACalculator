/**
  * @file calculate.c
  * @author John Choi
  * @since 05082019
  *
  * Calculates overall GPA based on the courses added to the data.
  */

#include "data.h"
#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
  * Converts the letter grade to a double number value.
  *
  * @param grade - letter grade to convert
  * @return number value of the letter grade
  */
double convertToNumeric(const char *grade) {
  if (strcmp(grade, "A+") == 0) {
    return 4.333;
  } else if (strcmp(grade, "A") == 0) {
    return 4.0;
  } else if (strcmp(grade, "A-") == 0) {
    return 3.667;
  } else if (strcmp(grade, "B+") == 0) {
    return 3.333;
  } else if (strcmp(grade, "B") == 0) {
    return 3.0;
  } else if (strcmp(grade, "B-") == 0) {
    return 2.667;
  } else if (strcmp(grade, "C+") == 0) {
    return 2.333;
  } else if (strcmp(grade, "C") == 0) {
    return 2.0;
  } else if (strcmp(grade, "C-") == 0) {
    return 1.667;
  } else if (strcmp(grade, "D+") == 0) {
    return 1.333;
  } else if (strcmp(grade, "D") == 0) {
    return 1.0;
  } else if (strcmp(grade, "D-") == 0) {
    return 0.667;
  } else {
    return 0;
  }
}

/**
  * Formula is (grade * credits) / credits.
  * Skips over S/U grades.
  *
  * @param data - pointer to the data struct
  * @return cumulative GPA
  */
double calculateGPA(Data *data, int creditOnly) {
  double gpa = 0;
  if (data->size == 0) {
    return 0;
  }

  for (int i = 0; i < data->size; i++) {
    if (strcmp(data->courseList[i].letterGrade, "S") != 0 || strcmp(data->courseList[i].letterGrade, "U") != 0) {
      gpa += (convertToNumeric(data->courseList[i].letterGrade) * data->courseList[i].hours);
    }
  }
  gpa /= (data->totalCredits - creditOnly);
  return gpa;
}
