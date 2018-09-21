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

double getRandomNumber(){
	 srand(getMicrotime());
}

char timeFormat(){
	int randomNumber = rand() %20000+30000; 
	int minutes = (randomNumber % 60000);
	randomNumber -= minutes*60000;
	int secondes = (randomNumber % 1000);
	randomNumber -= secondes*1000;
	int millisecondes = randomNumber; 
	char minutesChar[10];
	char secondesChar[10];
	char millisecondesChar[10];
	sprintf(minutesChar,"%d",minutes);
	sprintf(secondesChar,"%d",secondes);
	sprintf(millisecondesChar,"%d",millisecondes);
	char str[30] =  minutesChar + " : " + secondesChar + " : " + millisecondesChar;
	return str; 
}
int main(int argc, char *argv[]){
	getRandomNumber();
	printf("Le nombre randoM est %d\n",rand() %20000+30000);
	return 0;
}


