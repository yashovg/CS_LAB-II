#include<stdio.h>
#include<math.h>
#include<complex.h>
#include<stdlib.h>

#define neta 1
#define g_m 15
#define L 0.01
#define a 1.0274
#define b 1.5
#define E_c 1
#define PI 3.1415926535897

int main(){
	
	FILE* fptr;
	fptr = fopen("TF.txt", "w");
	if (fptr == NULL) {
        printf("Error opening file!\n");
        return 1;
    	}
	double T_1, T_2, T_3, T_4;
	double TF_real, TF_img;
	double x, f_m = 1.5, f_c = 45, f_s = 4500, W_c, Q_e;
	int Length = 2000;

	Q_e = 1/(2*0.66*f_c*f_m);
	W_c = 2*PI*f_c;
	T_1 = neta*g_m*W_c*L*Q_e;

	for(int i=1; i<=Length; i++){

		x = ((i*f_s)/Length - f_c)/f_c;

		T_2 = pow((1 + pow((x+a), 2)), 0.5);
		T_3 = (1 - pow((x+a),2));
		T_4 = (1 + pow(b, 2) - pow(x, 2)) + 4*pow(x, 4);
	
		if(T_3 >= 0){ 
			TF_real = (T_1*(T_2-pow(T_3, 0.5)))/T_4;
			TF_img = 0;
		}
		else {
			TF_real = (T_1*T_2)/T_4;
			TF_img = (-T_1*pow(-T_3, 0.5))/T_4;
		}	
	
		fprintf(fptr, "%d %lf %lf\n", i, TF_real, TF_img); 

	}

	fclose(fptr);
	return 0;

}
