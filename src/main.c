#include <stdio.h>
#include <stdlib.h>
#include "recursiveFunctions.h"
#include "utils.h"

int N = -1, **relationship;
person_t *people;

int main(int argc, char* argv[]) {
  
  int ret, *offspring, nOffspring;
  ret = loadData("people.txt", &people, &relationship);
  if(!ret)
    return ret;

  printPeople(people);
  printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%d ", relationship[i][j]);
    printf("\n");
  }
  printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");

  nOffspring = getOffspring("Rocco", "Verdi", &offspring);
  if (nOffspring < 0) {
    printf("Person not found\n");
  } else {
    printf("Offspring = %d:\n", nOffspring);
    for (int i = 0; i < nOffspring; i++)
      printf("- %s\n", people[offspring[i]].name);
  }
  printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
  return 0;
}