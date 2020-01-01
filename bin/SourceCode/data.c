/**
  * @file data.c
  * @author John Choi
  * @version 08112019
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
  data->capacity = 20;
  data->size = 0;
  data->totalCredits = 0;
  data->courseList = (Course *)malloc(data->capacity * sizeof(Course));
  return data;
}

void addCourse(Data *data, const char *course, int hours, const char *grade) {
  canImport = false;
  data->totalCredits += hours;

  //first, make a new course
  Course newCourse;
  newCourse.name = strdup(course);
  newCourse.letterGrade = strdup(grade);
  newCourse.hours = hours;
  if (data->size >= data->capacity) {
    data->capacity += 20;
    Course *newCourseList = (Course *)calloc(data->capacity, sizeof(Course));
    for (int i = 0; i < data->size; i++) {
      newCourseList[i] = data->courseList[i];
    }
    free(data->courseList);
    data->courseList = (Course *)calloc(data->capacity, sizeof(Course));
    for (int i = 0; i < data->size; i++) {
      data->courseList[i] = newCourseList[i];
    }
    free(newCourseList);
  }
  data->courseList[data->size] = newCourse;
  data->size++;
}

bool removeCourse(Data *data, const char *courseName) {
  if (strcasecmp(courseName, "all") == 0) {
    freeAllCourses(data);
    canImport = true;
    data->size = 0;
    data->totalCredits = 0;
    data->capacity = 20;
    data->courseList = (Course *)malloc(data->capacity * sizeof(Course));
    return true;
  }
  bool removed = false;
  if (data->size == 0) {
    return false;
  }
  int index;
  for (index = 0; index < data->size; index++) {
    if (strcmp(courseName, data->courseList[index].name) == 0) {
      removed = true;
      free(data->courseList[index].name);
      free(data->courseList[index].letterGrade);
      data->totalCredits -= data->courseList[index].hours;
      break;
    }
  }
  if (removed) {
    for (int i = index; i < data->size - 1; i++) {
      data->courseList[i] = data->courseList[i + 1];
    }
    data->size--;
  }
  return removed;
}

/**
  * Removes all courses and frees all memory.
  *
  * @param data - pointer to data
  */
void freeAllCourses(Data *data) {
  for (int i = 0; i < data->size; i++) {
    free(data->courseList[i].name);
    free(data->courseList[i].letterGrade);
  }
  free(data->courseList);
}

void freeData(Data *data) {
  freeAllCourses(data);
  free(data);
}
