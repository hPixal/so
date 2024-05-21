#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
using namespace std;

int counter = 0;

struct ThreadData
{
    string StringValue;
    int IntegerValue;
    float FloatValue;
};

void *threadFunc1(void *arg)
{
    ThreadData *data = (ThreadData *)arg;
    counter++;
    std::cout << "Integer: " << data->IntegerValue
              << " String: " << data->StringValue
              << " Float: " << data->FloatValue
              << " Count: " << counter
              << std::endl;
    sleep(1);
    pthread_exit(NULL);
}
void *threadFunc2(void *arg)
{
    int *data = (int *)arg;
    counter++;
    std::cout << "Integer: " << *data << " Count: " << counter <<std::endl;
    sleep(1);
    pthread_exit(NULL);
}
void *threadFunc3(void *arg)
{
    float *data = (float *)arg;
    counter++;
    std::cout << "Float: " << *data << " Count: " << counter << std::endl;
    sleep(1);
    pthread_exit(NULL);
}

int main()
{
    vector<pthread_t> threadIds;
    pthread_t threadId1;
    pthread_t threadId2;
    pthread_t threadId3;
    ThreadData data = {"Hello, Thread!", 1, 10.34};

    pthread_create(&threadId3, NULL, threadFunc1, &data);
    threadIds.push_back(threadId3);
    pthread_create(&threadId1, NULL, threadFunc2, &data.IntegerValue);
    threadIds.push_back(threadId1);
    pthread_create(&threadId2, NULL, threadFunc3, &data.FloatValue);
    threadIds.push_back(threadId2);

    pthread_join(threadId1, NULL);
    pthread_join(threadId2, NULL);
    pthread_join(threadId3, NULL);

    return 0;
}