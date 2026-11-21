#ifndef HOSPITAL_H
#define HOSPITAL_H

#include <stdio.h>

#define FILE_NAME "patients.dat"
#define TEMP_FILE "temp.dat"

struct Patient {
    int id, age, days;
    char name[50], gender[15], doctor[50];
    float roomCharge, doctorFee;
};

int readInt(void);
float readFloat(void);
void readString(char s[], int size);
int findPatient(int id, struct Patient *p);

void addPatient(void);
void displayPatients(void);
void searchPatient(void);
void modifyPatient(int deleting);
void generateBill(void);
void generatePatientQR(void);

#endif