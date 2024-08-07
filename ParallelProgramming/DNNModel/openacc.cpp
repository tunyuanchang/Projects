#include <iostream>
#include <cstdlib>
#include <string>
#include <utility>
#include <cmath>
#include <chrono>
#include <iomanip>

#include <openacc.h>

#include "mnist/mnist_reader.hpp"

using namespace std;

#define RESULT_FILE "result.txt"
#define MNIST_DATA_LOCATION "/home/pp23/share/lab5/testcases/MNIST"
#define WEIGHT_ROOT "/home/pp23/share/lab5/testcases/weights"

/* Model architecture:
 *  Layer1: 784 x 1024
 *  Layer2: 1024 x 10
 */
#define LAYER0 784
#define LAYER1 1024
#define LAYER2 10

/* https://pytorch.org/docs/stable/generated/torch.nn.Linear.html
 * D := AxB + C
 *
 * A := n*k matrix
 * B := k*m matrix
 * C := m*1 matrix
 */
 
 /* TODO: Parallel the for loops
  * HINT: 1. (a) copy array A, B, C to GPU device
  *          (b) copy array D back to CPU
  *       2. Parallel the loop using
  *          (a) #pragma acc XXX
  *          (b) CUDA kernel function
  */
void LinearLayer(float *A, float *B, float *C, float *D, int n, int k, int m) {
    #pragma acc data copyin(A[0:n*k], B[0:k*m], C[0:m]) copyout(D[0:n*m])
    {
        float sum;
        #pragma acc data present(A, B, C, D)
        #pragma acc kernels
        #pragma acc loop independent
        for (int i = 0; i < n; i++) {
            #pragma acc loop independent
            for (int j = 0; j < m; j++) {
                sum = C[j];
                #pragma acc loop reduction(+: sum)
                for (int a = 0; a < k; a++) {
                    // sum += A[i][a] * B[a][j]
                    sum += A[i * k + a] * B[a * m + j];
                }
                D[i * m + j] = sum;
            }
        }
    }
}

/* https://pytorch.org/docs/stable/generated/torch.nn.Sigmoid.html
 * A := sigmoid(A)
 * A := n*m matrix
 */

/* TODO: Parallel the for loops */
void Sigmoid(float *A, int n, int m) {
    #pragma acc data copy(A[0:n*m])
    {
        #pragma acc data present(A)
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Sigmoid(x) = 1/(1+exp(x))
                A[i * m + j] = 1. / (1. + expf(-A[i * m + j]));
            }
        }
    }
}

/* Argmax: Choose the index with the largest value
 * A := n*m matrix (data type: float)
 * D := n*1 matrix (data type: int)
 */

 /* TODO: Parallel the for loops */
void Argmax(float *A, int *D, int n, int m) {
    #pragma acc data copyin(A[0:n*m]) copyout(D[0:n])
    {
        #pragma acc data present(A, D)
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            float mx = A[i * m];
            int index = 0;
            for (int j = 1; j < m; j++) {
                if (mx < A[i * m + j]) {
                    mx = A[i * m + j];
                    index = j;
                }
            }
            D[i] = index;
        }
    }
}

/* my_nn: A simple neural network
 * Input arrays:
 *     training_images_flat: float[num_images * LAYER0]
 *     layer1_matrix:        float[LAYER0 * LAYER1]
 *     layer1_bias:          float[LAYER1]
 *     layer2_matrix:        float[LAYER1 * LAYER2]
 *     layer2_bias:          float[LAYER2]
 * Output array:
 *     result:               int[num_images]
 */
void my_nn(float *training_images_flat, int num_images,
           float *layer1_matrix, float *layer1_bias, float *layer2_matrix, float *layer2_bias,
           int *result) {
    float *layer1_output = new float[num_images * LAYER1];
    float *layer2_output = new float[num_images * LAYER2];

    // Layer1: Linear layer + Sigmoid (activation function)
    LinearLayer(training_images_flat, layer1_matrix, layer1_bias, layer1_output,
                num_images, LAYER0, LAYER1);
    Sigmoid(layer1_output, num_images, LAYER1);


    // Layer2: Linear layer + Argmax
    LinearLayer(layer1_output, layer2_matrix, layer2_bias, layer2_output,
        num_images, LAYER1, LAYER2);
    Argmax(layer2_output, result, num_images, LAYER2);

    delete [] layer1_output;
    delete [] layer2_output;
}


/////////////////////////////////////////////////////////////////////
//                 NO NOT MODIFY THE CODE BELOW                    //
/////////////////////////////////////////////////////////////////////

/* Read neural network's weight from file (in binary format)
 */
void read_weight(float *array, string filename, int num_floats) {
    string full_filename = string(WEIGHT_ROOT) + '/' + filename;
    std::cout << "Reading file: " << full_filename << std::endl;
    ifstream file(full_filename, ios::in | ios::binary);
    if (!file) {
        std::cerr << "error reading file: " << full_filename << std::endl;
        exit(1);
    }
    file.read((char*)array, num_floats * sizeof(float));
}

/* Write predicted result to file
 */
void write_predict(int *result, int n, string filename) {
    std::ofstream file(filename, std::ofstream::out);
    for (int i = 0; i < n; i++) {
        file << result[i] << '\n';
    }
    file.close();
}

/* Print an image
 * Usage: print_img(training_images[i])
 */
