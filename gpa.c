/**
  * @file gpa.c
  * @author John Choi
  * @since 01072019
  *
  * Driver file for this program.
  */

#include "data.h"
#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>

/**
  * Prints out failure message and terminates program.
  *
  * @param msg - failure message
  */
void fail(const char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

/**
  * Prints out the list of added courses.
  *
  * @param data - pointer to the data
  */
void listCommand(Data *data) {
  if (data->size != 0) {
    data->current = data->course;
    fprintf(stdout, "%7s%3d Hours %7s earned\n", data->current->name, data->current->hours, data->current->letterGrade);
    while (data->current->next != NULL) {
      data->current = data->current->next;
      fprintf(stdout, "%7s%3d Hours %7s earned\n", data->current->name, data->current->hours, data->current->letterGrade);
    }
  }
  fprintf(stdout, "Total of %d courseworks with %d credit hours completed\n", data->size, data->totalCredits);
}

/**
  * Defines behavior for the help command.
  */
void helpCommand() {
  fprintf(stdout, "\nUsage:\n");
  fprintf(stdout, "\tlist\n\tcalculate\n\tchart\n\tadd [COURSE] [HOURS] [LetterGrade]\n\tremove [COURSE]\n\tquit\n");
}

/**
  * Prints out the GPA chart.
  */
void chartCommand() {
  fprintf(stdout, "\n\n");
  fprintf(stdout, "%10s|%10s\n", "Grade  ", "Value");
  fprintf(stdout, "---------------------\n");
  fprintf(stdout, "---------------------\n");
  fprintf(stdout, "%10s|%10s\n", "A+  ", "4.333");
  fprintf(stdout, "%10s|%10s\n", "A   ", "4.000");
  fprintf(stdout, "%10s|%10s\n", "A-  ", "3.667");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "B+  ", "3.333");
  fprintf(stdout, "%10s|%10s\n", "B   ", "3.000");
  fprintf(stdout, "%10s|%10s\n", "B-  ", "2.667");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "C+  ", "2.333");
  fprintf(stdout, "%10s|%10s\n", "C   ", "2.000");
  fprintf(stdout, "%10s|%10s\n", "C-  ", "1.667");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "D+  ", "1.333");
  fprintf(stdout, "%10s|%10s\n", "D   ", "1.000");
  fprintf(stdout, "%10s|%10s\n", "D-  ", "0.667");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "F   ", "0.000");
  fprintf(stdout, "---------------------\n");
}

/**
  * Defines behavior for the calculate command.
  * Calculates the cumulative GPA.
  *
  * @param data - pointer to the data
  */
void calculateCommand(Data *data) {
  double gpa = calculateGPA(data);
  fprintf(stdout, "The cumulative GPA with %d coursework(s) is:\t%.3f\n\n", data->size, gpa);
}

/**
  * Finds and returns the pointer to the course with the given name.
  * O(n) linear search method.
  *
  * @param data - pointer to the data
  * @param name - name of the course to find
  * @return pointer to the course with the given name or NULL if does not exist
  */
Course *findCourse(Data *data, const char *name) {
  data->current = data->course;
  if (strcasecmp(data->current->name, name) == 0) {
    return data->current;
  }
  while (data->current->next != NULL) {
    data->current = data->current->next;
    if (strcasecmp(data->current->name, name) == 0) {
      return data->current;
    }
  }
  return NULL;
}

/**
  * Returns true if the input grade is valid.
  * Valid grades should have optional '+' or '-' following the letter,
  * which should be A, B, C, D, or F.
  *
  * @param grade - pointer to the grade
  * @return true if grade is valid
  */
bool isValidGrade(char *grade) { //TODO only A, B, C, D, F are valid
  if (strlen(grade) > 3) {
    return false;
  }
  if (strlen(grade) == 2 && (grade[1] != '+' && grade[1] != '-')) {
    return false;
  }
  if ((grade[0] >= 'A' && grade[0] <= 'F') || (grade[0] >= 'a' && grade[0] <= 'f')) {
    if (grade[0] >= 'a' && grade[0] <= 'f') {
      *(grade) = grade[0] - 32;
    }
    if (grade[0] == 'E') {
      return false;
    }
    return true;
  }
  return false;
}

