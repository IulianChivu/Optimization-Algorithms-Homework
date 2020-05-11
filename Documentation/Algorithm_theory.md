# Teorie GA (by Iulian)
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

# Teorie GA (by Bogdan)

Algoritmul genetic de implementat este SPC-PNX (scaled probabilistic crowding genetic algorithm with parent centric normal crossover). Algoritmul dispune de urmatoarele 3 faze in ordine:

- Selectie
- Recombinare (crossover)
- Inlocuirea indivizilor in populatie pentru a pastra pe aceasta *constanta*.

**Conditii initiale:** o populatie de dimensiune **N** cu indivizi *M-dimensionali*.

## Pasii algoritmului

1. **Initializarea populatiei**
	1. Initializarea variabilelor de care depinde operatia de recombinare
	2. Initializarea componentelor indivizilor cu valori aleatoare in intervalul [-10 -5]
2. **Recombinarea (de tip PNX)**
	1. Din populatia curenta se aleg aleator dupa o **distributie uniforma**,  **2** parinti
	2. Se doreste ca din cei 2 parinti selectati sa rezulte **lambda copii**. Pentru fiecare copil:
		- Se alege un numar aleator **w** din intervalul [0 1]
		-  Daca **w** < 0.5 folosim forma (1) pentru a determina genele copilului
		-  Daca **w** >= 0.5 folosim forma (2) pentru a determina genele copilului
		- Genele copilului se determina alegand pentru fiecare un numar aleator ce urmeaza o **distributie gaussiana** N(miu, sigma) de medie miu si dispersie sigma
3. **Selectia (replacement)**
	- ??? Pentru fiecare copil:
		- Se alege un numar de **NREP = 2** indivizi aleator din populatie 
		- Din multimea de **NREP = 2** indivizi se alege individul "cel mai apropiat" de copilul curent
		- Individul selectat la pasul anterior intra intr-un turneu probabilistic cu copilul curent cu scopul de a concura pentru un loc in populatie, se foloseste setul (2) de probabilitati pentru a decide cine ramane in populatie
		- Aici inca exista o neclaritate, dupa ce se va decide *cst* din *NREP* presupun ca acesta va fi marcat pentru urmatoarele turnee pentru a nu putea fi selectat din nou ?!, deoarece indiferent cine castiga (*cst* sau *ofp* ) acel individ va avea un loc asigurat in populatie ?!
4. **Se evalueaza functia obiectiv pentru fiecare individ si daca nu s-au atins un numar de 10^6 sondari ale functiei SAU o eroare de 10^-20 (10^-10 pentru anumite functii obiectiv) se continua algoritmul de la pasul 2; ALTFEL se returneaza cel mai bun individ ca solutie de optim**