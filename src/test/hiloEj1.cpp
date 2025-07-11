#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

using namespace std;

int suma = 0;

void* thread1(void*){
    for(char i = 'a'; i < 'z'+1; i++){
        cout << i;
    }
    cout << '\n';
    pthread_exit(NULL);     
}

void* thread2(void*){
    for(int i = 0; i < 11; i++ ){
        cout << i;
    }
    cout << '\n';
    pthread_exit(NULL);
}

int main(){
    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,NULL);
    pthread_create(&t2,NULL,thread2,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
