#include <stdio.h>
#include <math.h>
#include <complex.h>
#include <stdlib.h>

#define neta 1
#define g_m 15
#define L 0.01
#define a 1.0274
#define b 1.5
#define E_c 1
#define PI 3.1415926535897
#define SAMPLES 20000

// Function to compute the transfer function
void computeTransferFunction() {
    FILE *fptr = fopen("TF.txt", "w");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }

    double T_1, T_2, T_3, T_4;
    double TF_real, TF_img;
    double x, f_m = 1.5, f_c = 45, f_s = 4500, W_c, Q_e;

    Q_e = 1 / (2 * 0.66 * f_c * f_m);
    W_c = 2 * PI * f_c;
    T_1 = neta * g_m * W_c * L * Q_e;

    for (int i = 1; i <= SAMPLES; i++) {
        x = ((i * f_s) / SAMPLES - f_c) / f_c;

        T_2 = pow((1 + pow((x + a), 2)), 0.5);
        T_3 = (1 - pow((x + a), 2));
        T_4 = (1 + pow(b, 2) - pow(x, 2)) + 4 * pow(x, 4);

        if (T_3 >= 0) {
            TF_real = (T_1 * (T_2 - pow(T_3, 0.5))) / T_4;
            TF_img = 0;
        } else {
            TF_real = (T_1 * T_2) / T_4;
            TF_img = (-T_1 * pow(-T_3, 0.5)) / T_4;
        }

        fprintf(fptr, "%d %lf %lf\n", i, TF_real, TF_img);
    }

    fclose(fptr);
}

// Function to generate FM signal
void generateFMSignal(double *fm_signal, double *message_signal) {
    double fc = 15;   // Carrier frequency
    double fs = fc * 100; // Sampling frequency
    double fm = 1.5;  // Message frequency
    double Am = 1;    // Message amplitude
    double Ac = 1;    // Carrier amplitude
    double kf = 5;    // Frequency sensitivity

    for (int i = 0; i < SAMPLES; i++) {
        double t = (double)i / fs;
        message_signal[i] = Am * cos(2 * PI * fm * t);  // Message signal
        fm_signal[i] = Ac * cos(2 * PI * fc * t + 2 * PI * kf * message_signal[i] * t);  // FM signal
    }
}

// Function to compute DFT
void computeDFT(double *signal, double complex *dft) {
    for (int k = 0; k < SAMPLES; k++) {
        dft[k] = 0;
        for (int n = 0; n < SAMPLES; n++) {
            double angle = -2 * PI * k * n / SAMPLES;
            dft[k] += signal[n] * (cos(angle) + I * sin(angle));
        }
    }
}

// Function to compute IDFT
void computeIDFT(double complex *dft, double *signal) {
    for (int n = 0; n < SAMPLES; n++) {
        signal[n] = 0;
        for (int k = 0; k < SAMPLES; k++) {
            double angle = 2 * PI * k * n / SAMPLES;
            signal[n] += creal(dft[k] * (cos(angle) + I * sin(angle)));
        }
        signal[n] /= SAMPLES;
    }
}

// Function to implement envelope detector
void envelopeDetector(double *signal, double *envelope) {
    for (int i = 0; i < SAMPLES; i++) {
        envelope[i] = sqrt(pow(signal[i], 2) + pow(signal[(i + 1) % SAMPLES], 2));
    }
}

int main() {
    // Step 1: Compute Transfer Function
    computeTransferFunction();

    // Step 2: Generate FM Signal
    double fm_signal[SAMPLES];
    double message_signal[SAMPLES];
    generateFMSignal(fm_signal, message_signal);

    // Step 3: Compute DFT of FM Signal
    double complex dft[SAMPLES];
    computeDFT(fm_signal, dft);

    // Step 4: Multiply DFT with Transfer Function
    FILE *tf_file = fopen("TF.txt", "r");
    double complex tf[SAMPLES];
    for (int i = 0; i < SAMPLES; i++) {
        int index;
        double real, imag;
        fscanf(tf_file, "%d %lf %lf", &index, &real, &imag);
        tf[i] = real + I * imag;
    }
    fclose(tf_file);

    for (int i = 0; i < SAMPLES; i++) {
        dft[i] *= tf[i];
    }

    // Step 5: Compute IDFT of the Product
    double idft_output[SAMPLES];
    computeIDFT(dft, idft_output);

    // Step 6: Implement Envelope Detector
    double envelope[SAMPLES];
    envelopeDetector(idft_output, envelope);

    // Save Results for MATLAB Plots
    FILE *fm_file = fopen("fm_signal.txt", "w");
    FILE *idft_file = fopen("idft_output.txt", "w");
    FILE *envelope_file = fopen("envelope.txt", "w");
    FILE *message_file = fopen("message_signal.txt", "w");

    for (int i = 0; i < SAMPLES; i++) {
        fprintf(fm_file, "%lf\n", fm_signal[i]);
        fprintf(idft_file, "%lf\n", idft_output[i]);
        fprintf(envelope_file, "%lf\n", envelope[i]);
        fprintf(message_file, "%lf\n", message_signal[i]);
    }

    fclose(fm_file);
    fclose(idft_file);
    fclose(envelope_file);
    fclose(message_file);

    return 0;
}