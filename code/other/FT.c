#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.1415926535897

// Function to compute DFT
void computeDFT(double *signal, double complex *dft, int N) {
    for (int k = 0; k < N; k++) {
        dft[k] = 0;
        for (int n = 0; n < N; n++) {
            double angle = -2 * PI * k * n / N;
            dft[k] += signal[n] * (cos(angle) + I * sin(angle));
        }
    }
}

// Function to compute IDFT
void computeIDFT(double complex *dft, double *signal, int N) {
    for (int n = 0; n < N; n++) {
        signal[n] = 0;
        for (int k = 0; k < N; k++) {
            double angle = 2 * PI * k * n / N;
            signal[n] += creal(dft[k] * (cos(angle) + I * sin(angle))) / N;
        }
    }
}

int main() {
    int N = 20000; // Number of samples
    double FM_signal[N];
    double complex DFT[N];
    double complex Y[N];
    double IDFT_output[N];

    // Load FM signal from file
    FILE *fm_file = fopen("FM_signal.txt", "r");
    if (!fm_file) {
        printf("Error opening FM_signal.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        int index;
        fscanf(fm_file, "%d %lf", &index, &FM_signal[i]);
    }
    fclose(fm_file);

    // Compute DFT of FM signal
    computeDFT(FM_signal, DFT, N);

    // Save DFT to file
    FILE *dft_file = fopen("DFT_output.txt", "w");
    if (!dft_file) {
        printf("Error opening DFT_output.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        fprintf(dft_file, "%d %lf %lf\n", i, creal(DFT[i]), cimag(DFT[i]));
    }
    fclose(dft_file);

    // Load Transfer Function from file
    double complex TF[N];
    FILE *tf_file = fopen("TF.txt", "r");
    if (!tf_file) {
        printf("Error opening TF.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        int index;
        double real, imag;
        fscanf(tf_file, "%d %lf %lf", &index, &real, &imag);
        TF[i] = real + I * imag;
    }
    fclose(tf_file);

    // Multiply DFT with Transfer Function
    for (int i = 0; i < N; i++) {
        Y[i] = DFT[i] * TF[i];
    }

    // Compute IDFT of the product
    computeIDFT(Y, IDFT_output, N);

    // Save IDFT output to file
    FILE *idft_file = fopen("IDFT_output.txt", "w");
    if (!idft_file) {
        printf("Error opening IDFT_output.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        fprintf(idft_file, "%d %lf\n", i, IDFT_output[i]);
    }
    fclose(idft_file);

    return 0;
}