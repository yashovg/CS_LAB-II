#include <stdio.h>
#include <math.h>
#include<complex.h>

#define PI 3.1415926535897

int main() {
    FILE *fptr;
    fptr = fopen("FM_signal.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    double fc = 45;   // Carrier frequency
    double fs = fc*100; // Sampling frequency
    double fm = 1.5;  // Message frequency
    double Am = 1;    // Message amplitude
    double Ac = 1;    // Carrier amplitude
    double kf = 5;    // Frequency sensitivity
    int Length = 20000;

    for (int i = 0; i < Length; i++) {
        double t = i / fs;
        double m = Am * cos(2 * PI * fm * t); // Message signal
        double s = Ac * cos(2 * PI * fc * t + 2 * PI * kf * m * t); // FM signal
        fprintf(fptr, "%d %lf\n", i, s);
    }

    fclose(fptr);
    printf("The file has been created successfully");
    return 0;
}