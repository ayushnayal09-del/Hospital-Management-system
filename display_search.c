#include "hospital.h"

/* DISPLAY ALL PATIENTS */

void displayPatients(void) {
    FILE *fp = fopen(FILE_NAME, "rb");
    struct Patient p;
    int count = 0;

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== ALL PATIENT RECORDS =====\n");

    while (fread(&p, sizeof(p), 1, fp) == 1) {

        printf("\nPatient ID: %d\n", p.id);
        printf("Name: %s\n", p.name);
        printf("Age: %d\n", p.age);
        printf("Gender: %s\n", p.gender);
        printf("Doctor: %s\n", p.doctor);
        printf("Hospital days: %d\n", p.days);

        printf("Room charge/day: Rs. %.2f\n",
               p.roomCharge);

        printf("Doctor fee: Rs. %.2f\n",
               p.doctorFee);

        printf("-----------------------------\n");

        count++;
    }

    if (count == 0)
        printf("No patient records found!\n");

    fclose(fp);
}

/* SEARCH PATIENT */

void searchPatient(void) {
    struct Patient p;
    int id;

    printf("\nEnter Patient ID: ");
    id = readInt();

    if (findPatient(id, &p)) {

        printf("\n===== PATIENT FOUND =====\n");

        printf("ID: %d\n", p.id);
        printf("Name: %s\n", p.name);
        printf("Age: %d\n", p.age);
        printf("Gender: %s\n", p.gender);
        printf("Doctor: %s\n", p.doctor);
        printf("Days: %d\n", p.days);

        printf("Room charge/day: %.2f\n",
               p.roomCharge);

        printf("Doctor fee: %.2f\n",
               p.doctorFee);

    } else {
        printf("Patient not found!\n");
    }
}