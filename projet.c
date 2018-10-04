#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>

long getMicrotime(){
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
}

double getRandomSeed(){
	 srand(getMicrotime());
}

char *timeFormat(){
	int randomNumber = rand() %20000+30000;
	//Récupère les minutes du nombre en arrondissant vers le bas
	int minutes = randomNumber/60000;
	randomNumber -= minutes*60000;
	//Récupère les secondes du nombre en arrondissant vers le bas
	int secondes = randomNumber / 1000;
	randomNumber -= secondes*1000;
	//Récupère les millisecondes du nombre
	int millisecondes = randomNumber; 
	static char minutesChar[30];
	char secondesChar[10];
	char millisecondesChar[10];
	sprintf(minutesChar,"%d : ",minutes);
	sprintf(secondesChar,"%d : ",secondes);
	sprintf(millisecondesChar,"%d",millisecondes);
	strcat(minutesChar,secondesChar);
	strcat(minutesChar,millisecondesChar);
	return minutesChar; 
}

int main(int argc, char *argv[]){
	getRandomSeed();
	pid_t voiture; 
	voiture = fork();

	void child_process(void){
		//Renvoie 15 fois (15 tours) 3 temps (3 secteurs) : Total 45 temps
	}

	void father_process(int child_pid){
		//Recevoir les infos des processus fils (voitures) et les stocker
	}

	switch(voiture){
	//Si erreur lors du fork
	case -1;
	perror("Erreur de fork");
	return  EXIT_FAILURE;
	break;
	//Si on est dans le fils
	case 0;
	child_process();
	break;
	//Si on est dans le père
	default;
	father_process(pid);
	break;
	}

	printf("Le temps de la voiture est  %s\n", timeFormat());
	return 0;
}


