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
        close(fd[1]);  // Close write end

        char buffer[128];
        ssize_t bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';  // Null-terminate

        std::cout << "[Child] Received: " << buffer << std::endl;
        close(fd[0]);
    } else {
        // Parent process
        close(fd[0]);  // Close read end

        const char *msg = "Hello from parent!";
        write(fd[1], msg, strlen(msg));

        close(fd[1]);  // Signal EOF to child
        wait(NULL);
    }

    return 0;
}