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
	ofstream fileOut("Out.txt");
	int functionEval = 0; //Number of function evaluations
	double optimum; //The value returned as the optimum solution
	int bestIndividualIndex; //Index of the optimum in population
	const int MAX_FUNCTION_EVAL = 1e6; 
	const double TARGET = 1e-20; //Target value for most objective functions
	//down varies but up doesen't
	const int runs = 10; //
	const int M = 20; //No. of dimensions of an individual
	const int N = 400; //No. of population individuals
	const int lambda = 4; //No. of children
	//up varies but down doesen't
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

	for (int r = 0; r < runs; r++) {

		//Popoulation initializations
		for (it = population.begin(); it != population.end(); it++)
			for (int i = 0; i < M; i++)
				it->at(i) = random_init(-10, -5); //random initialization between [-10,-5]

		functionEval = 0; //Reset the number of function evaluations for every run

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
					for (int j = 0; j < parent1.size(); j++) {
						double sigma = fabs(parent2[j] - parent1[j]) / niu;
						if (sigma == 0.0) sigma = 0.001;
						xOFP->at(j) = normal_dis(parent1[j], sigma);
					}
				else //works only if w is a number in [0 1]
					for (int j = 0; j < parent2.size(); j++) {
						double sigma = fabs(parent2[j] - parent1[j]) / niu;
						if (sigma == 0.0) sigma = 0.000001;
						xOFP->at(j) = normal_dis(parent1[j], sigma);
					}

			}

			//First encounter of the objective function here
			//Selection
			for (xOFP = children.begin(); xOFP != children.end(); xOFP++) {

				double min = fRRTG(*xOFP);//Initialize min to find the best individual fBest
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
					if (fRRTG(*pI) < min) {
						min = fRRTG(*pI);
						fBest = *pI;
					}
				}

				//Determining the closest preselected individual
				int index = 0; //index of closest  preselected individual
				distMin = fabs(fRRTG(preselectedIndividuals[0]) - fRRTG(*xOFP));
				xCST = preselectedIndividuals[0];
				for (pI = preselectedIndividuals.begin(); pI != preselectedIndividuals.end(); pI++) {

					if (fabs(fRRTG(*pI) - fRRTG(*xOFP)) < distMin) {

						distMin = fabs(fRRTG(*pI) - fRRTG(*xOFP));
						xCST = *pI;
						index = (int)(pI - preselectedIndividuals.begin());
					}
				}

				//Add fBEST condition here (The fittest individual does not always win)

				//Determining culling probabilities for xCST and xOFP
				double pOFP = (fRRTG(*xOFP) - fRRTG(fBest)) / (fRRTG(*xOFP) + fRRTG(xCST) - 2 * fRRTG(fBest));
				double pCST = (fRRTG(xCST) - fRRTG(fBest)) / (fRRTG(*xOFP) + fRRTG(xCST) - 2 * fRRTG(fBest));

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
			optimum = fRRTG(population[0]);
			bestIndividualIndex = 0;
			for (it = population.begin(); it != population.end(); it++)
				if (fRRTG(*it) < optimum) {

					optimum = fRRTG(*it);
					bestIndividualIndex = (int)(it - population.begin());
				}
			//Update the number of function evaluations
			functionEval += population.size();

		} while (optimum >= TARGET && functionEval <= MAX_FUNCTION_EVAL);


		fileOut << "Optimul: " << optimum << endl;
		fileOut << "No. of function evaluations: " << functionEval << endl;
		fileOut << "Optimum achived for this individual: " << endl << population[bestIndividualIndex] << endl;


	}

	fileOut.close();
	return 0;
}