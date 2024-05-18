#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    pid_t pid;
    int i;

    pid = fork();
    if (pid == 0)
    {
        for (size_t i = 0; i < 10; i++)
        {
            printf("Hijo: %d\n", i);
            sleep(1);
        }
        return 0;
    }
    else if ( pid > 0 )
    {
        for (size_t i = 0; i < 8; i++)
        {
            printf("Padre: %d\n", i);
            sleep(1);
        }
        return 0;
    }else
    {
        printf("Error al crear el proceso\n");
        return -1;
    }
    wait( NULL );
    

    return 0;
}