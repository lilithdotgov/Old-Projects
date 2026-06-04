#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct s_result{
	int* i_arr;
	double* f_arr;
} result;

struct s_result foo(){

	
	int A[] = {1,2,3}; double B[] = {3.0,4.0};
	result.i_arr = malloc(sizeof A);
	result.f_arr = malloc(sizeof B);
	memcpy(result.i_arr, A, sizeof A);
	memcpy(result.f_arr, B, sizeof B);

	return result;
}

int main(){
	struct s_result D = foo();
	free(result.i_arr); free(result.f_arr);
	printf("%d\t%d\t%d\n",D.i_arr[0],D.i_arr[1],D.i_arr[2]);
	printf("%f\t%f\n",D.f_arr[0],D.f_arr[1]);
	//printf("%d\t%d\t%d\n",result.i_arr[0],result.i_arr[1],result.i_arr[2]);
	//printf("%f\t%f\n",result.f_arr[0],result.f_arr[1]);
	
	free(D.i_arr); free(D.f_arr);
}