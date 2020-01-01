/**
  * @file data.h
  * @author John Choi
  * @version 02282019
  *
  * Header file that defines the struct, function prototypes,
  * and the data structure required for this program.
  * Edit 02282019: Switching from LinkedList to ArrayList. 
  */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef _DATAH_
#define _DATAH_

bool canImport;

/** Struct to represent the course. */
typedef struct _Course {
  char *name;
  int hours;
  char *letterGrade;
} Course;

/** Struct to represent the data. */
/** ArrayList */
typedef struct {
  int capacity;
  int size;
  int totalCredits;
  Course *courseList;
} Data;

/**
  * Initializes data and returns the pointer to the data.
  *
  * @returns the pointer to the data
  */
Data *initializeData();

/**
  * Adds a single course to the data.
  *
  * @param data - the pointer to the data
  * @param course - the string value of the course name
  * @param hours - the credit hour of the corresponding course
  * @param grade - the grade earned for the course
  */
void addCourse(Data *data, const char *course, int hours, const char *grade);

/**
  * Removes a course with the passed in course name.
  *
  * @param data - the pointer to the data
  * @param courseName - the name of the course to remove
  * @return true if the course was removed, false if course not found
  */
bool removeCourse(Data *data, const char *courseName);

/**
  * Frees the data and everything else.
  *
  * @param data - the pointer to the data
  */
void freeData(Data *data);

#endif
