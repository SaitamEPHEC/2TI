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
	return srand(getMicrotime());
}

int main(int argc, char *argv[]){
//	int r = rand() % 20; // nbr random entre 0 et 19
//	r += 30; // nbr random entre 30 et 49
	getRandomNumber();
	printf("Le nombre randoM est %d\n",rand() %100);
	printf("Le nombre randoM est %d\n",rand() %100);
	printf("Le nombre randoM est %d\n",rand() %100);
	return 0;
}


