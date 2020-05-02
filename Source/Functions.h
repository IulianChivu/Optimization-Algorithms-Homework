#pragma once
#include<armadillo>
#define _USE_MATH_DEFINES //to be able to se M_PI, must be defined before math.h
#include<math.h>
using namespace arma;

////Objective functions


//Ellipsoidal function -- fELP
//Schwefel function -- fSCH
//Generalized Rosenbrock function -- fROS
//Ackley function -- fACKL
//Rastrigin function -- fRTG
//Rotated Rastrigin function -- fRRTG

double fELP(vec x) { 

	rowvec y(x.size());
	double j = 1;
	for (int i = 0; i < x.size(); i++)
		y[i] = j++;
	x = x % x;
	return dot(y, x.t());
}

double fSCH(vec x) {

	double sum = 0.0;
	double result = 0.0;
	for (int j = 0; j < x.size(); j++) {
		sum += x[j];
		result += sum * sum;
	}
	return result;
}

double fROS(vec x) {

	double first_term = 0.0;
	double second_term = 0.0;
	double sum = 0.0;
	for (int j = 0; j < x.size() - 1; j++) {
		//warning about arithmetic overflow for x[j+1] -> casting a 4 byte value to an 8 byte one
		first_term += 100 * (x[j] * x[j] - x[j + 1]) * (x[j] * x[j] - x[j + 1]);
		second_term += (x[j] - 1) * (x[j] - 1);
	}
	sum += first_term;
	sum += second_term;

	return sum;
}

double fACKL(vec x) {

	rowvec y(x.size());
	y.fill(1.0);
	double first_sum = dot(y, x % x);
	double first_exp = exp(-0.2 * sqrt(1.0 / x.size() * first_sum));
	double second_sum = 0.0;

	for (int j = 0; j < x.size(); j++)
		second_sum += cos(2 * M_PI * x[j]);

	double second_exp = exp(1.0 / x.size() * second_sum);
	
	return 20.0 + exp(1) - 20.0 * first_exp - second_exp;
}


