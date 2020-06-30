# Optimization Algorithms Homework
In this homework me and my colleague [Iulian Chivu](https://github.com/IulianChivu) had to implement an optimization algorithm based on a scientific study conducted by Pedro J. Ballester and Jonathan N. Carter. The algorithm is a real-parameter genetic algorithm with parent centric normal crossover for multimodal optimization. For a better time performance we chose to implement the algorithm in C++ using the Armadillo linear algebra library. Just like in the study we tested the algorithm's performance on a series of multimodal functions in a specific number of runs. Unfortunatly we did not achive the same performance as the authors of the paper, we belive the difference appeared because we did not implement the algorithm 100% correct. **A more detailed explanation can be found in Documentation -> Documentation.pdf**. Our results are shown in the following table: 
|  M 	|   	|  N  	|   	| No. of offspring 	|   	| FUNC 	|   	| BEST FOUND 	|   	| SUCCESS 	|   	| RUNS 	|
|:--:	|---	|:---:	|---	|:----------------:	|---	|:----:	|---	|:----------:	|---	|:-------:	|---	|:----:	|
|    	|   	|     	|   	|                  	|   	|      	|   	|            	|   	|         	|   	|      	|
| 20 	|   	|  35 	|   	|         1        	|   	|  ELP 	|   	|   10^-15   	|   	|   1/10  	|   	|  10  	|
| 20 	|   	|  35 	|   	|         1        	|   	|  SCH 	|   	|    10^-1   	|   	|   1/10  	|   	|  10  	|
| 20 	|   	|  80 	|   	|         1        	|   	|  ROS 	|   	|    10^1    	|   	|  28/50  	|   	|  50  	|
| 20 	|   	|  50 	|   	|         1        	|   	| ACKL 	|   	|    10^-4   	|   	|   3/10  	|   	|  10  	|
| 20 	|   	| 400 	|   	|         4        	|   	|  RTG 	|   	|    10^2    	|   	|  10/10  	|   	|  10  	|
| 20 	|   	| 400 	|   	|         4        	|   	| RRTG 	|   	|    10^2    	|   	|  10/10  	|   	|  10  	|
