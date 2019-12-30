/**
  * @file file.c
  * @author John Choi
  * @version 05082019
  *
  * Handles import and export commands.
  */

#include "data.h"
#include "calculate.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int creditOnlyHours;

/**
  * Encrypts line by adding 4 to the ascii code of each character.
  *
  * @param line - single line to encrypt
  */
void lineEncrypt(char *line) {
  for (int i = 0; i < strlen(line); i++) {
    line[i] += 4;
  }
}

/**
  * Decrypts line by subtracting 4 from the ascii code of each character.
  *
  * @param line - single line to decrypt
  */
void lineDecrypt(char *line) {
  for (int i = 0; i < strlen(line); i++) {
    line[i] -= 4;
  }
}

bool import(Data *data, const char *filename) {
  creditOnlyHours = 0;
  FILE *fp = fopen(filename, "r");
  if (!fp) {
    fprintf(stdout, "Cannot open file <%s>\n\n", filename);
    return false;
  }
  char *courseName = (char *)malloc(20);
  int creditHour;
  char *letterGrade = (char *)malloc(20);
  char *line = (char *)malloc(50);
  while (fscanf(fp, "%[^\n]\n", line) != EOF) {
    lineDecrypt(line);
    sscanf(line, "%s %d %s", courseName, &creditHour, letterGrade);
    if (strcmp(letterGrade, "S") == 0 || strcmp(letterGrade, "U") == 0) {
      creditOnlyHours += creditHour;
    }
    addCourse(data, courseName, creditHour, letterGrade);
  }
  free(line);
  free(courseName);
  free(letterGrade);
  fclose(fp);
  return true;
}

void export(Data *data, const char *filename) {
  FILE *fp = fopen(filename, "w");
  char *line = (char *)malloc(50);
  strcpy(line, "");
  char *credits = (char *)malloc(10);
  for (int i = 0; i < data->size; i++) {
    // make a line
    strcat(line, data->courseList[i].name);
    strcat(line, " ");
    sprintf(credits, "%d", data->courseList[i].hours);
    strcat(line, credits);
    strcat(line, " ");
    strcat(line, data->courseList[i].letterGrade);

    lineEncrypt(line); // encrypt line
    fprintf(fp, "%s\n", line);
    strcpy(line, "");
  }
  free(credits);
  free(line);
  fclose(fp);
}
