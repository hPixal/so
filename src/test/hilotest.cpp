#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct ThreadData {
    int arg1;
    std::string arg2;
};

int suma = 0;

void* thread1(void* args){
    vector<int>* v = static_cast<vector<int>*>(args);
    for(int i = 0; i < (static_cast<int>(v->size())/2); i++ ){
        suma = suma + v->at(i);
    }
    pthread_exit(NULL); 
}

void* thread2(void* args){
    vector<int>* v = static_cast<vector<int>*>(args);
    for(int i = (static_cast<int>(v->size())/2); i < v->size(); i++ ){
        suma = suma + v->at(i);
    }
    pthread_exit(NULL); 
}


int main(){
    vector<int>* v;
    for(int i = 0; i < 11; i++ ){
        v->push_back(1);
    }

    pthread_t t1,t2;
    pthread_create(&t1,NULL,thread1,v);
    pthread_create(&t2,NULL,thread2,v);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    cout << suma << endl;
    return 0;
}
