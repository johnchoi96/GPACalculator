/**
  * @file data.c
  * @author John Choi
  * @since 01092019
  *
  * Initializes data and adds and removes courses, and frees data.
  */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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

/**
  * Removes all courses and frees all memory.
  *
  * @param data - pointer to data
  */
void freeAllCourses(Data *data) {
  data->current = data->course;
  free(data->current->name);
  free(data->current->letterGrade);
  while (data->current->next != NULL) {
    data->current = data->current->next;
    free(data->current->name);
    free(data->current->letterGrade);
  }
}

bool removeCourse(Data *data, const char *courseName) {
  if (strcasecmp(courseName, "all") == 0) {
    data->size = 0;
    data->totalCredits = 0;
    freeAllCourses(data);
    return true;
  }
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
  if (data->size != 0) {
    freeAllCourses(data);
    free(data->course);
    free(data->current);
  }
}
