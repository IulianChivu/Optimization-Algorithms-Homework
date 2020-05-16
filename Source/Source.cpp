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
	const int MAX_FUNCTION_EVAL = 1e6; 
	const int TARGET = 1e-20; //Target value for most objective functions
	default_random_engine generator; //don't know
	normal_distribution<double> distribution(-7.5, 0.99);//don't know
	const int M = 5; //No. of dimensions of an individual
					//must find a way to read it from file and make it const
	const int N = 35; //No. of population individuals
					//must find a way to read it from file and make it const
	const int lambda = 1; //No. of children
					//must find a way to read it from file and make it const
	const double niu = 2.0; //Mean used for crossover as parameter for the Normal Distribution
	const int NREP = 2; //No. of preselected individuals to compete for a place in the
					  //population
	
	vector<vec::fixed<M>> population(N);
	vector<vec::fixed<M>> children(lambda);
	vector<vec::fixed<M>>::iterator xOFP, it;
	vector<vec::fixed<M>> preselectedIndividuals(NREP);
	vector<vec::fixed<M>>::iterator pI;
	vec::fixed<M> parent1, parent2, fBest, xCST;

	//Must have a do-while() loop here for the runs

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
	for (xOFP = children.begin(); xOFP != children.end(); xOFP++) {

		//draw a random number in [0 1]
		double w = coin_flip();
		fileOut << w << endl;
		if (w < 0.5)
			for (int j = 0; j < parent1.size(); j++)
				xOFP->at(j) = normal_dis(parent1[j], fabs(parent2[j] - parent1[j]) / niu);
		else //works only if w is a number in [0 1]
			for (int j = 0; j < parent2.size(); j++)
				xOFP->at(j) = normal_dis(parent2[j], fabs(parent2[j] - parent1[j]) / niu);
		
	}

	//Selection
	for (xOFP = children.begin(); xOFP != children.end(); xOFP++) {

		double min = fROS(*xOFP);//Initialize min to find the best individual fBest
		double distMin;
		fBest = *xOFP;//Initialize fBest as xOFP

		//Choosing the preselected individuals at random from the population
		//The NREP set of individuals and determining the fBEST individual
		for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++) {

			srand(time(NULL));
			*pI = population[rand() % population.size()];
			if (fROS(*pI) < min) {
				min = fROS(*pI);
				fBest = *pI;
			}
			fileOut << "fbest here ////////////////" << endl;
		fileOut << fBest << " " << min << endl;
		}

		//Determining the closest preselected individual
		distMin = fabs(fROS(preselectedIndividuals[0]) - fROS(*xOFP));
		xCST = preselectedIndividuals[0];
		for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++) {
			
			if (fabs(fROS(*pI) - fROS(*xOFP)) < distMin) {

				distMin = fabs(fROS(*pI) - fROS(*xOFP));
				xCST = *pI;
			}
		}

		//Add fBEST condition here (The fittest individual does not always win)
		
		//Determining culling probabilities for xCST and xOFP
		double pOFP = (fROS(*xOFP) - fROS(fBest)) / (fROS(*xOFP) + fROS(xCST) - 2 * fROS(fBest));
		double pCST = (fROS(xCST) - fROS(fBest)) / (fROS(*xOFP) + fROS(xCST) - 2 * fROS(fBest));

		if (pOFP < pCST) {

			void;
			//Continue here
			//Swap xCST with xOFP in population
		}

	}
	
	fileOut << "kids down ////////////////////////" << endl;
	for (it = children.begin(); it != children.end(); it++)
		fileOut << *it << endl;
	fileOut << "population down ////////////////////////" << endl;
	for (it = population.begin(); it != population.end(); it++)
		fileOut << *it << endl;
	fileOut << "fROS for each individual ////////////////////////" << endl;
	for (it = population.begin(); it != population.end(); it++)
		fileOut << fROS(*it) << endl;

	fileOut << "NREP population down ////////////////////////" << endl;
	for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++)
		fileOut << *pI << endl;

	fileOut << MAX_FUNCTION_EVAL << endl;
	fileIn.close();
	fileOut.close();
	return 0;
}