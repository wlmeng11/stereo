#ifndef __argument_processing_hpp__
#define __argument_processing_hpp__

#include <iostream>
#include <string.h>
#include "structs.hpp"

using namespace std;

int ReadArgs(struct parameters *pars, int argc, char **argv);
int PrintHelp(struct parameters *pars, int argc, char **argv);
void PrintParams(struct parameters *pars);

#endif
