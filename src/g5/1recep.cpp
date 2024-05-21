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
	int shmid, i, CANTIDAD = 10, TamanioMem;
	int *valores;
    
	TamanioMem = sizeof(*valores)*CANTIDAD;
	shmid = shmget (SHMKEY, CANTIDAD*sizeof(int), 0777); /* Obtener dirección de la región de memoria */
	
	valores =(int *) shmat (shmid, 0, 0); /* Enlazar región al espacio de direccionamiento del proceso */
	
	for(i=0; i<CANTIDAD; i++) 
		printf("\n%d", valores[i] );
	
	
	printf("\nLectura de memoria finalizada\n");
	shmdt((void *) valores); /* Separar la región del espacio de direccionamiento del proceso */
	shmctl (shmid, IPC_RMID, 0); /* Eliminar la región de memoria ocupada */
	return 0;
}
