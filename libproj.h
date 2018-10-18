#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>


//#define int KEy_SHM = 69;



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
