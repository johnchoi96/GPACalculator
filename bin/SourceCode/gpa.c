/**
  * @file gpa.c
  * @author John Choi
  * @version 01012020
  *
  * Driver file for this program.
  */

#include "data.h"
#include "file.h"
#include "calculate.h"
#include "print.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#ifndef unix
#include <windows.h>
#endif

#define MAX_TOKENS 1024

/* Every simple command has one of these associated with it */
typedef struct {
	char* token[MAX_TOKENS]; /* tokens of the command */
	int count; /* the number of tokens */ /* count - 2 gives the last argument */
} Command;

// parses input from the user
Command *parseSequence();
// changes passed in string to uppercase
void toUpperCase(char *string);

/**
  * Prints out failure message and terminates program.
  *
  * @param msg failure message
  */
void fail(const char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(EXIT_FAILURE);
}

/**
  * Prints the list of save files ending in .gpa.
  */
void printFileList() {
  // Structs
  DIR *dp;
  struct dirent *files;

	const char *path = "./savefiles";
  dp = opendir(path);
  if (!dp) {
    fprintf(stdout, "Error while opening the directory.\n");
		return;
  }
	fprintf(stdout, "List of savefiles:\n\n");
  while ((files = readdir(dp)) != NULL) {
		if (strlen(files->d_name) > 4 && !strcmp(files->d_name + strlen(files->d_name) - 4, ".gpa")) {
	    fprintf(stdout, "\t%30s\n", files->d_name);
		}
  }
	fprintf(stdout, "\n");
  closedir(dp);
}

/**
  * Defines behavior for export command.
	* Checks if the savefiles directory exists, takes in the file name,
	* and creates the save file.
  *
  * @param data pointer to the data struct
	* @param cmd input from the user
  */
void exportCommand(Data *data, Command *cmd) {
	if (cmd->count != 2) {
		fprintf(stdout, "Usage: export\n");
		return;
	}

	// check if the directory "savefiles" exists
	struct stat s;
	bool dirExists = true;
	int exists = stat("./savefiles", &s);
	if (exists == -1) {
		fprintf(stdout, "Directory \"savefiles\" directory will be created.\n");
		dirExists = false;
	}

  if (dirExists) {
	  printFileList();
	}

  char *fullName = (char *)malloc(MAX_TOKENS);
  strcpy(fullName, "");

	fprintf(stdout, "Specify the file name. \".gpa\" suffix will be appended.\n");
	fprintf(stdout, "\nFILE NAME: ");
	fscanf(stdin, "%[^\n]", fullName);
	fscanf(stdin, "%*c");
	Command *nameInput = parseSequence(fullName);
	if (nameInput->count != 2) {
	  if (nameInput->count == 1) {
	    fprintf(stdout, "File name cannot be blank\n");
	  } else {
	    fprintf(stdout, "File name cannot contain a space\n");
	  }
	  free(fullName);
	  free(nameInput);
	  return;
	}

	// create directory if it does not exist
	if (!dirExists) {
#ifdef unix
		mkdir("./savefiles", 0777);
#else
    CreateDirectory("./savefiles", NULL);
#endif
	}
	char *partialName = (char *)malloc(MAX_TOKENS);
	strcpy(partialName, "");
	sprintf(partialName, "%s%s", nameInput->token[0], ".gpa");
	sprintf(fullName, "%s%s", "./savefiles/", partialName);
	fprintf(stdout, "\n");
  export(data, fullName);
  fprintf(stdout, "File exported as %s\n", fullName);
	free(partialName);
  free(fullName);
  free(nameInput);
}

/**
  * Defines behavior for import command.
	* Checks if the save file directory exists, and if it does not, quits.
	* Lists the list of files in the save files directory with suffix .gpa.
	* Reads the save file and imports data.
  *
  * @param data pointer to the data struct
	* @param cmd input from the user
  */
