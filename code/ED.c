#include <stdio.h>
#include <math.h>

void envelopeDetector(double *signal, double *envelope, int N) {
    for (int i = 0; i < N; i++) {
        envelope[i] = fabs(signal[i]); // Simple absolute value for envelope detection
    }
}

int main() {
    int N = 20000; // Number of samples
    double IDFT_output[N];
    double envelope[N];

    // Load IDFT output from file
    FILE *idft_file = fopen("IDFT_output.txt", "r");
    if (!idft_file) {
        printf("Error opening IDFT_output.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        int index;
        fscanf(idft_file, "%d %lf", &index, &IDFT_output[i]);
    }
    fclose(idft_file);

    // Compute Envelope Detector output
    envelopeDetector(IDFT_output, envelope, N);

    // Save Envelope Detector output to file
    FILE *env_file = fopen("Envelope_output.txt", "w");
    if (!env_file) {
        printf("Error opening Envelope_output.txt\n");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        fprintf(env_file, "%d %lf\n", i, envelope[i]);
    }
    fclose(env_file);

    return 0;
}