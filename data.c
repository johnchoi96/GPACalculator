/**
  * @file data.c
  * @author John Choi
  * @since 01072019
  *
  * Initializes data and adds and removes courses, and frees data.
  */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Data *initializeData() {
  Data *data = (Data *)malloc(sizeof(Data));
  data->size = 0;
  return data;
}

void addCourse(Data *data, const char *course, int hours, const char *grade) {
  //first, make a new course
  data->totalCredits += hours;
  Course *newCourse = (Course *)malloc(sizeof(Course));
  // fprintf(stdout, "Reached\n");
  newCourse->name = (char *)malloc(1024);
  newCourse->letterGrade = (char *)malloc(1024);
  newCourse->hours = hours;
  strcpy(newCourse->name, course);
  strcpy(newCourse->letterGrade, grade);
  // newCourse->next = NULL;

  if (data->size == 0) {
    data->course = newCourse;
    data->current = data->course;
  } else {
    while (data->current->next != NULL) {
      data->current = data->current->next;
    }
    data->current->next = newCourse;
    data->current = data->course;
  }
  data->size++;
}

void removeCourse(Data *data, const char *courseName) {

}

void freeData(Data *data) {

}
