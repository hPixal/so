#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

int main() {
    int fd[2];  // fd[0] is read end, fd[1] is write end

    if (pipe(fd) == -1) {
        perror("pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process

        char buffer[128];
        ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';  // Null-terminate

        std::cout << "[Child] Received: " << buffer << std::endl;
        close(fd[0]);

        const char *msg = "Hello from Child!";
        write(fd[1], msg, strlen(msg));
        close(fd[1]);
    } else {
        // Parent process
        const char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));

        close(fd[1]);  // Signal EOF to child

        wait(NULL);

        char buffer[128];
        ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';  // Null-terminate

        std::cout << "[Parent] Received: " << buffer << std::endl;
        close(fd[0]);
    }

    return 0;
}