#include<iostream>
#include<armadillo>
#include"Functions.h";
using namespace std;
using namespace arma;

int main() {

	cout << "TOP" << endl;
	cout << "TOP" << endl;

	mat A(2, 2);
	A.fill(3.0);
	vec x(3);
	x[0] = 1;
	x[1] = 2;
	x[3] = 3;
	rowvec y = x.t();
	cout << size(A) << endl;
	cout << A.size() << endl;
	cout << dot(x,y);

	cin.get();
	return 0;
}