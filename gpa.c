/**
  * @file gpa.c
  * @author John Choi
  * @since 01062019
  *
  * Driver file for this program.
  */

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fprintf(stdout, "%7s%3d%7s earned\n", data->current->name, data->current->hours, data->current->letterGrade);
    while (data->current->next != NULL) {
      data->current = data->current->next;
      fprintf(stdout, "%7s%3d%7s earned\n", data->current->name, data->current->hours, data->current->letterGrade);
    }
  }
}

/**
  * Defines behavior for the help command.
  */
void helpCommand() {
  fprintf(stdout, "\nUsage:\n");
  fprintf(stdout, "\tlist\n\tcalculate\n\tadd [COURSE] [HOURS] [LetterGrade]\n\tremove [COURSE]\n\tquit\n");
}

/**
  * Defines behavior for the calculate command.
  * Calculates the cumulative GPA.
  *
  * @param data - pointer to the data
  */
void calculateCommand(Data *data) {

}

/**
  * Defines a behavior for the add command.
  *
  * @param data - pointer to the data
  */
void addCommand(Data *data) { //TODO need to do a name duplicate check
  char *course = (char *)malloc(1024);
  int creditHours;
  char *letterGrade = (char *)malloc(1024);
  int matches = fscanf(stdin, "%s%d%s%*[^\n]\n", course, &creditHours, letterGrade);
  if (matches != 3) {
    fprintf(stdout, "Invalid command\n");
    return;
  }

  addCourse(data, course, creditHours, letterGrade);
  fprintf(stdout, "%s with %d credit hours - %s earned.\tAdded\n", course, creditHours, letterGrade);
}

/**
  * Removes the course with given name.
  * Prints the error message if the course does not exist.
  *
  * @param data - pointer to the data
  */
void removeCommand(Data *data) {

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
  return EXIT_SUCCESS;
}
