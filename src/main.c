#include <stdio.h>
#include <stdlib.h>
#include "recursiveFunctions.h"
#include "utils.h"

int N = -1;

int main(int argc, char* argv[]) {
  person_t *people;
  int **relationship, ret;

  ret = loadData("people.txt", &people, &relationship);
  if(!ret)
    return ret;

  printf("%s\n", people[5].surname);
  printf("%d\n", N);
  printPeople(people);
  int id = searchPersonByName(people, 0, N - 1, "Luigi", "Verdi");
  if (id < 0)
    printf("-----------------------\nPerson not found\n");
  else
    printf("-----------------------\nId = %d\n", id);

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      printf("%d ", relationship[i][j]);
    printf("\n");
  }
  return 0;
}