void print_img(float *img) {
    for (int i = 0; i < 28; i++) {
        for (int j = 0; j < 28; j++) {
            if (img[i*28+j] > 0.5) {
                std::cout << 'x';
            }else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

bool InitCUDA(void) {
    int count = 0;

    count =  acc_get_num_devices(acc_device_nvidia);
    if(count == 0) {
        std::cerr << "There is no device.\n";
        return false;
    }

    acc_set_device_num(0, acc_device_nvidia);

    std::cout << "CUDA initialized.\n";
    return true;
}

int main(int argc, char* argv[]) {
    auto initcuda_start = std::chrono::steady_clock::now();
    InitCUDA();
    auto read_start = std::chrono::steady_clock::now();
    // std::cout << "MNIST data directory: " << MNIST_DATA_LOCATION << std::endl;

    /* Load MNIST data
     */
    mnist::MNIST_dataset<std::vector, std::vector<uint8_t>, uint8_t> dataset;
    if (argc == 1) {
        dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(MNIST_DATA_LOCATION);
    }else {
        dataset = mnist::read_dataset<std::vector, std::vector, uint8_t, uint8_t>(argv[1]);
    }

    std::cout << "Nbr of training images = " << dataset.training_images.size() << std::endl;
    // std::cout << "Nbr of training labels = " << dataset.training_labels.size() << std::endl;
    // std::cout << "Nbr of test images = " << dataset.test_images.size() << std::endl;
    // std::cout << "Nbr of test labels = " << dataset.test_labels.size() << std::endl;

    int num_train_images = dataset.training_images.size();
    // int num_train_images = 8000;
    int num_pixels       = dataset.training_images.front().size();  // should be 28*28 = 784

    /* Convert 60000 training images from [0, 255] to [0, 1)
     * We will first generate another 2D array by `new`
     */

    /* training_images_flat[i*num_pixels + j] == training_images[i][j]
     * j-th pixel in i-th image
     */
    float *training_images_flat = new float[num_train_images * num_pixels];

    float **training_images = new float*[num_train_images];
    for (int i = 0; i < num_train_images; i++) {
        training_images[i] = training_images_flat + i * num_pixels;
    }

    for (int i = 0; i < num_train_images; i++) {
        for (int j = 0; j < num_pixels; j++) {
            training_images[i][j] = (float)(dataset.training_images[i][j]) / 255.0;
        }
    }

    /* Print first image */
    // print_img(training_images[0]);
    

    /* Load matrices' weight from binary file
     * You can print the binary file by: `od -f layer1_bais`
     * https://stackoverflow.com/questions/36791622/how-to-print-float-value-from-binary-file-in-shell
     */
    float *layer1_matrix = new float[LAYER0 * LAYER1];
    float *layer1_bias = new float[LAYER1];
    float *layer2_matrix = new float[LAYER1 * LAYER2];
    float *layer2_bias = new float[LAYER2];
    read_weight(layer1_matrix, "layer1_matrix", LAYER0 * LAYER1);
    read_weight(layer1_bias, "layer1_bias", LAYER1);
    read_weight(layer2_matrix, "layer2_matrix", LAYER1 * LAYER2);
    read_weight(layer2_bias, "layer2_bias", LAYER2);
    
    
    /*
    std::cout << "The first 10 numbers in layer1_matrix: ";
    for (int i = 0; i < 10; i++) {
        std::cout << layer1_matrix[i] << ' ';
    }
    std::cout << std::endl;
    */

    auto read_end = std::chrono::steady_clock::now();

    /* Inference */
    int *result = new int[num_train_images];
    my_nn(training_images_flat, num_train_images,
          layer1_matrix, layer1_bias, layer2_matrix, layer2_bias, result);

    auto inference_end = std::chrono::steady_clock::now();

    /* Calculate accuracy */
    int correct = 0;
    int total = 0;
    for (int i = 0; i < num_train_images; i++) {
        if ((int)result[i] == (int)dataset.training_labels[i]) {
            correct++;
        }
        total++;
    }
    std::cout << "\nInference accuracy: " << (double)correct / (double)total * 100.0 << "%\n";
    if (argc == 1) 
        write_predict(result, num_train_images, RESULT_FILE);
    else
        write_predict(result, num_train_images, argv[2]);

    auto acc_end = std::chrono::steady_clock::now();

    std::cout << std::setprecision(5) << std::fixed;
    std::cout << "\n-----     STATS     -----\n";
    std::cout << "Time for initializing CUDA device:     " << std::chrono::duration_cast<std::chrono::milliseconds>(read_start - initcuda_start).count() << " m.s.\n";
    std::cout << "Time for reading MNIST data & weights: " << std::chrono::duration_cast<std::chrono::milliseconds>(read_end - read_start).count() << " m.s.\n";
    std::cout << "Time for inferencing                 : " << std::chrono::duration_cast<std::chrono::milliseconds>(inference_end - read_end).count() << " m.s.\n";
    std::cout << "Time for calculating accuracy        : " << std::chrono::duration_cast<std::chrono::milliseconds>(acc_end - inference_end).count() << " m.s.\n";
    std::cout <<   "----- END OF STATS  -----\n";

    delete [] result;
    delete [] layer1_matrix;
    delete [] layer1_bias;
    delete [] layer2_matrix;
    delete [] layer2_bias;
    delete [] training_images_flat;
    delete [] training_images;
    return 0;
}
