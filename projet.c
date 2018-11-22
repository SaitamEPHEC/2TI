#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include "libproj.h"


int main(int argc, char *argv[]){
	//tableau des numéros de
	int tabNum [20] = {44, 77, 5, 7, 3, 33, 11, 31, 18, 35, 27, 55, 10, 28, 8, 20, 2, 14, 9, 16};
	getRandomSeed();
	struct Voiture* shmem;

	//mémoire partagée
	//crée le segment 
	int shmid = shmget(KEY_SHM, 20*sizeof(struct Voiture), SHM_FLAG); // valeur retournee de shmget, si -1 erreur lors du partage de memoire
	
    	//test si erreur shmget
   	 if (shmid < 0) {
     	   perror("Erreur shmget");
     	   exit(1);
   	 }

   	 //on attache le segment à l'espace de donnée
   	 if (shmem = shmat(shmid, NULL, 0) == (void *) -1) {
		perror("Erreur shmat");
		exit(1);
  	 }
	
	//FORK
	pid_t pids[3];

	for(int i=0;i<=3;i++){
		//processus fils
		if((pids[i] = fork()) == 0){
			if (shmem = shmat(shmid,NULL, 0) == (void *) -1){
				perror("Erreur shmat");
				exit(1);			
			}

			//TODO
			//Assigner la 1ère voiture à la 1ère case de la SH, 
			//Assigner la 2ème voiture à la 2ème case de la SH,
			//etc...
			
			child_process();
			
		}
		//processus père
		if(pids[i] != 0){
			father_process();
		}	
	}

	shmdt(shmem);
	return 0;
}

void child_process(void){
	struct Voiture Voiture;
	
	//à généraliser pour n'importe quel processus de voiture
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

		//Affichage des temps
		printf("Voiture n°%d :\t", Voiture.numero);
		printf("%s\t",timeFormat(new_s1));
		printf("%s\t",timeFormat(new_s2));
		printf("%s\t",timeFormat(new_s3));
		printf("%s\n", timeFormat(new_tour));

		//Affichage des Meilleur temps
		printf("MEILLEURS TEMPS : %s\t",timeFormat(Voiture.best_s1));
		printf("%s\t",timeFormat(Voiture.best_s2));
		printf("%s\t",timeFormat(Voiture.best_s3));
		printf("%s\n", timeFormat(Voiture.best_tour));
		printf("TEMPS TOTAL : %s\n\n", timeFormat(Voiture.total_tour));
	}
}

void father_process(int child_pid){
	//Recevoir les infos des processus fils (voitures) et les stocker
}

