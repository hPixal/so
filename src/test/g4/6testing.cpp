#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <tuple>
using namespace std;

vector<pthread_t> threadIds;

float** initializeMatrix(int rows, int cols, float value) {
    float** matrix = new float*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new float[cols];
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = value;
        }
    }
    return matrix;
}

tuple<float**, int, int> manualMatrixSetUp(){
    int length = 0; 
    int width = 0;

    cout << "Enter length: ";
    cin >> length;
    cout << "Enter width: ";
    cin >> width;  

    float** mymatrix = initializeMatrix(length, width, 5.0);

    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            cout << "Enter value for : " << i << " " << j << ": ";
            cin >> mymatrix[i][j];
        }
    }

    return make_tuple(mymatrix, length, width);
}

void displayMatrix(float** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

float** multiplyMatrices(float** matrix1, float** matrix2, int rows, int cols) {
    float** result = initializeMatrix(rows, cols, 0.0);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0.0;
            for (int k = 0; k < cols; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return result;
}

void* parseThread(void *args) {
    cout << "STARTING PARSE THREAD" << endl;
    int *data = (int *)args;
    
    return nullptr;
}


void test(){
    float** matrix1;
    float** matrix2;
    int rows1, cols1, rows2, cols2;
    tie(matrix1, rows1, cols1) = manualMatrixSetUp();
    
    tie(matrix2, rows2, cols2) = manualMatrixSetUp();
    float** matrix = multiplyMatrices(matrix1, matrix2, rows1, cols1);

    displayMatrix( matrix, rows1, cols1 );
}

int main(int argc, char *argv[]) {

    test();


    return 0;
}