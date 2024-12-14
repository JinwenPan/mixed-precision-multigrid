#include <iostream>
#include <chrono>
#include <random>
#include <cstdio>
#include "papi.h"

template<typename T>
void perform_matrix_multiplication(int n, int blockSize) {
    
    T* A = new T[n * n];
    T* B = new T[n * n];
    T* C = new T[n * n];

    // Initialize matrices A and B with random values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(0.0, 1.0);

    for (int i = 0; i < n * n; i++) {
        A[i] = dist(gen);
        B[i] = dist(gen);
        C[i] = 0;
    }

    // Perform matrix multiplication with loop blocking
    
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i += blockSize) {
        for (int j = 0; j < n; j += blockSize) {
            for (int k = 0; k < n; k += blockSize) {
                for (int ii = i; ii < std::min(i + blockSize, n); ++ii) {
                    for (int jj = j; jj < std::min(j + blockSize, n); ++jj) {
                        for (int kk = k; kk < std::min(k + blockSize, n); ++kk) {
                            C[ii * n + jj] += A[ii * n + kk] * B[kk * n + jj];
                        }
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Matrix size: " << n << "*" << n << std::endl;
    std::cout << "Time taken: " << duration.count() << " microseconds." << std::endl;
    
    delete[] A;
    delete[] B;
    delete[] C;
}

int main(int argc, char* argv[]) {
    
    // check arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " [matrix size] [data type identifier] [block size]" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    int dataType = std::atoi(argv[2]);
    int blockSize = std::atoi(argv[3]);

    if (n <= 0 || blockSize <=0 || n < blockSize) {
        std::cerr << "Invalid matrix and block size. Please enter positive integers and matrix size should be larger." << std::endl;
        return 1;
    }

    // papi things
	int retval;
    int regionID = 0;
    char test[5];
    sprintf(test, "%d", regionID);

	retval = PAPI_library_init(PAPI_VER_CURRENT);
	if (retval != PAPI_VER_CURRENT) {
        std::cerr << "Failed to initialize PAPI library" << std::endl;
        return 1;
    }

    std::cout << "===============================================" <<std::endl;

    retval = PAPI_hl_region_begin(test);
    if ( retval != PAPI_OK ) {
        std::cerr << "Begin Error"<< std::endl;
        return 1;
    }

    switch (dataType) {
        case 1:
            std::cout << "Precision: float" << std::endl;
            perform_matrix_multiplication<float>(n, blockSize);
            break;
        case 2:
            std::cout << "Precision: double" << std::endl;
            perform_matrix_multiplication<double>(n, blockSize);
            break;
        case 3:
            std::cout << "Precision: long double" << std::endl;
            perform_matrix_multiplication<long double>(n, blockSize);
            break;
        default:
            std::cerr << "Invalid datatype. Please choose 1 for float, 2 for double, or 3 for long double." << std::endl;
            return 1;
    }

    retval = PAPI_hl_region_end(test);
    if ( retval != PAPI_OK ) {
        std::cerr << "End Error"<< std::endl;
        return 1;
    }

    return 0;
}
