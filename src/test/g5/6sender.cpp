#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <cstring>

using namespace std;

int main()
{
    const char * fifopath = "fifo";
    char buffer[255];

    if (mkfifo(fifopath, 0777) < 0)
    {   perror("mkfifo");
        exit(EXIT_FAILURE); }

    int fd = open(fifopath, O_WRONLY);
    if (fd = -1)
    {   perror("open");
        exit(EXIT_FAILURE); }
    
    string message = "Hello World!";
    write(fd,message.c_str(),strlen(message.c_str())+1);

    close(fd);
    return 0;
}