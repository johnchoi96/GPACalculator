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
#include <stdbool.h>

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

bool removeCourse(Data *data, const char *courseName) {
  bool removed = false;
  if (data->size == 0) {
    return false;
  }
  data->current = data->course;
  if (strcmp(data->current->name, courseName) == 0) {
    if (data->size == 1) {
      // data->current = NULL;
      free(data->course);
      data->current = data->course;
      data->size = 0;
      data->totalCredits = 0;
      return true;
    }
    data->current = data->current->next;
    data->course = data->current;
    removed = true;

    data->size--;
    data->totalCredits -= data->current->hours;
  } else {
    Course *prev = data->current;
    while (data->current->next != NULL) {
      data->current = data->current->next;
      if (strcmp(data->current->name, courseName) == 0) {
        prev->next = data->current->next;
        removed = true;

        data->size--;
        data->totalCredits -= data->current->hours;
        break;
      }
      prev = data->current;
    }
  }
  return removed;
}

void freeData(Data *data) {

}
