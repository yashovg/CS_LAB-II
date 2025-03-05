#include <stdio.h>
#include <math.h>
#include <complex.h>

#define PI 3.14159265358979323846
#define NUM_SAMPLES 1000

// Function to compute DFT
void dft(double complex *x, double complex *X, int N) {
    for (int k = 0; k < N; k++) {
        X[k] = 0;
        for (int n = 0; n < N; n++) {
            X[k] += x[n] * cexp(-I * 2 * PI * k * n / N);
        }
    }
}

// Function to compute IDFT
void idft(double complex *X, double complex *x, int N) {
    for (int n = 0; n < N; n++) {
        x[n] = 0;
        for (int k = 0; k < N; k++) {
            x[n] += X[k] * cexp(I * 2 * PI * k * n / N);
        }
        x[n] /= N;
    }
}

int main() {
    // Load FM signal from file
    double t[NUM_SAMPLES], m_t[NUM_SAMPLES], s_t[NUM_SAMPLES];
    FILE *file = fopen("fm_signal.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    for (int n = 0; n < NUM_SAMPLES; n++) {
        fscanf(file, "%lf %lf %lf", &t[n], &m_t[n], &s_t[n]);
    }
    fclose(file);

    // Split FM signal into odd and even sequences
    int odd_size = (NUM_SAMPLES + 1) / 2;
    int even_size = NUM_SAMPLES / 2;
    double complex s_odd[odd_size], s_even[even_size];
    for (int i = 0; i < odd_size; i++) {
        s_odd[i] = s_t[2 * i];
    }
    for (int i = 0; i < even_size; i++) {
        s_even[i] = s_t[2 * i + 1];
    }

    // Compute DFT of odd and even sequences
    double complex X_odd[odd_size], X_even[even_size];
    dft(s_odd, X_odd, odd_size);
    dft(s_even, X_even, even_size);

    // Add DFTs (pad with zeros if necessary)
    int max_size = (odd_size > even_size) ? odd_size : even_size;
    double complex X_final[max_size];
    for (int k = 0; k < max_size; k++) {
        X_final[k] = (k < odd_size ? X_odd[k] : 0) + (k < even_size ? X_even[k] : 0);
    }

    // Compute IDFT of X_final
    double complex s_reconstructed[max_size];
    idft(X_final, s_reconstructed, max_size);

    // Save reconstructed signal to file
    file = fopen("reconstructed_signal.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    for (int n = 0; n < max_size; n++) {
        fprintf(file, "%lf %lf\n", t[n], creal(s_reconstructed[n])); // Save time and reconstructed signal
    }
    fclose(file);

    printf("Reconstructed signal saved to 'reconstructed_signal.txt'.\n");
    return 0;
}