/**
  * Converts all lowercases in the course title to uppercase.
  *
  * @param name - pointer to the name
  */
void toUpperCase(char *name) {
  for (int i = 0; i < strlen(name); i++) {
    if (name[i] >= 'a' && name[i] <= 'z') {
      *(name + i) = name[i] - 32;
    }
  }
}

/**
  * Defines a behavior for the add command.
  *
  * @param data - pointer to the data
  */
void addCommand(Data *data) {
  char *course = (char *)malloc(1024);
  int creditHours;
  char *letterGrade = (char *)malloc(1024);
  int matches = fscanf(stdin, "%s%d%s%*[^\n]\n", course, &creditHours, letterGrade);
  if (matches != 3) {
    fprintf(stdout, "Invalid command\n");
    return;
  }
  toUpperCase(course);
  if (!isValidGrade(letterGrade)) {
    fprintf(stdout, "Invalid grade.\n");
    return;
  }

  if (data->size != 0) {
    Course *dupCheckCourse = findCourse(data, course);
    if (dupCheckCourse != NULL) {
      fprintf(stdout, "Duplicate course %s already in the system.\n", course);
      fprintf(stdout, "Duplicate course: %s\tCredit Hours: %d\tGrade: \"%s\"\n\n", dupCheckCourse->name, dupCheckCourse->hours, dupCheckCourse->letterGrade);
      return;
    }
  }

  addCourse(data, course, creditHours, letterGrade);
  fprintf(stdout, "%s with %d credit hours - \"%s\" earned.\tAdded\n", course, creditHours, letterGrade);
}

/**
  * Removes the course with given name.
  * Prints the error message if the course does not exist.
  *
  * @param data - pointer to the data
  */
void removeCommand(Data *data) {
  char *courseName = (char *)malloc(1024);
  fscanf(stdin, "%s%*[^\n]\n", courseName);
  toUpperCase(courseName);
  if (!removeCourse(data, courseName)) {
    fprintf(stdout, "Course %s not found\n", courseName);
  }
  free(courseName);
}

/**
  * Prints the header and the program information at the beginning.
  */
void printHeader() {
  fprintf(stdout, "GPA Calculator by John Choi 2018\n");
  fprintf(stdout, "Version 1.0\n");
  fprintf(stdout, "To add a course, \"add [COURSE] [HOURS] [LETTERGRADE]\"\n");
  fprintf(stdout, "Type \"help\" to see the full list of commands\n\n");
}

/**
  * Driver function for this program.
  *
  * @return EXIT_SUCCESS if the program terminates correctly
  */
int main(void) {
  printHeader();
  char *command = (char *)malloc(1024);
  fprintf(stdout, "cmd> ");
  int matches = fscanf(stdin, "%s", command);
  if (matches != 1) {
    free(command);
    fail("Matches was not 1");
  }
  Data *data = initializeData();
  while (strcmp(command, "quit") != 0) {
    if (strcmp(command, "calculate") == 0) {
      fscanf(stdin, "%*[^\n]\n"); //clears the input buffer
      calculateCommand(data);
    } else if (strcmp(command, "add") == 0) {
      addCommand(data);
    } else if (strcmp(command, "remove") == 0) {
      removeCommand(data);
    } else if (strcmp(command, "help") == 0) {
      helpCommand();
    } else if (strcmp(command, "list") == 0) {
      listCommand(data);
    } else if (strcmp(command, "chart") == 0) {
      chartCommand();
    } else {
      fprintf(stdout, "Invalid command\n");
    }

    fprintf(stdout, "cmd> ");
    matches = fscanf(stdin, "%s", command);
    if (matches != 1) {
      free(command);
      fail("Matches was not 1");
    }
  }
  freeData(data);
  free(data);
  return EXIT_SUCCESS;
}
