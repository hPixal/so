#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <iostream>
#include <wait.h>

using namespace std;

int main()
{
    int pipefd[2]; // Pipe file descriptors
    char buffer[255];
    pid_t pid = fork();

    if (pipe(pipefd) == -1)
    {   perror("Failed to create pipe");
        exit(EXIT_FAILURE); }
    if (pid == -1)
    {   perror("Failed to create child process");
        exit(EXIT_FAILURE); }

    if (pid == 0)
    {
        close(pipefd[0]); 
		close(pipefd[1]); 

        strcpy(buffer, "Hello World! from child");
        write(pipefd[1], buffer, strlen(buffer) + 1);
        cout << "Sent message: " << buffer << endl;

        read(pipefd[0], buffer, sizeof(buffer) - 1);
        cout << "Received message: " << buffer << endl;

        close(pipefd[0]);
        close(pipefd[1]);
    }
    else
    {
        close(pipefd[0]); 
		close(pipefd[1]); 

        strcpy(buffer, "Hello World! from parent");
        write(pipefd[1], buffer, strlen(buffer) + 1);
        cout << "Sent message: " << buffer << endl;

        read(pipefd[0], buffer, sizeof(buffer) - 1);
        cout << "Received message: " << buffer << endl;

        close(pipefd[0]);
        close(pipefd[1]);
    }

    waitpid(pid, NULL, 0);
    return 0;
}