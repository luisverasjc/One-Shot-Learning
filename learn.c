#include "learn.h"
int main(int argc, char **argv){
    FILE *fp;
	int i, j, k, attributes, examples, aRows, aCols, bCols, testExamples; 
	double **arr, **transpose, **result, **inverse, **temp, **test, *price, *weight, *testPrices, tmp, curr; 
	fp = fopen(argv[1], "r");	
	fscanf(fp, "%d\n%d", &attributes, &examples);
	attributes = attributes + 1;
	aRows = attributes;
	aCols = examples;
	bCols = aRows;
	weight = (double *) calloc (attributes, sizeof(double));
	arr = (double **) calloc(examples, sizeof(double *));
	for (i = 0; i < examples; i++){
		arr[i] = (double *) calloc(attributes, sizeof(double));
	}
	price = (double *) calloc(examples, sizeof(double));
	for(i = 0; i < examples; i++){
		arr[i][0] = 1;
		for(j = 1; j <= attributes; j++){
			if(j == attributes){
				fscanf(fp, "%lf", &price[i]);
			}
			else {
				fscanf(fp,"%lf,", &arr[i][j]);
			}
		}
	}
	//create transpose
	transpose = (double **) calloc(attributes, sizeof(double *));
	for(i = 0; i < attributes; i++){
		transpose[i] = (double *) calloc(examples, sizeof(double));
	}
	for(i = 0; i < examples; i++){
		for(j = 0; j < attributes; j++){
			tmp = arr[i][j];
			transpose[j][i] = tmp;
		}
	}
	result = multiply(transpose, arr, aRows, aCols, bCols);
	inverse = (double **) calloc(attributes, sizeof(double *));
	for(i = 0; i < attributes; i++){
		inverse[i] = (double *) calloc(attributes, sizeof(double));
		inverse[i][i] = 1;
	}
	//invert
	//bottom triangle & diagonal
	for(i = 0; i < attributes; i++){
		for(j = 0; j <= i; j++){
			curr = result[i][j];
			if(i != j && curr == 0){
				continue;
			}
			if(i == j){
				if(curr == 1){
					continue;
				}
				else{
					for(k = 0; k < attributes; k++){
						result[i][k] = result[i][k] / curr;
						inverse[i][k] = inverse[i][k] / curr;
					}
				}
			}
			else{
				for(k = 0; k < attributes; k++){
					result[i][k] = result[i][k] - (curr * result[j][k]);
					inverse[i][k] = inverse[i][k] - (curr * inverse[j][k]);
				}
			}
		}
	}
	//upper triangle to 0's
	for(i = attributes - 2; i >= 0; i--){
		for(j = attributes - 1; j > i; j--){
			curr = result[i][j];
			if(curr == 0){
				continue;
			}
			else{
				for(k = 0; k < attributes; k++){
					result[i][k] = result[i][k] - (curr * result[j][k]);
					inverse[i][k] = inverse[i][k] - (curr * inverse[j][k]);
				}
			}
		}
	}
	temp = (double **) calloc(attributes, sizeof(double *));
	for(i = 0; i < attributes; i++){
		temp[i] = calloc(examples, sizeof(double));
	}
	temp = multiply(inverse, transpose, attributes, attributes, examples);
	weight = multiply1d(temp, price, attributes, examples);
	fp = fopen(argv[2], "r");	
	fscanf(fp, "%d", &testExamples);
	test = (double **) calloc(testExamples, sizeof(double *));
	for(i = 0; i < testExamples; i++){
		test[i] = (double *) calloc(attributes, sizeof(double));
	}
	for(i = 0; i < testExamples; i++){
		test[i][0] = 1;
		for(j = 1; j < attributes; j++){
			fscanf(fp, "%lf,", &test[i][j]);
		}
	}
	testPrices = (double *) calloc(testExamples, sizeof(double));
	testPrices = multiply1d(test, weight, testExamples, attributes);
	for(i = 0; i < testExamples; i++){
		printf("%0.0lf\n", testPrices[i]);
	}
	return 0;
}
