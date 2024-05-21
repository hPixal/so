#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <cstring>
#define SHMKEY 75

using namespace std;

struct dato{
	int sigue;
	int v[10];
};

int main(){
	int shmid, CANTIDAD = 10;
	int *valores;
		
	shmid = shmget (SHMKEY, CANTIDAD*sizeof(int), 0777 | IPC_CREAT); /* Crear la región de memoria y obtener la dirección */
	valores =(int *) shmat (shmid, 0, 0); /* Enlazar región al espacio de direccionamiento del proceso */
	
    for(int i=0; i<CANTIDAD; i++) 
        valores[i] = rand()%100; 	/*Generar los números aleatorios*/

	for (int i=0; i<CANTIDAD; i++) 
        printf("\n%d", valores[i] ); 	/*Escritura en memoria*/
    
	printf("\nEscritura a memoria finalizada\n");

	shmdt((void *) valores); /* Separar la región del espacio de direccionamiento del proceso */
	printf("\nSHMID: %d",shmid);
	return 0;
}