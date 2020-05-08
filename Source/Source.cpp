#include<iostream>
#include<armadillo>
#include<vector>
#include<fstream>
#include"Functions.h";
#include"Random.h";
using namespace std;
using namespace arma;

int main() {

	//Variable declarations
	ifstream fileIn("In.txt");
	ofstream fileOut("Out.txt");
	const int MAX_FUNCTION_EVAL = 10e6; 
	default_random_engine generator; //don't know
	normal_distribution<double> distribution(-7.5, 0.99);//don't know
	const int M = 4; //No. of dimensions of an individual
					//must find a way to read it from file and make it const
	const int N = 35; //No. of population individuals
					//must find a way to read it from file and make it const
	const int lambda = 2; //No. of children
					//must find a way to read it from file and make it const
	vector<vec::fixed<M>> population(N);
	vector<vec::fixed<M>> children(lambda);
	vector<vec::fixed<M>>::iterator it;
	vec::fixed<M> parent1, parent2;

	//Must have a do-while() loop here
	 

	//Popoulation initializations
	for (it = population.begin(); it != population.end(); it++)
		for (int i = 0; i < M; i++)
			it->at(i) = coin_flip(); //must be made after a certain function layout
									//will not be using the current one
	
	//Parental selection
	//Choosing two individuals from the current population
	parent1 = population[rand() % N];//should be made following a uniform distribution
	parent2 = population[rand() % N];//should be made following a uniform distribution

	//Crossover
	for (it = children.begin(); it != children.end(); it++) {

		double w = coin_flip();
		fileOut << w << endl;
		/*if (w < 0.5) void;
			*it = crossoverForm1(parent1, parent2);
		else //works only if w is a number in [0 1]
			*it = crossoverForm2(parent1, parent2);
		*/

	}
		

	for (it = population.begin(); it != population.end(); it++)
		fileOut << *it << endl;
	for (it = population.begin(); it != population.end(); it++)
		fileOut << fELP(*it) << endl;

	fileIn.close();
	fileOut.close();
	return 0;
}