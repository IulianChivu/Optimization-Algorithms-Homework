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
	return ((double)rand() / (RAND_MAX));
}