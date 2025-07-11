
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <tuple>
#include <iostream>
using namespace std;

float factorial(int num,float accum = 1){
    if(num == 0) return accum;
    accum *= num;
    return factorial(num-1,accum);
}

void* thread_factiorial(void* arg){
    
    // ARGS
    int number = 0; 

    // FAILSAFE
    if(arg == nullptr) pthread_exit(nullptr); 

    // START
    *(int*)arg = factorial(*(int*)arg);

    pthread_exit(nullptr);
}

int main(int argc, char* argv[]) {
    for (size_t i = 0; i < 9; i++)
    {
        int factorialize = i;
        
        std::cout << "Comienzo del Thread de factoriales | Valor: " << factorialize << std::endl;
       
        pthread_t thread;
        pthread_create(&thread, nullptr, thread_factiorial,&factorialize);
        pthread_join(thread,nullptr);
       
        std::cout << "Resultado del thread : " << factorialize << std::endl;
    }
    std::cout << "Finish." << std::endl;
    return 0;
}
