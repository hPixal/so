
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <tuple>
#include <iostream>
using namespace std;

struct nn_matrix
{
    int **matrix; // int [] [] matrix size n
    size_t n;     // size n
};

struct row_sum_args
{
    int *row1;
    int *row2;
    size_t size;
};

float factorial(int num, float accum = 1)
{
    if (num == 0)
        return accum;
    accum *= num;
    return factorial(num - 1, accum);
}

void nn_mx_row_sum(int *row1, int *row2, size_t size)
{
    // Pointers
    int *p1 = row1;
    int *p2 = row2;

    // Result will be in row matrix  1
    for (size_t i = 0; i < size; i++)
    {
        *p1 = *p1 + *p2;
        p1++;
        p2++;
    }
}

void *thread_2_nn_matrix_row_sum(void *arg)
{
    row_sum_args *args = static_cast<row_sum_args *>(arg);
    nn_mx_row_sum(args->row1, args->row2, args->size);
    delete args; // liberar memoria del struct
    pthread_exit(nullptr);
}

void *thread_2_nn_matrix_sum(void *arg)
{
    // ARGS

    // void* arg must be a nn_matrix* arr[2]
    nn_matrix m1 = *(nn_matrix *)arg;       // arr[0]
    nn_matrix m2 = *((nn_matrix *)arg + 1); // arr[1]

    int n = static_cast<int>(m1.n);

    // DEBUG
    std::cout << m1.matrix[0][0] << ' ' << m2.matrix[n - 1][n - 1] << std::endl;

    if (n == m2.n)
    {
        pthread_t threads[n];

        for (size_t i = 0; i < n; i++)
        {
            row_sum_args *args = new row_sum_args;
            args->row1 = m1.matrix[i];
            args->row2 = m2.matrix[i];
            args->size = n;
            pthread_create(&threads[i], nullptr, thread_2_nn_matrix_row_sum, args);
        }

        for (size_t i = 0; i < n; i++)
        {
            pthread_join(threads[i], nullptr);
        }
    }
    else
    {
        std::cout << "Size mismatch" << std::endl;
        pthread_exit(nullptr);
    }
    pthread_exit(nullptr);
}

int main(int argc, char *argv[])
{
    size_t n = 3;

    // Matrix 1 declaration.
    int **matrix1 = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        matrix1[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            matrix1[i][j] = i * n + j + 1; // Fill with values
        }
    }

    // Matrix 2 declaration.
    int **matrix2 = new int *[n];
    for (int i = 0; i < n; ++i)
    {
        matrix2[i] = new int[n];
        for (int j = 0; j < n; ++j)
        {
            matrix2[i][j] = i * n + j + 1; // Fill with values
        }
    }

    // Set up N by N Matrix struct
    nn_matrix m1;
    m1.matrix = matrix1;
    m1.n = n;

    nn_matrix m2;
    m2.matrix = matrix2;
    m2.n = n;

    std::cout << "Comienzo del Thread de Matrices" << std::endl;

    nn_matrix send[2];
    send[0] = m1;
    send[1] = m2;

    pthread_t thread;
    pthread_create(&thread, nullptr, thread_2_nn_matrix_sum, &send);
    pthread_join(thread, nullptr);

    std::cout << "Resultado de la suma de matrices (m1):" << std::endl;
    for (size_t i = 0; i < m1.n; ++i)
    {
        for (size_t j = 0; j < m1.n; ++j)
        {
            std::cout << m1.matrix[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "Finish." << std::endl;
    return 0;
}
