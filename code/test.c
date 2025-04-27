#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


void generate_inter_arrival_times(double intr_arrival_time[], int N, double arrive_rate) {
        double pkts_time = 0;

    // Seed the random number generator
    srand(time(NULL));

    for (int i = 0; i < N; i++) {
        // Generate a random value for P in the range (0, 1]
        double P = (double)rand() / RAND_MAX;
        if (P == 0.0) {
            P = 1.0; // Ensure P is not zero to avoid log(0)
        }

        // Calculate inter-arrival time using the provided formula
        intr_arrival_time[i] = (-1.0 / arrive_rate) * log(P / arrive_rate);
        printf("%lf\t", intr_arrival_time[i]);
        pkts_time = pkts_time + intr_arrival_time[i];
    }s

    printf("\nTotal packets time: %lf\n", pkts_time);
}

int main() {
    int N = 10;
    double intr_arrival_time[100]; // Array to store inter-arrival times
    double uf = 1.5;            // Utilization factor
    double depart_rate = 10.0;  // Departure rate
    double arrive_rate = uf * depart_rate; // Arrival rate

    // Generate inter-arrival times
    generate_inter_arrival_times(intr_arrival_time, N, arrive_rate);

    return 0;
}