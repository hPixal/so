#include <iostream>
#include <pthread.h>
#include <vector>
#include <cstdlib>

using namespace std;

class matrix {
    int rows;
    int cols;
    float **m;

public:
    matrix(int rows, int cols, float **m) {
        this->rows = rows;
        this->cols = cols;
        this->m = m;
    }

    matrix(int rows, int cols) {
        this->rows = rows;
        this->cols = cols;
        this->m = new float*[rows];
        for (int i = 0; i < rows; i++) {
            this->m[i] = new float[cols];
            for (int j = 0; j < cols; j++) {
                this->m[i][j] = 0.0;
            }
        }
    }

    float** getMatrix() {
        return m;
    }

    void setMatrix(float **m) {
        this->m = m;
    }

    int getRows() {
        return rows;
    }

    int getCols() {
        return cols;
    }

    void displayMatrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
    }

    void operator=(const matrix &other) {
        this->rows = other.rows;
        this->cols = other.cols;
        this->m = new float*[rows];
        for (int i = 0; i < rows; i++) {
            this->m[i] = new float[cols];
            for (int j = 0; j < cols; j++) {
                this->m[i][j] = other.m[i][j];
            }
        }
    }

    void operator+(matrix &other) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this->m[i][j] += other.m[i][j];
            }
        }
    }

    void operator-(matrix &other) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                this->m[i][j] -= other.m[i][j];
            }
        }
    }

    float* operator[](int i) {
        return m[i];
    }

    matrix operator*(matrix &other) {
        if (this->cols != other.rows) {
            throw invalid_argument("Matrix dimensions do not match for multiplication.");
        }

        // Allocate the result matrix
        float **result = new float*[rows];
        for (int i = 0; i < rows; i++) {
            result[i] = new float[other.cols];
        }

        // Create a thread for each element in the result matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                pthread_t threadId;
                threadData *data = new threadData{this, &other, result, i, j};

                pthread_create(&threadId, NULL, getElem, data);
                threadIds.push_back(threadId);
            }
        }

        // Join all the threads
        for (pthread_t &threadId : threadIds) {
            pthread_join(threadId, NULL);
        }

        return matrix(rows, other.cols, result);

    }

    void manualMatrixSetup() {
        cout << "Enter amount of rows: ";
        cin >> rows;
        cout << "Enter amount of columns: ";
        cin >> cols;

        m = new float*[rows];
        for (int i = 0; i < rows; i++) {
            m[i] = new float[cols];
            for (int j = 0; j < cols; j++) {
                cout << "Enter value for : " << i << " " << j << ": ";
                cin >> m[i][j];
            }
        }
    }

    ~matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] m[i];
        }
        delete[] m;
    }

private:
    vector<pthread_t> threadIds;

    struct threadData {
        matrix *self;
        matrix *other;
        float **result;
        int rownum;
        int colnum;
    };

    static void* getElem(void *arg) {
        threadData *data = static_cast<threadData*>(arg);

        int rownum = data->rownum;
        int colnum = data->colnum;

        matrix *self = data->self;
        matrix *other = data->other;
        float sum = 0;

        for (int k = 0; k < self->cols; k++) {
            sum += self->m[rownum][k] * other->m[k][colnum];
        }

        data->result[rownum][colnum] = sum;
        delete data;
        pthread_exit(NULL);
    }
};

int main() {
    
    matrix m1(3, 3);
    matrix m2(3, 3);
    m1.manualMatrixSetup();
    m2.manualMatrixSetup();
    auto m3 = m1 * m2;

    m3.displayMatrix(); 
    return 0;
}
