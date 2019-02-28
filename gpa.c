/**
  * @file gpa.c
  * @author John Choi
  * @since 02252019
  *
  * Driver file for this program.
  */

#include "data.h"
#include "calculate.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TOKENS 1024

/* Every simple command has one of these associated with it */
typedef struct {
	char* token[MAX_TOKENS]; /* tokens of the command */
	int count; /* the number of tokens */ /* count - 2 gives the last argument */
} Command;

Command *parseSequence();

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
	* Compares two course objects to sort them in
	* alphabetical order.
	*
	* @param a void pointer to the first course
	* @param b void pointer to the second course
	* @return difference
	*/
int compare(const void *a, const void *b) {
	Course *firstCourse = (Course *)a;
	Course *secondCourse = (Course *)b;
	return strcmp(firstCourse->name, secondCourse->name);
}

/**
  * Sorts and prints out the list of added courses.
  *
  * @param data - pointer to the data
  */
void listCommand(Data *data) {
	qsort(data->courseList, data->size, sizeof(Course), compare);
	for (int i = 0; i < data->size; i++) {
		fprintf(stdout, "%7s%3d Hours %7s earned\n", data->courseList[i].name, data->courseList[i].hours, data->courseList[i].letterGrade);
	}
  fprintf(stdout, "Total of %d courseworks with %d credit hours completed\n", data->size, data->totalCredits);
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
	for (int i = 0; i < data->size; i++) {
		if (strcmp(name, data->courseList[i].name) == 0) {
			return &data->courseList[i];
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
void addCommand(Data *data, Command *cmd) {
  char *course = (char *)malloc(1024);
  int creditHours;
  char *letterGrade = (char *)malloc(1024);
  if (cmd->count == 5) {
    strcpy(course, cmd->token[1]);

    creditHours = atoi(cmd->token[2]);
    if (creditHours == 0) {
      free(course);
      free(letterGrade);
      fprintf(stdout, "Invalid credit hours\n");
      return;
    }
    strcpy(letterGrade, cmd->token[3]);
  } else if (cmd->count == 6) {
    strcpy(course, cmd->token[1]);
    strcat(course, cmd->token[2]);
    creditHours = atoi(cmd->token[3]);
    if (creditHours == 0) {
      free(course);
      free(letterGrade);
      fprintf(stdout, "Invalid credit hours\n");
      return;
    }
    strcpy(letterGrade, cmd->token[4]);
  } else {
    free(course);
    free(letterGrade);
    fprintf(stdout, "Invalid command\n");
    return;
  }
  toUpperCase(course);
  if (!isValidGrade(letterGrade)) {
    fprintf(stdout, "Invalid grade\n");
    free(course);
    free(letterGrade);
    return;
  }

  if (data->size != 0) {
    Course *dupCheckCourse = findCourse(data, course);
    if (dupCheckCourse != NULL) {
      fprintf(stdout, "Duplicate course %s already in the system.\n", course);
      fprintf(stdout, "Duplicate course: %s\tCredit Hours: %d\tGrade: \"%s\"\n\n", dupCheckCourse->name, dupCheckCourse->hours, dupCheckCourse->letterGrade);
      free(course);
      free(letterGrade);
      return;
    }
  }

  addCourse(data, course, creditHours, letterGrade);
  fprintf(stdout, "%s with %d credit hours - \"%s\" earned.\tAdded\n", course, creditHours, letterGrade);
  free(course);
  free(letterGrade);
}

/**
  * Removes the course with given name.
  * Prints the error message if the course does not exist.
  *
  * @param data - pointer to the data
  */
void removeCommand(Data *data, Command *cmd) {
  char *courseName = (char *)malloc(1024);
  if (cmd->count == 3) { //handles remove csc316
    strcpy(courseName, cmd->token[1]);
  } else if (cmd->count == 4) {
    strcpy(courseName, cmd->token[1]);
    strcat(courseName, cmd->token[2]);
  } else {
    free(courseName);
    fprintf(stdout, "Invalid command\n");
    return;
  }
  toUpperCase(courseName);
  if (!removeCourse(data, courseName)) {
    fprintf(stdout, "Course %s not found\n", courseName);
  }
  free(courseName);
}

/**
  * Driver function for this program.
  *
  * @return EXIT_SUCCESS if the program terminates correctly
  */
int main(void) {
  printHeader();
  char *command = (char *)malloc(1024);
  Data *data = initializeData();
  while (1) {
    fprintf(stdout, "cmd> ");
    int matches = fscanf(stdin, "%[^\n]", command);
    fscanf(stdin, "%*c");
    Command *cmd = parseSequence(command);
    if (matches != 1 || cmd->count == 1) {
      continue;
    }
    if (strcmp(cmd->token[0], "calculate") == 0) {
      calculateCommand(data);
    } else if (strcmp(cmd->token[0], "add") == 0) {
      addCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "remove") == 0) {
      removeCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "help") == 0) {
      helpCommand();
    } else if (strcmp(cmd->token[0], "list") == 0) {
      listCommand(data);
    } else if (strcmp(cmd->token[0], "chart") == 0) {
      chartCommand();
    } else if (strcmp(cmd->token[0], "quit") == 0i || strcmp(cmd->token[0], "exit") == 0) {
      free(cmd);
      break;
    } else {
      fprintf(stdout, "Command not found\n");
    }
    free(cmd);
  }
  freeData(data);
  free(command);
  return EXIT_SUCCESS;
}

/**
  * "parseSequence" function is used to parse the char line got from the
  * standard input into the simple structure to pass arguments into system
  * calls later.
  *
  * @param line - stdin
  * @return c pointer to the command struct
  */
Command *parseSequence(char *line) {
	int i, t;
	Command *c = (Command *)malloc(sizeof(Command));
	t = 0;
	i = 0;
	while (isspace(line[i])) {
		i++;
	}
	c->token[t] = &line[i];
	while (line[i] != '\0' && t < MAX_TOKENS - 1) {
		t++;
		while (!isspace(line[i]) && line[i] != '\0') {
			i++;
    }
		while (isspace(line[i])) {
			line[i] = '\0';
			i++;
		}
		c->token[t] = &line[i];
	}
	c->count = t + 1;
	c->token[t] = NULL;

	return c;
}
