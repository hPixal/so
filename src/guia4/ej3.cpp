
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <iostream>
using namespace std;


void* thread_hello(void* arg){
    std::cout << "Sistemas Operativos" << std::endl;
    sleep(10);
    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    for (size_t i = 0; i < 3; i++)
    {
        pthread_t thread;
        pthread_create(&thread, nullptr, thread_hello, nullptr);
        pthread_join(thread,nullptr);
    }
    std::cout << "Finish." << std::endl;
    return 0;
}
