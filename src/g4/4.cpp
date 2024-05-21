#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
using namespace std;

vector<pthread_t> threadIds;

void factorial(int n) {
    int fact = 1;
    cout << " TEST: " << n << endl;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    
    cout << "Factorial of " << n << " is " << fact << endl;
}

void displayArguments(int argc, char *argv[]) {
    cout << "Argc : " << argc << endl; 
    for (int i = 0; i < argc; i++) {
        cout << "Parameter number " << i << ": " << argv[i] << endl;
    }
}

void* parseThread(void* args) {
    cout << "STARTING PARSE THREAD" << endl;
    int *data = (int *)args;
    factorial(*data);
    return nullptr;
}


void operateInThreads(int argc, char *argv[]) {
    for (size_t i = 1; i < argc; i++)
    {
        pthread_t threadId;
        auto aux = atoi(argv[i]);
        pthread_create(&threadId, NULL,parseThread, &aux);
        threadIds.push_back(threadId);
    }


    for (size_t i = 0; i < threadIds.size(); i++)
    {
        pthread_join(threadIds[i], NULL);
    }
}

void normalOperation(int argc, char *argv[]) {
    for (size_t i = 1; i < argc; i++)
    {
        auto aux = atoi(argv[i]);
        factorial(aux);
    }
}


int main(int argc, char *argv[]) {
    displayArguments(argc, argv);
    operateInThreads(argc, argv);
    //normalOperation(argc, argv);


    return 0;
}