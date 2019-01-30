/**
  * @file data.c
  * @author John Choi
  * @since 01302019
  *
  * Initializes data and adds and removes courses, and frees data.
  */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

void freeAllCourses();

Data *initializeData() {
  Data *data = (Data *)malloc(sizeof(Data));
  data->size = 0;
  data->totalCredits = 0;
  data->course = NULL;
  data->current = NULL;
  return data;
}

void addCourse(Data *data, const char *course, int hours, const char *grade) {
  //first, make a new course
  data->totalCredits += hours;
  Course *newCourse = (Course *)malloc(sizeof(Course));
  newCourse->name = (char *)malloc(1024);
  newCourse->letterGrade = (char *)malloc(1024);
  newCourse->hours = hours;
  strcpy(newCourse->name, course);
  strcpy(newCourse->letterGrade, grade);
  newCourse->next = NULL;

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
      freeAllCourses(data);
      data->size = 0;
      data->totalCredits = 0;
      return true;
    }
    Course *next = data->current->next;
    free(data->current->name);
    free(data->current->letterGrade);
    free(data->current);
    data->current = next;
    data->course = data->current;
    removed = true;

    data->size--;
    data->totalCredits -= data->current->hours;
  } else {
    Course *nextnext = data->current->next->next; // csc316->csc216->csc116->NULL
    if (strcmp(data->current->next->name, courseName) == 0) {
      data->size--;
      data->totalCredits -= data->current->next->hours;
      free(data->current->next->name);
      free(data->current->next->letterGrade);
      free(data->current->next);
      data->current->next = nextnext;
      removed = true;
    } else { //TODO causing valgrind issues
      while (data->current->next->next != NULL) {
        if (strcmp(data->current->next->name, courseName) == 0) {
          data->size--;
          data->totalCredits -= data->current->next->hours;
          free(data->current->next->name);
          free(data->current->next->letterGrade);
          free(data->current->next);
          data->current->next = nextnext;
          removed = true;
          
          data->size--;
          data->totalCredits -= data->current->hours;
          break;
        }
        data->current = data->current->next;
      }
      if (strcmp(data->current->next->name, courseName) == 0) {
        data->size--;
        data->totalCredits -= data->current->next->hours;
        free(data->current->next->name);
        free(data->current->next->letterGrade);
        free(data->current->next);
        data->current->next = NULL;
        removed = true;
      }
    } //TODO causing valgrind issues
  }
  return removed;
}

/**
  * Removes all courses and frees all memory.
  *
  * @param data - pointer to data
  */
void freeAllCourses(Data *data) {
  data->current = data->course;
  while (data->current != NULL) {
    Course *next = data->current->next;
    free(data->current->name);
    free(data->current->letterGrade);
    free(data->current);
    data->current = next;
  }
}

void freeData(Data *data) {
  if (data->size != 0) {
    freeAllCourses(data);
  }
  free(data);
}
