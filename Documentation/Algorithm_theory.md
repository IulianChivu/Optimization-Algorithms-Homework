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
1. ?B? parinti sunt alesi random sa concureze cu cei B copii(pdf: 3.2 pag5); folosim algoritmul ***probabilistic crowding replacement:***
	* pentru fiecare din cei 2B participanti calculam probabilitatea lor de a supravietui: p(x1) = (f(x1) - fbest) / (suma de la 1 la 2B din(f(xi)) - 2*B*fbest)
	* unde:
		* fbest -> valoarea functiei celui mai bun individ dintre cei 2B