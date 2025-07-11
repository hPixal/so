
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <tuple>
#include <iostream>
using namespace std;

struct matrix_nn
{
    int **m;
    int n; // size

    matrix_nn(size_t n)
    {
        this->n = n;
        this->m = new int *[n];
        ;
        this->fill();
    }

    void fill(int z)
    {
        for (size_t i = 0; i < this->n; i++)
        {
            auto arr = new int[this->n];
            for (size_t j = 0; j < this->n; j++)
            {
                arr[j] = z;
            }
            this->m[i] = arr;
        }
    }

    void fill()
    {
        int val = 0;
        for (size_t i = 0; i < this->n; i++)
        {
            auto arr = new int[this->n];
            for (size_t j = 0; j < this->n; j++)
            {
                arr[j] = val;
                val++;
            }
            this->m[i] = arr;
        }
    }

    void display()
    {
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                std::cout << " m[" << i + 1 << "][" << j + 1 << "]: " << this->m[i][j] << ' ';
            }
            std::cout << std::endl;
        }
    }
};

struct ThreadArgs
{
    int row;
    matrix_nn *A;
    matrix_nn *B;
    matrix_nn *C;
};

// Multiplica la fila `row` de A por cada columna de B
void *multiply_row(void *arg)
{
    ThreadArgs *args = (ThreadArgs *)arg;
    int n = args->A->n;
    int i = args->row;

    for (int j = 0; j < n; j++)
    {
        args->C->m[i][j] = 0;
        for (int k = 0; k < n; k++)
        {
            args->C->m[i][j] += args->A->m[i][k] * args->B->m[k][j];
        }
    }

    pthread_exit(nullptr);
}


int main()
{
    const int n = 3;

    matrix_nn A(n), B(n), C(n);
    A.fill();      // valores incrementales
    B.fill(1);     // llena con unos
    C.fill(0);     // limpia

    pthread_t threads[n];
    ThreadArgs args[n];

    for (int i = 0; i < n; i++)
    {
        args[i] = {i, &A, &B, &C};
        pthread_create(&threads[i], nullptr, multiply_row, &args[i]);
    }

    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], nullptr);
    }

    cout << "Matriz A:\n";
    A.display();

    cout << "\nMatriz B:\n";
    B.display();

    cout << "\nResultado A * B:\n";
    C.display();

    return 0;
}