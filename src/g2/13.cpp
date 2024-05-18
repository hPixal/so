#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    pid_t pid;
    int i;
    int padre = 1;
    for ( i = 0 ; i < 3 ; i++ ) {
        if (padre == 1) {
            if (fork() == 0) {
                printf("Hijo: %d Padre: %d\n", getpid(),getppid());   
                padre = 0;
            }
            else
            {
                printf("Padre: %d\n", getpid());
                padre = 1;
            }
        }       
        sleep(1);
    }
    return 0;
}