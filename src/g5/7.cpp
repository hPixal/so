#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

using namespace std;

#define MAX_TEXT 512

struct Message {
	long int mtype; 
	char mtext[MAX_TEXT];
};

int main() {
	int flag = 1; char buffer[BUFSIZ];
	struct Message msj; int msgid;
	
	msgid = msgget((key_t)1234, 0777 | IPC_CREAT);
	
	if (msgid == -1) {
		fprintf(stderr, "Se produjo un error al crear la cola de Messages: %d\n", errno);         
		exit(EXIT_FAILURE);
	}
	
	while(flag) {
		printf("Ingrese un texto a enviar -fin para terminar-: "); 
		fgets(buffer, BUFSIZ, stdin); 
		msj.mtype = 1; 
		strcpy(msj.mtext, buffer); 
		
		if (msgsnd(msgid, (void *)&msj, MAX_TEXT, 0) == -1) {          
			fprintf(stderr, "Se produjo un error al eliminar la cola\n");
			exit(EXIT_FAILURE);
		}
		
		if (strncmp(buffer, "fin", 3) == 0) {
			flag = 0;
		}
		
	}
	exit(EXIT_SUCCESS); 
}
