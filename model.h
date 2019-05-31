#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include "matrix.h"
#define MODEL_DIMENTIONS 50
#define LEARNING_RATE .002
#define EPOCHS 100
using namespace std;

class Model{
    public:
        std::pair<int, int> p_dimentions;
        std::pair<int, int> q_dimentions;
        int model_dimentions;
        float learning_rate;
        float mean;
        std::vector<array<int, 5>> train;
        std::vector<array<int, 5>> test;
        std::vector<array<int, 5>> target;

        Matrix* p_matrix;
        Matrix* q_matrix;
    
    Model(std::pair<int, int> dimentions, std::vector<array<int, 5>> train);

    void create_pq_matrix();

    void fill_pq_matrix();

    Matrix getq_matrix();
    
    Matrix getp_matrix();

    void get_mean();

    void print_csv_line(int user, int item, float prediction);

    void get_prediction(string filename);

    float get_value_product(int user, int item);

    void update_matrix(int user, int item, float error);

    void stochastic_gradient_descent();
};