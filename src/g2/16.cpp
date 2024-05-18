#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;


int main()
{
    int i;
    printf("INICIO \n");
    for (i = 0; i < 4; i++)
        if (fork() == 0)
            break;
    sleep(5);
    printf("FIN \n");
    wait(nullptr);
    return 0;
}