#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    
    unsigned int i,j,a,v[50000];
    for (i = 0; i < 50000; i++)
    {
        v[i] = i;
    }
    
    printf("\n INICIO \n");
    for (i = 0; i < 50000; i++){
        for ( j = i+1 ; j < 50000; j++){
            if (v[i] > v[j]){
                a = v[i];
                v[i] = v[j];
                v[j] = a;
            }
        }
    }
    printf("\n ordenamiento terminado \n");
    execlp("ls", "ls", "-l", NULL);

    return 0;
}