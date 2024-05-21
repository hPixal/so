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

    if (pipe(pipefd) == -1)
    {   perror("Failed to create pipe");
        exit(EXIT_FAILURE); }

    pid_t pid = fork();

    if (pid == -1)
    {   perror("Failed to create child process");
        exit(EXIT_FAILURE); }

    if (pid == 0)
    {
        // Child process
        close(pipefd[1]); // Close write end of the pipe

        char buffer[255];
        ssize_t count = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (count == -1)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        buffer[count] = '\0'; // Null-terminate the string
        cout << "Child received: " << buffer << endl;

        close(pipefd[0]); // Close the read end of the pipe
    }
    else
    {
        close(pipefd[0]); // Close the read end of the pipe

        const char *message = "Hello from parent!";
        write(pipefd[1], message, strlen(message));

        close(pipefd[1]); // Close the write end of the pipe

        wait(NULL); // Wait for the child process to finish
    }

    return 0;
}