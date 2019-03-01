#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "recursiveFunctions.h"

extern int N;
extern person_t *people;
extern int **relationship;

static void _getOffspring(int id, int *count, int *ids) {
  for (int j = 0; j < N; j++) {
    if (relationship[id][j] == 1) {
      ids[*count] = j;
      *count += 1;
      _getOffspring(j, count, ids);
    }
  }
}

int getOffspring(char *name, char *surname, int **offspringIds) {
  int id, count = 0;
  int ids[N];
  id = searchPersonByName(people, 0, N - 1, name, surname);
  if (id < 0)
    return id;

  _getOffspring(id, &count, ids);
  *offspringIds = (int*) malloc(count * sizeof(int));
  memcpy((void*)*offspringIds, (const void*)ids, count * sizeof(int));
  return count;
}

static int _computeLongestChain(int id, int count, int *result, int* ids, int* maxIds) {
  int offspringCount, ret, nextIds[N];
  ids[count] = id;
  // if is a leaf into tree structure
  maxIds[count] = id;
  count += 1;
  for (int j = 0; j < N; j++) {
    if (relationship[id][j] == 1) {
      (people[j].sex != people[id].sex) ? (offspringCount = 0) : (offspringCount = count); 
      ret = _computeLongestChain(j, offspringCount, result, (offspringCount) ? ids : nextIds, maxIds);
      if (ret > *result) {
        *result = ret;
        if (offspringCount)
          memcpy((void*)maxIds, (const void*)ids, ret * sizeof(int));
        else
          memcpy((void*)maxIds, (const void*)nextIds, ret * sizeof(int));
      }
    }
  }
  return count;
}

int longestOffspringChainSameSex(int** offspringIds) {
  int bestLen = 0, ret, ids[N], bestIds[N];
  for(int i = 0; i < N; i++) {
    if (people[i].root)
      ret = _computeLongestChain(i, 0, &bestLen, ids, bestIds);
      if (ret > bestLen) {
        bestLen = ret;
        memcpy((void*)bestIds, (const void*)ids, ret * sizeof(int));
      }
  }
  // create array containin id of longest same sex chain
  *offspringIds = (int*) malloc(bestLen * sizeof(int));
  memcpy((void*)*offspringIds, (const void*)bestIds, bestLen * sizeof(int));
  return bestLen;
}

static int _computeChainAge(int id, int age, int *result, int *count, int *ids, int *resultIds) {
  int ret;
  age += people[id].age;
  ids[*count] = id;
  *count += 1;
  for (int j = 0; j < N; j++) {
    if (relationship[id][j] == 1) {
      ret = _computeChainAge(j, age, result, count, ids, resultIds);
      if (ret > *result) {
        *result = ret;
        memcpy((void*)resultIds, (const void*)ids, (*count - 1) * sizeof(int));
      }
    }
  }
  return age;
}

int getOldestOffsringChain(int **oldestChain, int *chainLen) {
  int computedAge = 0, maxAge = 0, ids[N], resultIds[N], tmp[N], oldestChainIds[N], count;
  for(int i = 0; i < N; i++) {
    if (people[i].root) {
      count = 0;
      computedAge = 0;
      _computeChainAge(i, 0, &computedAge, &count, ids, resultIds);
      //printf(" --- returned age %d\n", computedAge);
      if (computedAge > maxAge) {
        maxAge = computedAge;
        memcpy((void*)tmp, (const void*)resultIds, (count - 1 )* sizeof(int));
        *chainLen = count;
      }
    }
  }
  // create array containin id of longest same sex chain
  *oldestChain = (int*) malloc(*chainLen * sizeof(int));
  memcpy((void*)*oldestChain, (const void*)tmp, *chainLen * sizeof(int));
  return maxAge;
}
