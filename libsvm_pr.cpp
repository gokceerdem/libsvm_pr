#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <iostream>
#include "svm.h"
#include "stdafx.h"
#define Malloc(type,n) (type *)malloc((n)*sizeof(type))

struct svm_parameter param;     // set by parse_command_line
struct svm_problem prob;        // set by read_problem
struct svm_model *model;
struct svm_node *x_space;

using namespace std;

int main()
{
    char input_file_name[1024];
    char model_file_name[1024];
    const char *error_msg;

    param.svm_type = C_SVC;
    param.kernel_type = RBF;
    param.degree = 3;
    param.gamma = 0.5;
    param.coef0 = 0;
    param.nu = 0.5;
    param.cache_size = 100;
    param.C = 1;
    param.eps = 1e-3;
    param.p = 0.1;
    param.shrinking = 1;
    param.probability = 1;
    param.nr_weight = 0;
    param.weight_label = NULL;
    param.weight = NULL;
	


    //Problem definition-------------------------------------------------------------
    prob.l = 12;

    //x values matrix of xor values
	double  inputs[12][2];

	inputs[0][0] = 0.1;
	inputs[0][1] = 0.1;

	inputs[1][0] = 0.89;
	inputs[1][1] = 0.45;

	inputs[2][0] = 0.56;
	inputs[2][1] = 0.568;

	inputs[3][0] = 0.4789;
	inputs[3][1] = 0.1111;

	inputs[4][0] = -0.732;
	inputs[4][1] = 0.9;

	inputs[5][0] = -0.666;
	inputs[5][1] = 0.65;

	inputs[6][0] = -0.9;
	inputs[6][1] = 0.5;

	inputs[7][0] = -0.78;
	inputs[7][1] = 0.23;
	
	inputs[8][0] = 0.19;
	inputs[8][1] = -0.1;

	inputs[9][0] = 0.88;
	inputs[9][1] = -0.001;

	inputs[10][0] = 0.1277;
	inputs[10][1] = -0.9910;

	inputs[11][0] = 0.99;
	inputs[11][1] = -0.409;

    //This part i have trouble understanding
    svm_node** x = Malloc(svm_node*,12);

    //Trying to assign from matrix to svm_node training examples
    for (int row = 0;row <12; row++){
        svm_node* x_space = Malloc(svm_node,3);
        for (int col = 0;col < 2;col++){
            x_space[col].index = col;
            x_space[col].value = inputs[row][col];
        }
        x_space[2].index = -1;      //Each row of properties should be terminated with a -1 according to the readme
        x[row] = x_space;
    }

    prob.x = x;

    //yvalues
    prob.y = Malloc(double,prob.l);
    prob.y[0] = 1;
    prob.y[1] = 1;
    prob.y[2] = 1;
    prob.y[3] = 1;

	prob.y[4] = 2;
    prob.y[5] = 2;
    prob.y[6] = 2;
    prob.y[7] = 2;

	prob.y[8] = 3;
    prob.y[9] = 3;
    prob.y[10] = 3;
    prob.y[11] = 3;

    //Train model---------------------------------------------------------------------
    svm_model *model = svm_train(&prob,&param);


    //Test model----------------------------------------------------------------------
    svm_node* testnode = Malloc(svm_node,3);
	double test[3][2];

	test[0][0] = 0.177;
	test[0][1] = 0.1989;

	test[1][0] = -0.89;
	test[1][1] = 0.45;

	test[2][0] = 0.156;
	test[2][1] = -0.568;

	double prob_estimates[3];
	for (int dongu = 0; dongu<3; dongu++){    

		testnode[0].value = test[dongu][0];
		testnode[0].index = 0;

		testnode[1].value = test[dongu][1];
		testnode[1].index = 1;

		testnode[2].index = -1;
		
//		std::cout << "***" << testnode[0].value << " " <<testnode[1].value << endl; 

	float retval = svm_predict_probability(model,testnode,prob_estimates);
    printf("retval: %f\n",retval);
	    }


    svm_destroy_param(&param);
    free(prob.y);
    free(prob.x);
    free(x_space);

    return 0;
}