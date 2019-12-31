/**
  * @file calculate.c
  * @author John Choi
  * @version 12302019
  *
  * Calculates overall GPA based on the courses added to the data.
  *
  * Changes August 11, 2019:
  *   GPA scale now based on The Ohio State University, Columbus, OH.
  */

#include "data.h"
#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <assert.h>

/**
  * Converts the letter grade to a double number value.
  * A+ does not exist at OSU but supported for students at other institutions.
  *
  * @param grade letter grade to convert
  * @return number value of the letter grade
  */
double convertToNumeric(const char *grade) {
  if (strcmp(grade, "A+") == 0) {
    return 4.3;
  } else if (strcmp(grade, "A") == 0) {
    return 4.0;
  } else if (strcmp(grade, "A-") == 0) {
    return 3.7;
  } else if (strcmp(grade, "B+") == 0) {
    return 3.3;
  } else if (strcmp(grade, "B") == 0) {
    return 3.0;
  } else if (strcmp(grade, "B-") == 0) {
    return 2.7;
  } else if (strcmp(grade, "C+") == 0) {
    return 2.3;
  } else if (strcmp(grade, "C") == 0) {
    return 2.0;
  } else if (strcmp(grade, "C-") == 0) {
    return 1.7;
  } else if (strcmp(grade, "D+") == 0) {
    return 1.3;
  } else if (strcmp(grade, "D") == 0) {
    return 1.0;
  } else if (strcmp(grade, "D-") == 0) {
    return 0.7;
  } else {
    return 0;
  }
}

/**
  * Calculates the cumulative GPA.
  * Formula is (grade * credits) / credits.
  * Skips over S/U grades when calculating GPA.
  *
  * @param data pointer to the data struct
  * @return cumulative GPA
  */
double calculateGPA(Data *data) {
  double gpa = 0;
  if (data->size == 0) {
    return 0;
  }

  int creditOnly = 0;
  for (int i = 0; i < data->size; i++) {
    if (strcmp(data->courseList[i].letterGrade, "S") == 0 || strcmp(data->courseList[i].letterGrade, "U") == 0) {
      creditOnly += data->courseList[i].hours;
    } else {
        gpa += (convertToNumeric(data->courseList[i].letterGrade) * data->courseList[i].hours);
    }
  }
  if (data->totalCredits - creditOnly > 0) {
    gpa /= (data->totalCredits - creditOnly);
  } else {
    gpa = 0;
  }
  return gpa;
}

bool startsWith(const char *subjectCode, const char *course) {
  assert(strlen(course) >= strlen(subjectCode));
  for (int i = 0; i < strlen(subjectCode); i++) {
    if (subjectCode[i] != course[i]) {
      return false;
    }
  }
  return true;
}

/**
  * Calculates the major GPA given by the subject code.
  *
  * @param data pointer to the data
  * @param major subject code
  * @param totalCoursework total hours of this subject. This value will be
  *   changed by this function.
  * @return gpa the major gpa
  */
double calculateMajorGPA(Data *data, const char *subjectCode, int *totalCoursework) {
  double gpa = 0;
  if (data->size == 0) {
    return 0;
  }

  *totalCoursework = 0;
  int totalHours = 0;
  for (int i = 0; i < data->size; i++) {
    // if the subject name starts with the subject code
    if (strlen(data->courseList[i].name) >= strlen(subjectCode) && startsWith(subjectCode, data->courseList[i].name)) {
      // and if the course does not have a S/U grade
      if (strcmp(data->courseList[i].letterGrade, "S") != 0 && strcmp(data->courseList[i].letterGrade, "U") != 0) {
        totalHours += data->courseList[i].hours;
        gpa += (convertToNumeric(data->courseList[i].letterGrade) * data->courseList[i].hours);
      }
      (*totalCoursework)++;
    }
  }
  if (totalHours > 0) {
    gpa /= totalHours;
  } else {
    gpa = 0;
  }
  return gpa;
}
