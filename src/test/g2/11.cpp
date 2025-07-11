#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
using namespace std;

int main( int argc, char *argv[] ) {


    auto n = 1;
    cout << "Ingrese el n deseado: ";
    cin >> n;
    pid_t pid;
    
    for (size_t i = 0; i < n; i++)
    {
        pid = fork();
        if (pid == 0)
        {
            cout << "Hijo: " << i << endl;
            sleep(1);
            return 0;
        }
        else if ( pid > 0 )
        {
            cout << "Padre: " << i << endl;
            sleep(1);
        }
    }
    

    return 0;
}