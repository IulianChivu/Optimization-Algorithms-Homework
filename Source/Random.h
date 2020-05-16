#pragma once
#include<random>
using namespace std;

//distributie normala(Gauss)
double normal_dis(double medie, double dispersie) {
	default_random_engine generator;
	normal_distribution<double> distribution(medie, dispersie);
	return distribution(generator);
}

//random intre [0,1] pentru w din crossover
double coin_flip() {

	//srand(time(NULL));
	return ((double)rand() / (RAND_MAX));
}

//returns a random number between 0 and N - 1
int randomN(int N) {

	srand(time(NULL));
	return rand() % N;
}