#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    for (int i = 0 ; i < 3 ; i++ )
    {
        if (fork() == 0)
            printf("Proceso %d hijo de %d\n",getpid(),getppid());
        wait(NULL);
    }
    return 0;
}