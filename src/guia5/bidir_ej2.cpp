#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <sys/wait.h>

const int SIZE = 1024;

int main()
{
    key_t key = ftok("shmfile", 65);
    int shmID = shmget(key, SIZE, IPC_CREAT | 0666);
    if (shmID == -1) {
        perror("shmget failed");
        return 1;
    }

    char *shared = (char *)shmat(shmID, nullptr, 0);
    if (shared == (char *)-1) {
        perror("shmat failed");
        return 1;
    }

    memset(shared, 0, SIZE);

    char *child_msg = shared;             
    char *parent_msg = shared + 512;

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        std::string input;
        std::cout << "[Child] Say something to parent: ";
        std::getline(std::cin, input);
        strncpy(child_msg, input.c_str(), 511);  // Write to child_msg area

        // Wait for parent to respond
        while (parent_msg[0] == '\0')
        {
            usleep(1000);  // Sleep 1ms
        }

        std::cout << "[Child] Got from parent: " << parent_msg << std::endl;

        shmdt(shared);
    }
    else
    {
        // Parent process

        while (child_msg[0] == '\0')
        {
            usleep(1000);  // Sleep 1ms
        }

        std::cout << "[Parent] Got from child: " << child_msg << std::endl;

        std::string response;
        std::cout << "[Parent] Say something to child: ";
        std::getline(std::cin, response);
        strncpy(parent_msg, response.c_str(), 511); // Write to parent_msg

        // Let child read, then clean up
        sleep(1);
        shmdt(shared);
        shmctl(shmID, IPC_RMID, NULL);
    }

    return 0;
}
