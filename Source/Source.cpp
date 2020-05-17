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
	int functionEval = 0; //Number of function evaluations
	double optimum; //The value returned as the optimum solution
	int bestIndividualIndex; //Index of the optimum in population
	const int MAX_FUNCTION_EVAL = 1e6; 
	const double TARGET = 1e-20; //Target value for most objective functions
	const int M = 20; //No. of dimensions of an individual
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

	//Variable declarations seed and random generators
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // Initialize random seed
	default_random_engine generator(seed); //Initialize random generator
	uniform_real_distribution<double> unif_distribution(0, (double)(N-1)); //uniform distribution for choosing individuals from the current population
	uniform_real_distribution<double> unif_distribution_w(0.0, 1.0); //draw a random number in [0 1]
	srand((unsigned)time(NULL)); //radnom seed for random_init()

	//Must have a do-while() loop here for the runs

	//Popoulation initializations
	for (it = population.begin(); it != population.end(); it++)
		for (int i = 0; i < M; i++)
			it->at(i) = random_init(-10, -5); //random initialization between [-10,-5]


	do {

		//Parental selection
		//Choosing two individuals from the current population
		parent1 = population[(int)unif_distribution(generator)];
		parent2 = population[(int)unif_distribution(generator)];
		while (approx_equal(parent1, parent2, "absdiff", 0.0) == true) { //we make sure that we did not extract the same individual
			parent2 = population[(int)unif_distribution(generator)];
		}

		//Crossover
		for (xOFP = children.begin(); xOFP != children.end(); xOFP++) {

			//draw a random number in [0 1]
			double w = unif_distribution_w(generator);
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
			preselectedIndividuals[0] = population[(int)unif_distribution(generator)];
			preselectedIndividuals[1] = population[(int)unif_distribution(generator)];
			while (approx_equal(preselectedIndividuals[0], preselectedIndividuals[1], "absdiff", 0.0) == true) { //we make sure that we did not extract the same individual
				preselectedIndividuals[1] = population[(int)unif_distribution(generator)];
			}

			//The NREP set of individuals and determining the fBEST individual
			for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++) {
				if (fROS(*pI) < min) {
					min = fROS(*pI);
					fBest = *pI;
				}
			}

			//Determining the closest preselected individual
			int index = 0; //index of closest  preselected individual
			distMin = fabs(fROS(preselectedIndividuals[0]) - fROS(*xOFP));
			xCST = preselectedIndividuals[0];
			for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++) {

				if (fabs(fROS(*pI) - fROS(*xOFP)) < distMin) {

					distMin = fabs(fROS(*pI) - fROS(*xOFP));
					xCST = *pI;
					index = (int)(pI - preselectedIndividuals.begin());
				}
			}

			//Add fBEST condition here (The fittest individual does not always win)

			//Determining culling probabilities for xCST and xOFP
			double pOFP = (fROS(*xOFP) - fROS(fBest)) / (fROS(*xOFP) + fROS(xCST) - 2 * fROS(fBest));
			double pCST = (fROS(xCST) - fROS(fBest)) / (fROS(*xOFP) + fROS(xCST) - 2 * fROS(fBest));

			//If xOFP wins, we replace xCST with xOFP in the population
			if (pOFP < pCST) {
				for (it = population.begin(); it != population.end(); it++) {
					if (approx_equal(preselectedIndividuals[index], *it, "absdiff", 0.0) == true) {
						*it = *xOFP;
						break;
					}
				}
			}
		}

		//Determining the best individual in population as soultuion
		optimum = fROS(population[0]);
		bestIndividualIndex = 0;
		for (it = population.begin(); it != population.end(); it++)
			if (fROS(*it) < optimum) {

				optimum = fROS(*it);
				bestIndividualIndex = (int)(it - population.begin());
			}
		//Update the number of function evaluations
		functionEval += population.size();

	} while (optimum >= TARGET && functionEval <= MAX_FUNCTION_EVAL);
	

	fileOut << "Optimul: " << optimum << endl;
	fileOut << "No. of function evaluations: " << functionEval << endl;
	fileOut << "Optimum achived for this individual: " << endl << population[bestIndividualIndex] << endl;

	fileIn.close();
	fileOut.close();
	return 0;
}