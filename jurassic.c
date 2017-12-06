#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

sem_t sem_passenger,sem_cars;

void* thread_passenger(void* args)
{
	int n = *((int*)args);
	sem_post(&sem_passenger);
	printf("Passenger %d has entered the park and started roaming\n",n);
	sleep(2);
	//srand(time(NULL));
	int random = rand()%5;
	sleep(random);
	printf("Passenger %d has completed roaming in %d seconds\n",n,random);
	printf("Passenger %d is waiting for a car\n",n);
	sem_wait(&sem_cars);
	printf("Passenger %d started riding the car...\n",n);
	random = rand()%15;
	sleep(random);
	printf("Passenger %d has completed riding the car after %d seconds\n",n,random);
	sem_post(&sem_cars);
}

void* thread_cars(void* args)
{
	int n = *((int*)args);
	sem_post(&sem_cars);
	printf("Car %d is waiting...\n",n);
}

int main()
{
int nPass,nCars;
printf("Enter number of passengers: ");
scanf("%d",&nPass);
printf("Enter number of cars: ");
scanf("%d",&nCars);
pthread_t pass[nPass],cars[nCars];
sem_init(&sem_passenger,0,0);
sem_init(&sem_cars,0,0);
int i=0;
for(i=0;i<nPass;i++)
{
	pthread_create(&pass[i],NULL,thread_passenger,(void *)&i);
}
for(i=0;i<nCars;i++)
{
	pthread_create(&cars[i],NULL,thread_cars,(void *)&i);
}
for(i=0;i<nPass;i++)
{
	pthread_join(pass[i],NULL);
}
printf("All passengers have completed their visit!\n");
}
