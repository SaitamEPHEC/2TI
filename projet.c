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

char* timeFormat(){
	int randomNumber = rand() %20000+30000; 
	int minutes = randomNumber % 60000;
	//printf("MINUTES : %d", minutes);
	randomNumber -= minutes*60000;
	int secondes = randomNumber % 1000;
	
	randomNumber -= secondes*1000;
	int millisecondes = randomNumber; 
	char minutesChar[30];
	char secondesChar[10];
	char millisecondesChar[10];
	sprintf(minutesChar,"%d : ",minutes);
	//printf("MINUTES : %s",minutesChar);
	sprintf(secondesChar,"%d : ",secondes);
	//printf("SECONDES : %s",secondesChar);
	sprintf(millisecondesChar,"%d : ",millisecondes);
	//printf("MILLISECONDES : %s",millisecondesChar);
	strcat(minutesChar,secondesChar);
	strcat(minutesChar,millisecondesChar);  
	printf("AFFICHER : %s",minutesChar);
	return minutesChar; 
}

int main(int argc, char *argv[]){
	getRandomSeed();
	printf("Le temps de la voiture est de : %s\n", timeFormat());
	return 0;
}


