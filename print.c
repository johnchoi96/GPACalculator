/**
  * @file print.c
  * @author John Choi
  * @since 03092019
  *
  * Handles simple printing job.
  */

#include "print.h"
#include <stdio.h>
#include <stdlib.h>

#define VERSION "2.0"

void aboutCommand() {
  fprintf(stdout, "Website: johnchoi96.github.io\n");

  fprintf(stdout, "Changes in version %s:\n", VERSION);
  fprintf(stdout, "\tImproved runtime efficiency by replacing linear search\n");
  fprintf(stdout, "\talgorithm (O(n)) with binary search algorithm (O(log n)).\n");
  fprintf(stdout, "\tAdded import and export functions to easily restore courses.\n");

  fprintf(stdout, "\n");
}

void printHeader() {
  fprintf(stdout, "GPA Calculator by John Choi 2019\n");
  fprintf(stdout, "Version %s\n", VERSION);
  fprintf(stdout, "To add a course, \"add [COURSE] [HOURS] [LETTERGRADE]\"\n");
  fprintf(stdout, "Type \"help\" to see the full list of commands\n\n");
}

void helpCommand() {
  fprintf(stdout, "\nUsage:\n");
  fprintf(stdout, "\tlist\n");
  fprintf(stdout, "\tcalculate\n");
  fprintf(stdout, "\tchart\n");
  fprintf(stdout, "\texport\n"); // added in version 1.2
  fprintf(stdout, "\timport\n"); // added in version 1.2
  fprintf(stdout, "\tadd [COURSE] [HOURS] [GRADE]\n");
  fprintf(stdout, "\tremove [COURSE]\n");
  fprintf(stdout, "\tremove all\n");
  fprintf(stdout, "\tabout\n");
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
