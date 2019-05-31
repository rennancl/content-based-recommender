#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
using namespace std;

class Matrix{
    public:
        int x_dimention;
        int y_dimention;
        std::pair<int, int> dimentions;
        float** matrix;
    
    Matrix(std::pair<int, int> dimentions);
    void create_matrix();
    void fill_ones();
    void fill_matrix(std::vector<array<int, 5>> input_vector);
};


int max_in_vector(vector<array<int, 5>> vetor,unsigned const int index);

pair<int,int> get_matrix_dimentions(vector<array<int, 5>> vetor);

vector<array<int, 5>> process_inputs(string filename);