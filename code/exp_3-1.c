#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

int main() {
    // User inputs
    double Ac, fc, Am, fm, kf;
    printf("Enter Carrier Amplitude (Ac): ");
    scanf("%lf", &Ac);
    printf("Enter Carrier Frequency (fc): ");
    scanf("%lf", &fc);
    printf("Enter Message Amplitude (Am): ");
    scanf("%lf", &Am);
    printf("Enter Message Frequency (fm): ");
    scanf("%lf", &fm);
    printf("Enter Frequency Sensitivity (kf): ");
    scanf("%lf", &kf);

    // Parameters
    double fs = 100 * fc; // Sampling frequency
    int num_samples = 1000; // Number of samples
    double t[num_samples]; // Time vector
    double m_t[num_samples]; // Message signal
    double s_t[num_samples]; // FM signal

    // Generate time vector and signals
    for (int n = 0; n < num_samples; n++) {
        t[n] = n / fs; // Time vector
        m_t[n] = Am * cos(2 * PI * fm * t[n]); // Message signal
        double integral_m_t = (Am / (2 * PI * fm)) * sin(2 * PI * fm * t[n]); // Integral of m(t)
        s_t[n] = Ac * cos(2 * PI * fc * t[n] + 2 * PI * kf * integral_m_t); // FM signal
    }

    // Save data to file
    FILE *file = fopen("fm_signal.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    for (int n = 0; n < num_samples; n++) {
        fprintf(file, "%lf %lf %lf\n", t[n], m_t[n], s_t[n]); // Save time, message, and FM signal
    }
    fclose(file);

    printf("FM signal samples saved to 'fm_signal.txt'.\n");
    return 0;
}