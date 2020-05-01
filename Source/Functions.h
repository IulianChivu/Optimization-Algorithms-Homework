#pragma once
#pragma once
#include<armadillo>
using namespace arma;

////Objective functions


//Ellipsoidal function -- fELP
//Schwefel function -- fSCH
//Generalized Rosenbrock function -- fROS
//Ackley function -- fACKL
//Rastrigin function -- fRTG
//Rotated Rastrigin function -- fRRTG

double fELP(vec x) { //not the function yet

	return dot(x.t(), x);
}
