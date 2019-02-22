#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

extern int N;

int loadData(const char* filename, person_t **people, int **relationship[]) {
  FILE *fp = fopen(filename, "r");
  if (fp == NULL)
    return -1;
  
  char line[512], s, nameF[50], surnameF[50], nameM[50], surnameM[50], name[50], surname[50]; /* or other suitable maximum line size */
  int i, j, id, idF, idM;

  fgets(line, sizeof(line), fp);
  sscanf(line, "%d", &N);
  *people = (person_t*) malloc(N * sizeof(person_t));

  (*relationship) = (int**) malloc(N * sizeof(int*));
  for (i = 0; i < N; i++)
    (*relationship)[i] = (int*) malloc(N * sizeof(int)); 
  for (i = 0; i < N; i++)
    for (j = 0; j < N; j++)
      (*relationship)[i][j] = 0;

  for (i = 0; i < N; i++) {
    fgets(line, sizeof(line), fp);
    sscanf(line, "%s %s %c %d", (*people)[i].name, (*people)[i].surname, &s, &((*people)[i].age));
    (s == 'M') ? ((*people)[i].sex = M) : ((*people)[i].sex = F);
    (*people)[i].root = 1;
  }

  // load relatioship
  sortPeopleByName(*people, 0, N - 1);
  while (fgets(line, sizeof(line), fp) != NULL) {
    sscanf(line, "%s %s %s %s %s %s", name, surname, nameF, surnameF, nameM, surnameM);
    id = searchPersonByName(*people, 0, N - 1, name, surname);
    idF = searchPersonByName(*people, 0, N - 1, nameF, surnameF);
    idM = searchPersonByName(*people, 0, N - 1, nameM, surnameM);
    if (id < 0 || idM < 0 || idF < 0)
      continue;

    //printf("%s(%d) | P %s(%d) M %s(%d)\n", (*people)[id].name, id, (*people)[idF].name, idF, (*people)[idM].name, idM); 
    (*relationship)[idF][id] = 1;
    (*relationship)[idM][id] = 1;
    (*people)[id].root = 0;
  }
  fclose(fp);
  return 1;
}

static void swap(person_t *p1, person_t *p2) {
  person_t tmp = *p1;
  *p1 = *p2;
  *p2 = tmp;
}

static int partition(person_t *people, int low, int high) {
  person_t pivot = people[high];    // pivot 
  int i = (low - 1);
  
  for (int j = low; j < high; j++) { 
      // If current element is smaller than or equal to pivot 
      if (strcmp(people[j].surname, pivot.surname) < 0 || 
        (strcmp(people[j].surname, pivot.surname) == 0 && strcmp(people[j].name, pivot.name) < 0)) { 
          i++; // increment index of smaller element
          swap(&people[i], &people[j]);
      } 
  }
  // swap the pivot
  swap(&people[i + 1], &people[high]);
  return (i + 1); 
}

void sortPeopleByName(person_t *people, int low, int high) {
  if (low >= high)
    return;
  
  int pi = partition(people, low, high);
  sortPeopleByName(people, low, pi - 1);  // Before pi
  sortPeopleByName(people, pi + 1, high); // After pi
}

int searchPersonByName(person_t *people, int low, int high, char name[50], char surname[50]) {
  if (low > high) {
    return -1;
  }

  int m = (low + high) / 2;
  if (strcmp(people[m].name, name) == 0 && strcmp(people[m].surname, surname) == 0)
    return m;

  if (strcmp(surname, people[m].surname) < 0 || 
    (strcmp(surname, people[m].surname) == 0 && strcmp(name, people[m].name) < 0)) 
      return searchPersonByName(people, low, m - 1, name, surname);

  return searchPersonByName(people, m + 1, high, name, surname);
}

void printPeople(person_t *people) {
  for (int i = 0; i < N; i++)
    printf("%s | %s | %d | %d\n", people[i].name, people[i].surname, people[i].sex, people[i].age);
}