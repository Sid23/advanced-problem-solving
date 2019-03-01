#ifndef RECURSIVE_FUNCTIONS
#define RECURSIVE_FUNCTIONS

#include "utils.h"

int getOffspring(char *name, char *surname, int** offspringIds);
int longestOffspringChainSameSex(int** offspringIds);
int getOldestOffsringChain(int **oldestChain, int *chainLen);

#endif