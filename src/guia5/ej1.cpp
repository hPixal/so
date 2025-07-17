#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sstream>
#include <cstring>
#include <sys/wait.h>

// Declare a constant buffer size
const int SIZE = 1024;

int main()
{
    // Generate a key for secure communication
    key_t key = ftok("shmfile", 65);

    // Create a shared memory (shm) and retrieve it's ID
    int shmID = shmget(key, SIZE, IPC_CREAT | 0666);

    // Attach the shared memory space to a variable
    char *str = (char *)shmat(shmID, nullptr, 0);
    memset(str, 0, SIZE);

    pid_t pid = fork();

    if (pid == 0)
    {
        // Child process
        std::stringstream ss;

        for (size_t i = 0; i < 10; i++)
        {
            int newNum = rand() % 101;     // rand 0 to 100
            ss << "| " << newNum << " | "; // concat
        }
        ss << std::endl;
        std::cout << "Child wrote : " << ss.str();
        strcat(str, ss.str().c_str());

        // After everything is done, detach shared memory space
        shmdt(str);
    }
    else
    {
        // Father process

        // Wait for child to finish
        wait(NULL); 
        
        std::cout << "Parent Read: " << str << "\n";
        
        // After everything is done, detach shared memory space
        shmdt(str);

        // Destroy shared memory space
        shmctl(shmID, IPC_RMID, NULL); // Destroy
    }

    return 0;
}