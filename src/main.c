#include <stdio.h>
#include <stdlib.h>
#include "recursiveFunctions.h"
#include "utils.h"

int N = -1, **relationship;
person_t *people;

int main(int argc, char* argv[]) {
  
  int ret, *offspring, nOffspring, sameSexChainLen, *sameSexIds, age, *oldestChain, chainLen;
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
  sameSexChainLen = longestOffspringChainSameSex(&sameSexIds);
  printf("Longest chain of %d\n", sameSexChainLen);
  for (int i = 0; i < sameSexChainLen; i++)
    printf("--> %s\n", people[sameSexIds[i]].name);
  printf("+++++++++++++++++++++++++++++++++++++++++++++++\n");
  age = getOldestOffsringChain(&oldestChain, &chainLen);
  printf("Maximum age of offspring: %d\n", age);
  for (int i = 0; i < chainLen; i++)
    printf("--> %s\n", people[oldestChain[i]].name);
  return 0;
}