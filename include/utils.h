#ifndef UTILS_H
#define UTILS_H

enum sex_t {M, F}; 
typedef struct person {
   char name[50];
   char surname[50];
   enum sex_t sex;
   int age;
   int root;
} person_t;

extern int N;

int loadData(const char* filename, person_t **people, int **relationship[]);
void sortPeopleByName(person_t *people, int low, int high);
int searchPersonByName(person_t *people, int low, int high, char name[50], char surname[50]);
void printPeople(person_t *people);

#endif