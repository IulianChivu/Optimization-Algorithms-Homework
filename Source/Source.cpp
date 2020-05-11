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
	const int lambda = 1; //No. of children
					//must find a way to read it from file and make it const
	const double niu = 2.0; //Mean used for crossover as parameter for the Normal Distribution
					//must find a way to read it from file and make it const
	const int NREP = 2; //No. of preselected individuals to compete for a place in the
					  //population
					//must find a way to read it from file and make it const
	vector<vec::fixed<M>> population(N);
	vector<vec::fixed<M>> children(lambda);
	vector<vec::fixed<M>>::iterator it;
	vec::fixed<M> parent1, parent2, fBest;

	//Popoulation initializations
	for (it = population.begin(); it != population.end(); it++)
		for (int i = 0; i < M; i++)
			it->at(i) = coin_flip(); //must be made after a certain function layout
									//will not be using the current one


	//Must have a do-while() loop here
	
	//Parental selection
	//Choosing two individuals from the current population
	parent1 = population[rand() % N];//should be made following a uniform distribution
	parent2 = population[rand() % N];//should be made following a uniform distribution
	fileOut << "parents down ////////////////////////" << endl;
	fileOut << parent1 << endl << parent2 << endl;

	//Crossover
	for (it = children.begin(); it != children.end(); it++) {

		//draw a random number in [0 1]
		double w = coin_flip();
		fileOut << w << endl;
		if (w < 0.5)
			for (int j = 0; j < parent1.size(); j++)
				it->at(j) = normal_dis(parent1[j], fabs(parent2[j] - parent1[j]) / niu);
		else //works only if w is a number in [0 1]
			for (int j = 0; j < parent2.size(); j++)
				it->at(j) = normal_dis(parent2[j], fabs(parent2[j] - parent1[j]) / niu);
		
	}

	//Selection
	for (it = children.begin(); it != children.end(); it++) {

		vector<vec::fixed<M>> preselectedIndividuals(NREP);
		vector<vec::fixed<M>>::iterator pI;
		double min = fELP(*it);//Initialize min to find the best individual fBest

		//Choosing the preselected individuals
		//for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++)
		
		//Continue here
	}
	
	fileOut << "kids down ////////////////////////" << endl;
	for (it = children.begin(); it != children.end(); it++)
		fileOut << *it << endl;
	fileOut << "population down ////////////////////////" << endl;
	for (it = population.begin(); it != population.end(); it++)
		fileOut << *it << endl;
	fileOut << "fELP for each individual ////////////////////////" << endl;
	for (it = population.begin(); it != population.end(); it++)
		fileOut << fELP(*it) << endl;

	fileIn.close();
	fileOut.close();
	return 0;
}