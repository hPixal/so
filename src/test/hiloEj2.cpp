#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void thread(){
    cout << "Sistemas operativos";
    sleep(10);
}

int main(){
    for(int i = 0; i < 9 ; i++ ){
        fork();
        thread();
    }

    return 0;
}
