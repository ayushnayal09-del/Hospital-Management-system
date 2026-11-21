#include "hospital.h"
#include <string.h>

/* INPUT FUNCTIONS */

int readInt(void) {
    char line[100], extra;
    int n;

    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, " %d %c", &n, &extra) == 1)
            return n;

        printf("Enter a valid integer: ");
    }
    return 0;
}

float readFloat(void) {
    char line[100], extra;
    float n;

    while (fgets(line, sizeof(line), stdin)) {
        if (sscanf(line, " %f %c", &n, &extra) == 1)
            return n;

        printf("Enter a valid number: ");
    }
    return 0;
}

void readString(char s[], int size) {
    if (fgets(s, size, stdin)) {
        size_t len = strlen(s);

        if (len > 0 && s[len - 1] == '\n')
            s[len - 1] = '\0';
    } else {
        s[0] = '\0';
    }
}

/* FIND PATIENT */

int findPatient(int id, struct Patient *p) {
    FILE *fp = fopen(FILE_NAME, "rb");

    if (!fp)
        return 0;

    while (fread(p, sizeof(*p), 1, fp) == 1) {
        if (p->id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

/* ADD PATIENT */

void addPatient(void) {
    struct Patient p, temp;
    FILE *fp;

    printf("\n===== PATIENT REGISTRATION =====\n");

    printf("Patient ID: ");
    p.id = readInt();

    if (p.id <= 0 || findPatient(p.id, &temp)) {
        printf("Invalid or duplicate ID!\n");
        return;
    }

    printf("Name: ");
    readString(p.name, sizeof(p.name));

    if (!p.name[0]) {
        printf("Name cannot be empty!\n");
        return;
    }

    printf("Age: ");
    p.age = readInt();

    printf("Gender: ");
    readString(p.gender, sizeof(p.gender));

    printf("Doctor: ");
    readString(p.doctor, sizeof(p.doctor));

    printf("Hospital days: ");
    p.days = readInt();

    printf("Room charge per day: ");
    p.roomCharge = readFloat();

    printf("Doctor fee: ");
    p.doctorFee = readFloat();

    if (p.age < 0 || p.days < 0 ||
        p.roomCharge < 0 || p.doctorFee < 0) {
        printf("Values cannot be negative!\n");
        return;
    }

    fp = fopen(FILE_NAME, "ab");

    if (!fp) {
        printf("File error!\n");
        return;
    }

    if (fwrite(&p, sizeof(p), 1, fp) == 1)
        printf("Patient added successfully!\n");
    else
        printf("Error saving patient!\n");

    fclose(fp);
}