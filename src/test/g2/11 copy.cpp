#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {
    int n;
    cout << "Ingrese el n deseado: ";
    cin >> n;
    
    for (size_t i = 0; i < n; i++)
    {
        fork();
    }
    
    printf("FICH \n");

    return 0;
}