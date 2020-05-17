#pragma once
#include<random>
using namespace std;

//distributie normala(Gauss)
double normal_dis(double medie, double dispersie) {
	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); // Initialize random seed
	default_random_engine generator(seed); //Initialize random generator
	normal_distribution<double> distribution(medie, dispersie);
	return distribution(generator);
}

//random initialization between [-10,-5]
double random_init(double min, double max) { // random between [min,max];
	double out;
	out = ((double)rand() / (RAND_MAX)); //random between [0,1]
	out = min + out * (max - min); //random bewtween [min,max]
	return out;
}
