#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<limits.h>

#define depart_rate 1

double* expRV_arrive(int N, float uf){
	int arrive_rate;
	static double intr_arrival_time[1000];
	double pkts_time = 0;
	//double total_time = 10;
	//float BP;

	arrive_rate = uf*depart_rate;

	for(int i=0; i<N; i++){
		intr_arrival_time[i] = (-1/arrive_rate)*log((((double)rand())/(INT_MAX*arrive_rate));
		printf("%lf\t", intr_arrival_time[i]);
		pkts_time = pkts_time + intr_arrival_time[i];
	}
	
	printf("\n%lf\n", pkts_time);
	

	//BP = pkts_time/total_time;

	//printf("\n%f", BP);

	return intr_arrival_time;
}

double* expRV_depart(int N){
	static double intr_departure_time[1000];
	
	for(int i=0; i<N; i++){
		intr_departure_time[i] = (-1/depart_rate)*exp(((double)rand())/(INT_MAX*depart_rate));
	}

	return intr_departure_time;
}

int main(){
	int N, BUFFER = 2;
	printf("Enter the loop duration: ");
	scanf("%d", &N);
	
	float uf = 3;

	
	double* intr_arrival_time = expRV_arrive(N, uf);
	double* intr_departure_time = expRV_depart(N);
	
	FILE *fptr = fopen("exp6.txt", "w");
	if(fptr == NULL){
		printf("Error opening file\n");
		return 0;
	}
	if(BUFFER >= 2){
		for(int i=0; i<N; i++){
		if(intr_arrival_time < intr_departure_time)
			BUFFER++;
		
		fprintf(fptr, "%d\n", BUFFER);
		printf("%lf\t%lf\n", intr_arrival_time[i], intr_departure_time[i]);
		}
	}
	fclose(fptr);	
	printf("File created successfully\n");
	double A = log(((double)rand())/(INT_MAX*3));
	printf("%lf\n", A);
	return 0;

}
