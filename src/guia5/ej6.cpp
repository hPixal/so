#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    // Crear FIFO (solo la primera vez, luego verificar si ya existe)
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("mkfifo");
    }

    pid_t pid = fork();

    if(pid == 0){
        // Child
        int fd = open(FIFO_PATH,O_RDONLY);

        char buffer[128];
        ssize_t n = read(fd, buffer, sizeof(buffer) - 1);
        
        while (buffer[0] == '\0')
        {
            usleep(1000);
        }
        
        if (n > 0) {
            buffer[n] = '\0';
            std::cout << "[Child] Received: " << buffer << std::endl;
        }

        close(fd);

    }else{
        // Father
        int fd = open(FIFO_PATH,O_WRONLY);

        const char *msg = "Hello from Parent!";
        write(fd, msg, strlen(msg));

        close(fd);
    }

    return 0;
}