#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

#define depart_rate 1

double* expRV_arrive(int N, int arrive_rate){
	static double intr_arrival_time[1000];
	double pkts_time = 0;
		
	for(int i=0; i<N; i++){
		double P = (double)rand() / RAND_MAX;
        if (P == 0.0) {
            P = 1.0; 
        }

        intr_arrival_time[i] = (-1.0 / arrive_rate) * log(P / arrive_rate);
		printf("%lf\t", intr_arrival_time[i]);
		pkts_time = pkts_time + intr_arrival_time[i];
	}
	
	printf("\n%lf\n", pkts_time);


	return intr_arrival_time;
}

double* expRV_depart(int N){
	static double intr_departure_time[1000];
	
	for(int i=0; i<N; i++){
		double P = (double)rand() / RAND_MAX;
        if (P == 0.0) {
            P = 1.0; 
        }

        intr_departure_time[i] = (-1.0 / depart_rate) * log(P / depart_rate);
		printf("%lf\t", intr_departure_time[i]);
	}

	return intr_departure_time;
}

int main(){
	int N, BUFFER = 2;
	printf("Enter the loop duration: ");
	scanf("%d", &N);

	int arrive_rate, total_pkts, pkt_drop;
	float uf = 30;
	float BP; 
	//BP : pkt dropping probability/Blocking Probability

	arrive_rate = uf*depart_rate;
	total_pkts = N*arrive_rate;
	
	double* intr_arrival_time = expRV_arrive(N, arrive_rate);
	double* intr_departure_time = expRV_depart(N);
	
	FILE *fptr = fopen("exp_5.txt", "w");
	if(fptr == NULL){
		printf("Error opening file\n");
		return 0;
	}		
	
	for(int i=0; i<N; i++){
		if(intr_arrival_time < intr_departure_time){
			pkt_drop = arrive_rate-BUFFER;
			BP = pkt_drop/total_pkts;
			if(BP > 0.01)	BUFFER++;
		}
		fprintf(fptr, "%f %d\n", uf, BUFFER);
	}

	
	fclose(fptr);	
	printf("\nFile created successfully\n");
	

}
