#include <stdio.h>
#include <unistd.h>
#include <unistdio.h>
#include <sys/types.h>

int main(){
    fork();
    fork();
    fork();
    printf("Hello World\n");
    auto pid = getpid();
    printf("PID %d\n", pid);
    return  0;
}