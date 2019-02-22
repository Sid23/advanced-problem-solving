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

