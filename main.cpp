#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath> 
#include "model.h"

using namespace std;

int main(int argc, char *argv[])
{ 
    string ratings_filename = argv[1];
    string targets_filename = argv[2];

    vector<array<int, 5>> ratings = process_inputs(ratings_filename);

    //2.0 need to treat the cases which the iten or user was not seen
    //3.0 calculates de user and item bias

    Model model(get_matrix_dimentions(ratings), ratings);
    model.get_mean();
    model.create_pq_matrix();
    model.fill_pq_matrix(); 
    model.stochastic_gradient_descent();
    model.get_prediction(targets_filename);

    return 0;
}

