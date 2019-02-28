/**
  * @file print.c
  * @author John Choi
  * @since 02282019
  *
  * Handles simple printing job.
  */

#include "print.h"
#include <stdio.h>
#include <stdlib.h>

void printHeader() {
  fprintf(stdout, "GPA Calculator by John Choi 2019\n");
  fprintf(stdout, "Version 1.1\n");
  fprintf(stdout, "To add a course, \"add [COURSE] [HOURS] [LETTERGRADE]\"\n");
  fprintf(stdout, "Type \"help\" to see the full list of commands\n\n");
}

void helpCommand() {
  fprintf(stdout, "\nUsage:\n");
  fprintf(stdout, "\tlist\n");
  fprintf(stdout, "\tcalculate\n");
  fprintf(stdout, "\tchart\n");
  fprintf(stdout, "\tadd [COURSE] [HOURS] [GRADE]\n");
  fprintf(stdout, "\tremove [COURSE]\n");
  fprintf(stdout, "\tremove all\n");
  fprintf(stdout, "\tquit or exit\n");
}

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
