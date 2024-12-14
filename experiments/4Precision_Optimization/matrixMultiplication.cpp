#include <iostream>
#include <chrono>
#include <random>

template<typename T>
void perform_matrix_multiplication(int n) {
    
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

    // Perform matrix multiplication and timing
    auto start = std::chrono::high_resolution_clock::now();

    // The loops are indepedent and the order can be changed
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i * n + j] += A[i * n + k] * B[k * n + j];
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
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " [matrix size] [data type identifier]" << std::endl;
        return 1;
    }

    int n = std::atoi(argv[1]);
    int dataType = std::atoi(argv[2]);

    if (n <= 0) {
        std::cerr << "Invalid matrix size. Please enter a positive integer." << std::endl;
        return 1;
    }

    std::cout << "===============================================" <<std::endl;

    switch (dataType) {
        case 1:
            std::cout << "Precision: float" << std::endl;
            perform_matrix_multiplication<float>(n);
            break;
        case 2:
            std::cout << "Precision: double" << std::endl;
            perform_matrix_multiplication<double>(n);
            break;
        case 3:
            std::cout << "Precision: long double" << std::endl;
            perform_matrix_multiplication<long double>(n);
            break;
        default:
            std::cerr << "Invalid datatype. Please choose 1 for float, 2 for double, or 3 for long double." << std::endl;
            return 1;
    }

    return 0;
    
}
