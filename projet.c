#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>

struct Voiture {
	int numero;
	long best_s1;
	long best_s2;
	long best_s3;
	long best_tour;
	long total_tour;
};

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

double getRandomSeed(){
	 srand(getMicrotime());
}

long randomNumber(){
	return rand() %10000+40000;
}

char *timeFormat(long NumberToFormat){
	//Récupère les minutes du nombre en arrondissant vers le bas
	long minutes = NumberToFormat/60000;
	NumberToFormat -= minutes*60000;
	//Récupère les secondes du nombre en arrondissant vers le bas
	long secondes = NumberToFormat/1000;
	NumberToFormat -= secondes*1000;
	//Récupère les millisecondes du nombre
	long millisecondes = NumberToFormat; 
	static char minutesChar[30];
	char secondesChar[10];
	char millisecondesChar[10];
	if(minutes < 10){
		sprintf(minutesChar,"0%ld : ",minutes);
	}
	else{
		sprintf(minutesChar,"%ld : ",minutes);
	}
	if(secondes < 10){
		sprintf(secondesChar,"0%ld : ",secondes);
	}
	else{
		sprintf(secondesChar,"%ld : ",secondes);
	}
	if(millisecondes < 100){
		if(millisecondes < 10){
			sprintf(millisecondesChar,"00%ld",millisecondes);
		}
		else{
			sprintf(millisecondesChar,"0%ld",millisecondes);
		}
	}
	else{
		sprintf(millisecondesChar,"%ld",millisecondes);
	}
	strcat(minutesChar,secondesChar);
	strcat(minutesChar,millisecondesChar);
	return minutesChar; 
}



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

		//Simulation P1 ==> 1h30 = 
		while(Voiture.total_tour <= 5400000){
			long new_s1 = randomNumber();
			//update best_s1 si meilleur temps que précédent
			if(Voiture.best_s1 >= new_s1){
				Voiture.best_s1 = new_s1;	
			}
		
			//update best_s2 si meilleur temps que précédent
			long new_s2 = randomNumber();
			if(Voiture.best_s2 >= new_s2){
				Voiture.best_s2 = new_s2;	
			}

			//update best_s3 si meilleur temps que précédent
			long new_s3 = randomNumber();
			if(Voiture.best_s3 >= new_s3){
				Voiture.best_s3 = new_s3;	
			}
		
			long new_tour = new_s1 + new_s2 + new_s3;
			if(Voiture.best_tour >= new_tour){
				Voiture.best_tour = new_tour;
			}

			Voiture.total_tour += new_tour;
			
			/*printf("Voiture n°%d :\t %s\t %s\t %s\t %s\n", Voiture.numero,
			timeFormat(new_s1),timeFormat(new_s2),timeFormat(new_s3),
			timeFormat(new_s1))*/

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


