#include <stdio.h>
#include <stdlib.h>
#include <math.h>
double** multiply(double **a, double **b, int aRows, int aCols, int bCols);
double* multiply1d(double **a, double *b, int aRows, int aCols);

double** multiply(double **a, double **b, int aRows, int aCols, int bCols){
	double **res;
	int o, p, q;
	res = (double **) calloc(aRows, sizeof(double *));
	for(o = 0; o < aRows; o++){
		res[o] = (double *) calloc(bCols, sizeof(double));
	}
	for(o = 0; o < aRows ; o++){
		for(p = 0; p < bCols; p++){
			for(q = 0; q < aCols; q++){
				res[o][p] += a[o][q] * b[q][p];
			}
		}
	}
	return res;
}

double* multiply1d(double **a, double *b, int aRows, int aCols){
	double *ans;
	int o, p;
	ans = (double*) calloc(aRows, sizeof(double));
	for(o = 0; o < aRows; o++){
		for(p = 0; p < aCols; p++){
			ans[o] += (a[o][p] * b[p]);
		}
	}
	return ans;
}
