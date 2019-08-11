/**
  * @file print.c
  * @author John Choi
  * @since 08112019
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
  fprintf(stdout, "\tFile name can be specified for import and export commands.\n");
  fprintf(stdout, "\tAdded support for S/U grades.\n");

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
  fprintf(stdout, "\tadd [COURSE] [HOURS] [GRADE]\n");
  fprintf(stdout, "\tremove [COURSE]\n");
  fprintf(stdout, "\tremove all\n");
  fprintf(stdout, "\tchange grade [COURSE] [NEW GRADE]\n"); // added in 2.0
  fprintf(stdout, "\tchange hour [COURSE] [NEW HOUR]\n"); // added in 2.0
  fprintf(stdout, "\tlist\n");
  fprintf(stdout, "\tcalculate\n");
  fprintf(stdout, "\tchart\n");
  fprintf(stdout, "\timport\n"); // added in version 2.0
  fprintf(stdout, "\texport\n"); // added in version 1.2
  fprintf(stdout, "\tabout\n");
  fprintf(stdout, "\tquit or exit\n");
}

void chartCommand() {
  fprintf(stdout, "\n\n");
  fprintf(stdout, "%10s|%10s\n", "Grade  ", "Value");
  fprintf(stdout, "---------------------\n");
  fprintf(stdout, "---------------------\n");
  fprintf(stdout, "%10s|%10s\n", "A+  ", "4.3");
  fprintf(stdout, "%10s|%10s\n", "A   ", "4.0");
  fprintf(stdout, "%10s|%10s\n", "A-  ", "3.7");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "B+  ", "3.3");
  fprintf(stdout, "%10s|%10s\n", "B   ", "3.0");
  fprintf(stdout, "%10s|%10s\n", "B-  ", "2.6");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "C+  ", "2.3");
  fprintf(stdout, "%10s|%10s\n", "C   ", "2.0");
  fprintf(stdout, "%10s|%10s\n", "C-  ", "1.7");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "D+  ", "1.3");
  fprintf(stdout, "%10s|%10s\n", "D   ", "1.0");
  fprintf(stdout, "%10s|%10s\n", "D-  ", "0.7");

  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "%10s|%10s\n", "F   ", "0.0");
  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "S/U grades do not affect the GPA\n");
  fprintf(stdout, "---------------------\n");
  fprintf(stdout, "---------------------\n");

  fprintf(stdout, "GPA scale based on The Ohio State University\n");
  fprintf(stdout, "---------------------\n");
}
