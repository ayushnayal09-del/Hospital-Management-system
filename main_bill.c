#include "hospital.h"


void generateBill(void) {

    struct Patient p;
    int id;
    float total;

    printf("\nEnter Patient ID: ");
    id = readInt();

    if (!findPatient(id, &p)) {
        printf("Patient not found!\n");
        return;
    }

    total = p.days * p.roomCharge + p.doctorFee;

    printf("\n===== PATIENT BILL =====\n");

    printf("Patient ID: %d\n", p.id);
    printf("Patient Name: %s\n", p.name);
    printf("Doctor: %s\n", p.doctor);

    printf("Room charges: Rs. %.2f\n",
           p.days * p.roomCharge);

    printf("Doctor fee: Rs. %.2f\n",
           p.doctorFee);

    printf("-----------------------------\n");

    printf("Grand Total: Rs. %.2f\n", total);
}

/* MAIN MENU */

int main(void) {

    int choice;

    do {

        printf("\n================================\n");
        printf("   HOSPITAL MANAGEMENT SYSTEM\n");
        printf("================================\n");

        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Update Patient\n");
        printf("5. Delete Patient\n");
        printf("6. Generate Bill\n");
        printf("7. Generate Patient QR Code\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");

        choice = readInt();

        switch (choice) {

            case 1:
                addPatient();
                break;

            case 2:
                displayPatients();
                break;

            case 3:
                searchPatient();
                break;

            case 4:
                modifyPatient(0);
                break;

            case 5:
                modifyPatient(1);
                break;

            case 6:
                generateBill();
                break;

            case 7:
                generatePatientQR();
                break;

            case 0:
                printf("Thank you for using HMS!\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 0);

    return 0;
}