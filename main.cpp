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
    std::unordered_map<int, std::vector<int>> itens = content_table.itens_representation(ratings);

    Recommender recommender(itens,ratings);
    recommender.get_mean();
    recommender.train_weights();    
    recommender.get_prediction(targets_filename);
    return 0;
}

