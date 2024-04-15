#include <stdio.h>
#include <unistd.h>
#include <unistdio.h>
#include <sys/types.h>

int main()
{
    pid_t pid; size_t size = 50000;
    unsigned int i, j, a, v[size];
    for (i = 0; i < size; i++)
    {
        v[i] = i * i;
    }

    pid = fork();


    printf("PID %d\n", getpid());


    if (pid == 0)
    {
        printf("Inicio\n");
        for (i = 0; i < size; i++)
        {
            for (j = i + 1; j < size; j++)
            {
                if (v[i] > v[j])
                {
                    a = v[i];
                    v[i] = v[j];
                    v[j] = a;
                }
            }
        }
        printf("Ordenado terminado! \n");
    }else{
        execlp("/bin/ls", "ls", NULL);
    }

    return 0;
}