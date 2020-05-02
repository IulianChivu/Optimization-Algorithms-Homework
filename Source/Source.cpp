#include<iostream>
#include<armadillo>
#include"Functions.h";
using namespace std;
using namespace arma;

int main() {

	cout << "TOP" << endl;
	cout << "TOP" << endl;

	vec x = { 1.0, 2.0, 1.0 };
	
	cout << fELP(x) << endl;
	cout << fSCH(x) << endl;
	cout << fROS(x) << endl;
	cout << fACKL(x) << endl;

	return 0;
}