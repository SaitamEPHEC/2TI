#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include "libproj.h"

struct Voiture {
	int numero;
	long best_s1;
	long best_s2;
	long best_s3;
 	long best_tour;
	long total_tour;
};



int main(int argc, char *argv[]){
	getRandomSeed();
	pid_t v1; 
	v1 = fork();

	void child_process(void){
		struct Voiture Voiture;
		
		//à généraliser pour n'importe quel processus de voiture
		Voiture.numero = 44;
		Voiture.best_s1 = LONG_MAX;
		Voiture.best_s2 = LONG_MAX;
		Voiture.best_s3 = LONG_MAX;
		Voiture.best_tour = LONG_MAX;	
		
		//Simulation P1 ==> 1h30 
		while(Voiture.total_tour <= 600000){

			long new_s1 = randomNumber();

			//update best_s1 si meilleur temps que précédent
			if(Voiture.best_s1 >= new_s1){
				Voiture.best_s1 = new_s1;	
			}
		
			long new_s2 = randomNumber();

			//update best_s2 si meilleur temps que précédent
			if(Voiture.best_s2 >= new_s2){
				Voiture.best_s2 = new_s2;	
			}

			long new_s3 = randomNumber();
			
			//update best_s3 si meilleur temps que précédent
			if(Voiture.best_s3 >= new_s3){
				Voiture.best_s3 = new_s3;	
			}
		
			long new_tour = new_s1 + new_s2 + new_s3;

			//update best_tour si meilleur temps de tour que précédent
			if(Voiture.best_tour >= new_tour){
				Voiture.best_tour = new_tour;
			}
			
			Voiture.total_tour += new_tour;

			char *s1_formated = timeFormat(new_s1);
			char *s2_formated = timeFormat(new_s2);	
			char *tour_formated = timeFormat(new_tour);
			char *s3_formated = timeFormat(new_s3);
			
			printf("Voiture n°%d:\t %s\t %s\t %s\t %s\n", Voiture.numero,
			timeFormat(new_tour), s2_formated, s3_formated, tour_formated);

			//Affichage des temps
			/*printf("Voiture n°%d :\t", Voiture.numero);
			printf("%s\t",timeFormat(new_s1);
			printf("%s\t",timeFormat(new_s2));
			printf("%s\t",timeFormat(new_s3));
			printf("%s\n", timeFormat(new_tour));*/

			//Affichage des Meilleur temps
			/*printf("MEILLEURS TEMPS : %s\t",timeFormat(Voiture.best_s1));
			printf("%s\t",timeFormat(Voiture.best_s2));
			printf("%s\t",timeFormat(Voiture.best_s3));
			printf("%s\n", timeFormat(Voiture.best_tour));
			printf("TEMPS TOTAL : %s\n\n", timeFormat(Voiture.total_tour));*/
			//fflush( stdout );
        		//sleep(1);
		}
	}

	void father_process(int child_pid){
		//Recevoir les infos des processus fils (voitures) et les stocker
	}

	switch(v1){
	//Si erreur lors du fork
	case -1:
	perror("Erreur de fork");
	return  EXIT_FAILURE;
	break;
	//Si on est dans le fils
	case 0:
	child_process();
	break;
	//Si on est dans le père
	default:
	father_process(v1);
	break;
	}

	return 0;
}


