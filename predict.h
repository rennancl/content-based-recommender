#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map> 
#include <cmath>
#include <set> 

#include "matrix.h"
#define RECOMMENDER_DIMENTIONS 50
#define LEARNING_RATE .002
#define EPOCHS 100
using namespace std;

class Recommender{
    public:
        std::unordered_map<std::string, std::set<float>> itens_ratings;
        std::unordered_map<std::string, std::set<float>> user_ratings;
        std::vector<array<int, 5>> ratings;
        float mean;

    
    Recommender(std::pair<int, int> dimentions, std::vector<array<int, 5>> train);

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