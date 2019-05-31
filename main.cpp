#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath> 
#include "predict.h"
#include "content.h"


int main(int argc, char *argv[])
{ 
    std::string ratings_filename = argv[1];
    std::string targets_filename = argv[2];
    std::string content_filename = argv[3];

    //this vector contains all lines of the cvs file describing the user-iten-rating matrix 
    std::vector<array<int, 5>> ratings = process_inputs(ratings_filename);

    ContentTable content_table(content_filename);
    std::cout << content_table.itens[4967094] << std::endl;
    
    
    // Model model(get_matrix_dimentions(ratings), ratings);
    // model.get_mean();
    // model.create_pq_matrix();
    // model.fill_pq_matrix(); 
    // model.stochastic_gradient_descent();
    // model.get_prediction(targets_filename);

    return 0;
}

