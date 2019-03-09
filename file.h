/**
  * @file file.h
  * @author John Choi
  * @since 03092019
  *
  * Defines prototypes for functions defined in file.c
  */

#include "data.h"

#ifndef _FILEH_
#define _FILEH_

/**
  * Imports the course listing to the program from the input file.
  *
  * @param data - pointer to the data struct
  * @param filename - file to import from
  */
void import(Data *data, const char *filename);

/**
  * Exports the course listing to the output file.
  *
  * @param data - pointer to the data struct
  * @param filename - file to import from
  */
void export(Data *data, const char *filename);

#endif
