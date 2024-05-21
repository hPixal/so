#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <cstring>
#define SHMKEY 75

struct Message {
    long type;
    char text[100];
};

using namespace std;

int main(){
    int shmid,amount = 2;
    Message* messages;
    

    auto totalsize = sizeof(Message)*amount;
    shmid = shmget(SHMKEY,totalsize, 0777); /* Crear la región de memoria y obtener la dirección */

    if (shmid == -1) {
        perror("Failed to create shared memory space");
        exit(1);
    }

    messages = (Message *)shmat(shmid, 0, 0); 


    for (int i=0; i<amount; i++) 
        cout << messages[i].text << endl;
    
	printf("\nWriting operations have ended\n");

	shmdt((void *) messages); 
	printf("\nSHMID: %d \n",shmid);
	
    shmctl (shmid, IPC_RMID, 0);
    
    return 0;

}
