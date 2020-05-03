# Teorie GA:
#### O sa implementam un algoritm genetic de tip SPC-PNX:
1. Initializare a A puncte in intervalul [-10,-5] (populatia initiala)
1. Doi parinti sunt selectati random din cei A pentru a produce B copii prin ***crossover*** pentru fiecare dintre cei B copii procedam astfel:
	1. luam un punct w random cuprins in intervalul [0,1]. 
		1. daca w < 0.5 folosim forma y(1) pentru a determina caracteristica copilului
		1. daca w >= 0.5 folosim forma y(2) pentru a determina caracteristica copilului
	1. calculam caracteristica copilului astfel:
		1. y(1) = N(x(1), |x(2)-x(1)|/n)
		1. y(2) = N(x(2), |x(2)-x(1)|/n), unde:
			* N(u,n) -> distributia normala(Gauss)
			* x(1) -> caracteristica parintelui 1
			* x(2) -> caracteristica parintelui 2
			* n -> parametru pe care putem sa-l variem (cu cat n e mai mare cu cat copilul va fi mai aproape de zona parintilor)
1. B NREP din populatia curenta sunt alesi random sa concureze cu cei B copii(pdf: 3.2 pag5); folosim algoritmul ***probabilistic crowding replacement:***
	* combinam copii cu NREP astfel: selectam un copil si cel mai apropiat NREP de el si calculam probabilitatea lor de a fi eliminati: 
		* copil : p(x1) = (f(x1) - fbest) / (f(x1) + f(x2) - 2*fbest)
		* NREP : p(x2) = (f(x2) - fbest) / (f(x1) + f(x2) - 2*fbest)
	* unde:
		* fbest -> valoarea functiei celui mai bun individ dintre cei 2*B
		* daca cel mai bun este copil sau parinte actual, atunci individul care intra in competitie cu el va avea sanse 0 sa fie eliminat
1. Go to pas 2 pana cand numarul maxim de pasi este atins (10^6) sau avem o eroare mai mica de 10^-20