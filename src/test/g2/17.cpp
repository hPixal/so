#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    pid_t pid;
    int num;
    for (num = 1; num <= 3; num++) {
        pid = fork();
        if ((num == 3) & (pid == 0) || true) {
            printf("\n");
            execlp("ls", "ls", "-l", NULL);
        }
        wait(nullptr);
    }
    printf("FIN \n");
    return 0;
}