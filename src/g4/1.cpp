#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

using namespace std;

void* numbersThread(void* args){
    cout << "STARTING NUMBERS THREAD" << endl;
    for (int i = 0; i < 11; i++){
        cout << i << endl;
        //sleep(1);
    }
    return nullptr;
}

void* charThread(void* args){
    cout << "STARTING CHAR THREAD" << endl;
    for (int i = 0; i < 11; i++){
        sleep(1);
        cout << char('a'+i) << endl;
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, numbersThread, NULL);
    pthread_create(&t2, NULL, charThread, NULL);
    pthread_join(t1, NULL);
    //pthread_join(t2, NULL);

    cout << "FINISHED" << endl;
    return 0;
}