#include "hospital.h"

/* UPDATE AND DELETE PATIENT */

void modifyPatient(int deleting) {

    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp;

    struct Patient p;

    int id, found = 0, invalid = 0;

    if (!fp) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Patient ID: ");
    id = readInt();

    temp = fopen(TEMP_FILE, "wb");

    if (!temp) {
        fclose(fp);
        printf("File error!\n");
        return;
    }

    while (fread(&p, sizeof(p), 1, fp) == 1) {

        if (p.id == id) {

            found = 1;

            if (deleting)
                continue;

            printf("New name: ");
            readString(p.name, sizeof(p.name));

            printf("New age: ");
            p.age = readInt();

            printf("New gender: ");
            readString(p.gender, sizeof(p.gender));

            printf("New doctor: ");
            readString(p.doctor, sizeof(p.doctor));

            printf("New days: ");
            p.days = readInt();

            printf("New room charge/day: ");
            p.roomCharge = readFloat();

            printf("New doctor fee: ");
            p.doctorFee = readFloat();

            if (!p.name[0] || p.age < 0 ||
                p.days < 0 || p.roomCharge < 0 ||
                p.doctorFee < 0) {

                printf("Invalid details!\n");
                invalid = 1;
                break;
            }
        }

        if (fwrite(&p, sizeof(p), 1, temp) != 1) {
            printf("File writing error!\n");
            invalid = 1;
            break;
        }
    }

    fclose(fp);
    fclose(temp);

    if (invalid) {
        remove(TEMP_FILE);
        return;
    }

    if (!found) {
        remove(TEMP_FILE);
        printf("Patient not found!\n");
        return;
    }

    if (remove(FILE_NAME) != 0) {
        printf("Error replacing original file!\n");
        remove(TEMP_FILE);
        return;
    }

    if (rename(TEMP_FILE, FILE_NAME) != 0) {
        printf("Error renaming temporary file!\n");
        return;
    }

    if (deleting)
        printf("Patient deleted successfully!\n");
    else
        printf("Patient updated successfully!\n");
}