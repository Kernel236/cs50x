#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient{
    char name[50];
    char disease[50];
    int age;
    int h_day;
};

int main(void) 
{
    struct Patient patient0;
    patient0.age = 77;
    patient0.h_day = 144;
    strcpy( patient0.disease, "TEP");
    strcpy( patient0.name, "Jhon Doe");

    printf("Covid Patient 0 was %s, who survived at the age of %i after %i days of hospitalization and a %s!!\n",
            patient0.name, patient0.age, patient0.h_day, patient0.disease);

    return 0;
}