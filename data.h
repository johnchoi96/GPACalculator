/**
  * @file data.h
  * @author John Choi
  * @since 01062019
  *
  * Header file that defines the struct, function prototypes,
  * and the data structure required for this program.
  */

#include <stdio.h>
#include <stdlib.h>

/** Struct to represent the course. */
typedef struct Course {
  char *name;
  int hours;
  char *letterGrade;
  struct Course *next;
} Course;

/** Struct to represent the data. */
typedef struct {
  int size;
  Course *course; //head
  Course *current;
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
  */
void removeCourse(Data *data, const char *courseName);

/**
  * Frees the data and everything else.
  *
  * @param data - the pointer to the data
  */
void freeData(Data *data);
