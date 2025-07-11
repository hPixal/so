#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
using namespace std;

void hello()
{
    std::cout << "Sistemas Operativos" << std::endl;
    sleep(10);
}

int main(int argc, char *argv[])
{
    pid_t pid;
    

    for (size_t i = 0; i < 4; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            /* Hijo */
            hello();
            break;
        }
        else if (pid > 0)
        {
            /* Padre */
            hello();
        }
    }

    return 0;
}