
#include "hospital.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Convert patient information into URL-safe text */
void urlEncode(const char *input, char *output) {
    const char *hex = "0123456789ABCDEF";
    int j = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        unsigned char c = (unsigned char)input[i];

        if ((c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') ||
            c == '-' || c == '_' || c == '.' || c == '~') {
            output[j++] = c;
        } else {
            output[j++] = '%';
            output[j++] = hex[c >> 4];
            output[j++] = hex[c & 15];
        }
    }

    output[j] = '\0';
}

/* Generate patient QR code */
void generatePatientQR(void) {

    struct Patient p;
    int id;

    char data[200];
    char encoded[600];
    char filename[100];

    FILE *fp;

    printf("\n===== PATIENT QR GENERATOR =====\n");

    printf("Enter Patient ID: ");
    id = readInt();

    if (!findPatient(id, &p)) {
        printf("Patient not found!\n");
        return;
    }

    /* Patient information */
    snprintf(data, sizeof(data),
        "HOSPITAL MANAGEMENT SYSTEM\n"
        "Patient ID: %d\n"
        "Patient Name: %s",
        p.id, p.name
    );

    /* Encode information for URL */
    urlEncode(data, encoded);

    /* Create HTML file */
    snprintf(filename, sizeof(filename),
        "Patient_%d_QR.html", p.id);

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Unable to create QR file!\n");
        return;
    }

    fprintf(fp,
        "<html><head><title>Patient QR Code</title></head>"
        "<body style='text-align:center;font-family:Arial;'>"
        "<h2>Hospital Management System</h2>"
        "<h3>Patient: %s</h3>"
        "<h3>Patient ID: %d</h3>"
        "<img width='250' height='250' "
        "src='https://api.qrserver.com/v1/create-qr-code/"
        "?size=250x250&data=%s'>"
        "<p>Scan this QR code for patient information.</p>"
        "</body></html>",
        p.name, p.id, encoded
    );

    fclose(fp);

    printf("\nQR Code page created successfully!\n");
    printf("Patient Name: %s\n", p.name);
    printf("Patient ID: %d\n", p.id);
    printf("File: %s\n", filename);

    /* Open HTML page in default browser */
    {
        char command[150];

        snprintf(command, sizeof(command),
            "start \"\" \"%s\"", filename);

        system(command);
    }
}
