#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
using namespace std;

void* thread_func(void* arg) {
    std::cout << "Hello from thread!" << std::endl;
    return nullptr;
}

void* thread_count(void* arg){
    for (int i = 0; i < 10; i++)
    {
       std::cout << "Counting : " << i << std::endl;
    }
    pthread_exit(nullptr);
}

void* thread_abc(void* arg){
    for (int i = 65; i < 75; i++)
    {
       std::cout << "Letter : " << static_cast<char>(i) << std::endl;
    }
    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    pthread_t thread1;
    pthread_t thread2;

    pthread_create(&thread2, nullptr, thread_abc, nullptr);
    pthread_create(&thread1, nullptr, thread_count, nullptr);
    
    pthread_join(thread1, nullptr);
    pthread_join(thread2, nullptr);
    std::cout << "Thread finished." << std::endl;
    return 0;
}