#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>

const int SIZE = 1024;

int main() {
    key_t key = ftok("shmfile", 65); // Generate unique key
    int shmid = shmget(key, SIZE, 0666 | IPC_CREAT); // Create shared memory

    char* str = (char*) shmat(shmid, (void*)0, 0); // Attach to address space

    pid_t pid = fork();

    if (pid == 0) {
        std::strcpy(str, "Hello from child using SysV");
        std::cout << "[Child] Wrote message\n";
        shmdt(str); // Detach
    } else {
        wait(NULL);
        std::cout << "[Parent] Read: " << str << "\n";
        shmdt(str);
        shmctl(shmid, IPC_RMID, NULL); // Destroy
    }

    return 0;
}
