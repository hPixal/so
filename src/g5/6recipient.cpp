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

    // if (mkfifo(fifopath, 0777) < 0)
    // {   perror("mkfifo");
    //     exit(EXIT_FAILURE); }

    int fd = open(fifopath, O_WRONLY);
    if (fd < 0)
    {   perror("open");
        exit(EXIT_FAILURE); }
        
    ssize_t bytesread = read(fd,buffer,strlen(buffer));

    if (bytesread == -1) 
    {   perror("read");
        exit(EXIT_FAILURE); }

    buffer[bytesread] = '\0';
    cout << "Child received: " << buffer << endl;

    close(fd);
    return 0;
}