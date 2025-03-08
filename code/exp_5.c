#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

#define depart_rate 1

double* expRV_arrive(int N, int arrive_rate){
	static double intr_arrival_time[1000];

	srand(time(NULL));
	
	for(int i=0; i<N; i++){
		double P = (double)rand() / RAND_MAX;
        if (P == 0.0) {
            P = 1.0; 
        }
        intr_arrival_time[i] = (-1.0 / arrive_rate) * log(P / arrive_rate);
	}
	
	return intr_arrival_time;
}

double* expRV_depart(int N){
	static double intr_departure_time[1000];

	srand(time(NULL));
	
	for(int i=0; i<N; i++){
		double P = (double)rand() / RAND_MAX;
        if (P == 0.0) {
            P = 1.0; 
        }

        intr_departure_time[i] = (-1.0 / depart_rate) * log(P / depart_rate);
	}

	return intr_departure_time;
}

int main(){
	int N, BUFFER = 1;
	printf("Enter the loop duration: ");
	scanf("%d", &N);

	int arrive_rate, total_pkts, pkt_drop = 0;
	float uf = 2;
	float BP; 
	//BP : pkt dropping probability/Blocking Probability

	FILE *fptr = fopen("exp_5.txt", "w");
	
	if(fptr == NULL){
		printf("Error opening file\n");
		return 0;
	}
	for(int n=0; n < N; n++){

		arrive_rate = uf*depart_rate;
		total_pkts = N*arrive_rate;

		//printf("\n%d\n", total_pkts);

				double* intr_arrival_time = expRV_arrive(N, arrive_rate);
		double* intr_departure_time = expRV_depart(N);
	
			for(int i = 0; i < N; i++) {
			if(intr_arrival_time[i] < intr_departure_time[i]) {
				
				pkt_drop = arrive_rate-BUFFER; 
			
				BP = (float)pkt_drop / total_pkts; 
				if(BP > 0.01) {
					BUFFER++;
				}
			
				else BUFFER--;
			}
			//printf("%d\t", pkt_drop);
			//printf("%d\t%f\t", BUFFER, BP);
			//printf("%lf\t%lf\n", intr_arrival_time[i], intr_departure_time[i]);
	
		
		}

		//printf("\n");
		fprintf(fptr, "%d %d\n", (int)uf, BUFFER);
		uf++;
	}
	fclose(fptr);	
	printf("\nFile created successfully\n");
	
}