void importCommand(Data *data, Command *cmd) {
  if (!canImport) {
    fprintf(stdout, "Must clear current course entries with \"remove all\" command.\n\n");
    return;
  }
  if (cmd->count != 2) {
    fprintf(stdout, "Usage: import\n");
    return;
  }
	// check if the directory "savefiles" exists if unix is defined
	struct stat s;
	int exists = stat("./savefiles", &s);
	if (exists == -1) {
		fprintf(stdout, "Directory \"savefiles\" does not exist!\n");
		fprintf(stdout, "GPA Calculator now retrieves the save files from the directory \"savefiles\".\n");
		fprintf(stdout, "Create \"savefiles\" directory? (y/n)\n> ");
		char *response = strdup("y");
		fscanf(stdin, "%[^\n]", response);
		fscanf(stdin, "%*c");
		if (strcasecmp(response, "y") == 0) {
#ifdef unix
			mkdir("./savefiles", 0777);
#else
      CreateDirectory("./savefiles", NULL);
#endif
			fprintf(stdout, "Directory \"savefiles\" created.\n");
		}
		free(response);
		return;
	}
	// at this point, savefiles directory exists so print the list of save files.
	printFileList();

	char *fullName = (char *)malloc(MAX_TOKENS);
	strcpy(fullName, "");
	fprintf(stdout, "Specify the file name. \".gpa\" suffix will be appended.\n");
	fprintf(stdout, "\nFILE NAME: ");
	fscanf(stdin, "%[^\n]", fullName);
	fscanf(stdin, "%*c");
	Command *nameInput = parseSequence(fullName);
	if (nameInput->count != 2) {
	  if (nameInput->count == 1) {
	    fprintf(stdout, "File name cannot be blank\n");
	  } else {
	    fprintf(stdout, "File name cannot contain a space\n");
	  }
	  free(fullName);
	  free(nameInput);
	  return;
	}

	char *filename = strdup(nameInput->token[0]);
	strcpy(fullName, "");
	sprintf(fullName, "%s%s%s", "./savefiles/", filename, ".gpa");
	fprintf(stdout, "\n");
  if (import(data, fullName)) {
    canImport = false;
    fprintf(stdout, "File %s imported successfully\n", fullName);
  }
	free(filename);
  free(nameInput);
	free(fullName);
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
  * Calculates the cumulative GPA.
  *
  * @param data pointer to the data
  */
void calculate(Data *data) {
  double gpa = calculateGPA(data);
  fprintf(stdout, "The cumulative GPA with %d coursework(s) is:\t%.3f\n\n", data->size, gpa);
}

/**
  * Calculates GPA and prints out the list of added courses.
  *
  * @param data pointer to the data
	* @param cmd user input
  */
void listCommand(Data *data, Command *cmd) {
	if (cmd->count == 3 && strcasecmp(cmd->token[0], "calculate") == 0 && strcasecmp(cmd->token[1], "major") == 0) {
		fprintf(stdout, "\nEnter subject code> ");
		char *subjectCode = (char *)malloc(30);
		fscanf(stdin, "%[^\n]", subjectCode);
		fscanf(stdin, "%*c");
		toUpperCase(subjectCode);
		int *totalCoursework = (int *)malloc(sizeof(int));
		double gpa = calculateMajorGPA(data, subjectCode, totalCoursework);
	  fprintf(stdout, "\nThe major GPA of %s with %d coursework(s) is:\t%.3f\n\n", subjectCode, *totalCoursework, gpa);
		free(subjectCode);
		free(totalCoursework);
	} else {
		for (int i = 0; i < data->size; i++) {
	    fprintf(stdout, "%20s%3d Hours %7s%-3s earned\n", data->courseList[i].name, data->courseList[i].hours, "", data->courseList[i].letterGrade);
	  }
	  fprintf(stdout, "\nTotal of %d courseworks with %d credit hours completed\n", data->size, data->totalCredits);

	  // calculate and print cumulative GPA
	  calculate(data);
	}
}

/**
  * Uses binary search method to find the course in the list.
  * Produces O(log n) runtime at worst case.
  *
  * @param courseList sorted list of courses
  * @param lowIndex bottom index
  * @param highIndex top index
  * @param name target name of the course to find
  * @return pointer to the found course, NULL if not found
  */
Course *binarySearchCourse(Course *courseList, int lowIndex, int highIndex, const char *name) {
  // Base condition
	if (lowIndex > highIndex) {
		return NULL;
	}

	int midIndex = (lowIndex + highIndex) / 2;

	// Base condition (target value is found)
	if (strcmp(name, courseList[midIndex].name) == 0) {
		return &courseList[midIndex];
  } else if (strcmp(name, courseList[midIndex].name) < 0) {
		return binarySearchCourse(courseList, lowIndex,  midIndex - 1, name);
  } else {
		return binarySearchCourse(courseList, midIndex + 1,  highIndex, name);
  }
}

/**
  * Finds and returns the pointer to the course with the given name.
  * O(log n) binary search method.
  *
  * @param data pointer to the data
  * @param name name of the course to find
  * @return pointer to the course with the given name or NULL if does not exist
  */
Course *findCourse(Data *data, const char *name) {
	return binarySearchCourse(data->courseList, 0, data->size - 1, name);
}

/**
  * Returns true if the input grade is valid.
  * Valid grades should have optional '+' or '-' following the letter,
  * which should be A, B, C, D, F, U, or S.
  *
  * @param grade pointer to the grade
  * @return true if grade is valid
  */
bool isValidGrade(char *grade) {
  if (strlen(grade) > 3) {
    return false;
  }
  if (strlen(grade) == 2 && (grade[1] != '+' && grade[1] != '-')) {
    return false;
  }
  if (grade[0] >= 'A' && grade[0] <= 'F') {
    if (grade[0] == 'E') {
      return false;
    }
    return true;
  } else if (grade[0] == 'U' || grade[0] == 'S') {
		return true;
	} else {
		return false;
	}
}

/**
  * Converts all lowercases in the string to uppercase.
  *
  * @param name - pointer to the name
  */
void toUpperCase(char *string) {
  for (int i = 0; i < strlen(string); i++) {
    if (string[i] >= 'a' && string[i] <= 'z') {
      *(string + i) = string[i] - 32;
    }
  }
}

/**
  * Defines a behavior for the add command.
  * Sorts the list after addition.
  *
  * @param data pointer to the data
  */
void addCommand(Data *data, Command *cmd) {
  char *course = NULL;
  int creditHours;
  char *letterGrade = NULL;
  if (cmd->count == 5) {
		course = strdup(cmd->token[1]);

    creditHours = atoi(cmd->token[2]);
    if (creditHours == 0) {
      free(course);
      free(letterGrade);
      fprintf(stdout, "Invalid credit hours\n");
      return;
    }
		letterGrade = strdup(cmd->token[3]);
  } else if (cmd->count == 6) {
		course = strdup(cmd->token[1]);
    strcat(course, cmd->token[2]);
    creditHours = atoi(cmd->token[3]);
    if (creditHours == 0) {
      free(course);
      free(letterGrade);
      fprintf(stdout, "Invalid credit hours\n");
      return;
    }
		letterGrade = strdup(cmd->token[4]);
  } else {
    free(course);
    free(letterGrade);
    fprintf(stdout, "Invalid command\n");
    return;
  }

  toUpperCase(course); // capitalize the course name
  toUpperCase(letterGrade); // capitalize the letter grade
  if (!isValidGrade(letterGrade)) {
    fprintf(stdout, "Invalid grade\n");
    free(course);
    free(letterGrade);
    return;
  }

	// check for duplicates
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
	qsort(data->courseList, data->size, sizeof(Course), compare);
  fprintf(stdout, "%s with %d credit hours - \"%s\" earned.\tAdded\n", course, creditHours, letterGrade);
  free(course);
  free(letterGrade);
}

/**
  * Removes the course with given name.
  * Prints the error message if the course does not exist.
  *
  * @param data pointer to the data
  */
void removeCommand(Data *data, Command *cmd) {
  char *courseName = NULL;
  if (cmd->count == 3) { //handles remove csc316
		courseName = strdup(cmd->token[1]);
  } else if (cmd->count == 4) {
		courseName = strdup(cmd->token[1]);
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
	* Two different subroutines. change grade or change hour.
	* Usage: change grade CSE2221 a
	* or change hour CSE2221 4
	*
	* @param data pointer to the data
	* @param cmd command input from the user
	*/
void changeCommand(Data *data, Command *cmd) {
	if (cmd->count != 5) {
		fprintf(stdout, "Invalid command\n");
		return;
	}
	toUpperCase(cmd->token[2]);
	Course *course = findCourse(data, cmd->token[2]);
	if (course == NULL) {
		fprintf(stdout, "Course %s not found\n", cmd->token[2]);
		return;
	}
	// change grade
	if (strcmp(cmd->token[1], "grade") == 0) {
		if (strlen(cmd->token[3]) > 2) {
			fprintf(stdout, "Invalid grade\n");
			return;
		}
		toUpperCase(cmd->token[3]);
		if (isValidGrade(cmd->token[3])) {
			free(course->letterGrade);
			course->letterGrade = strdup(cmd->token[3]);
		} else {
			fprintf(stdout, "Invalid grade\n");
		}
	} else if (strcmp(cmd->token[1], "hour") == 0) { // change hour
		int newHour = atoi(cmd->token[3]);
		int oldHour = course->hours;
		if (newHour == oldHour) {
			fprintf(stdout, "New hour is equal to the old hour (%d)\n", course->hours);
			return;
		}
		course->hours = newHour;
		int difference = abs(newHour - oldHour);
		if (newHour > oldHour) {
			data->totalCredits += difference;
		} else {
			data->totalCredits -= difference;
		}
	} else {
		fprintf(stdout, "Invalid command\n");
	}
}

/**
  * Driver function for this program.
  *
  * @return EXIT_SUCCESS if the program terminates correctly
  */
int main() {
#ifdef unix
	system("clear");
#else
  system("cls");
#endif
  canImport = true;
  printHeader();
  char *command = (char *)malloc(MAX_TOKENS);
  Data *data = initializeData();
  while (1) {
    fprintf(stdout, "cmd> ");
    int matches = fscanf(stdin, "%[^\n]", command);
    fscanf(stdin, "%*c");
    Command *cmd = parseSequence(command);
    if (matches != 1 || cmd->count == 1) {
      continue;
    }
    if (strcmp(cmd->token[0], "calculate") == 0 || strcmp(cmd->token[0], "list") == 0 || strcmp(cmd->token[0], "ls") == 0) {
      listCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "add") == 0) {
      addCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "remove") == 0) {
      removeCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "help") == 0) {
      helpCommand();
    } else if (strcmp(cmd->token[0], "chart") == 0) {
      chartCommand();
    } else if (strcmp(cmd->token[0], "export") == 0) {
      exportCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "import") == 0) {
      importCommand(data, cmd);
    } else if (strcmp(cmd->token[0], "about") == 0) {
      aboutCommand();
    } else if (strcmp(cmd->token[0], "change") == 0) {
			changeCommand(data, cmd);
		} else if (strcmp(cmd->token[0], "quit") == 0 || strcmp(cmd->token[0], "exit") == 0) {
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
  * @param line stdin
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
