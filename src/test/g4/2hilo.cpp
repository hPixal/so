#include <stdio.h>
#include <pthread.h>
#include <stdlib.h> 
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;
int a=0;
void* hilo(void*)
{	cout<<++a<<") Sistemas Operativos\n";
sleep(3);
pthread_exit(NULL);
}

int main()
{	pthread_t t[8];
for(int i=0;i<8;i++) { 
	pthread_create(&t[i],NULL,hilo,NULL);
}

for(int i=0;i<8;i++) { 
	pthread_join(t[i],NULL);
}
return 0;
}