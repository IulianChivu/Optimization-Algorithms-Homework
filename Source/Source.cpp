#include<iostream>
#include<armadillo>
#include"Functions.h";
using namespace std;
using namespace arma;

int main() {

	cout << "TOP" << endl;
	cout << "TOP" << endl;

	vec x = { 1,1,1 };
	//rowvec y = x.t();
	cout << fELP(x);

	return 0;
}