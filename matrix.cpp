#include "matrix.h"
using namespace std;

Matrix::Matrix(std::pair<int, int> dimentions){
    this->dimentions = dimentions;
    this->x_dimention = dimentions.first;
    this->y_dimention = dimentions.second;
}

void Matrix::create_matrix(){
    this->matrix = new float*[x_dimention + 1];
    for (int i = 0; i < x_dimention + 1; i++)
        {
            this->matrix[i] = new float[y_dimention + 1];
        }
}

void Matrix::fill_ones(){
    for(int i = 0; i < x_dimention + 1; i++)
    {
        for(int j = 0; j < y_dimention + 1; j++)
        {
            matrix[i][j] = 0.4;
        }
        
    }
}

void Matrix::fill_matrix(std::vector<array<int, 5>> input_vector){
    for(unsigned i = 0; i < input_vector.size(); i++){
        this->matrix[get<0>(input_vector[i])][get<1>(input_vector[i])] = (float)get<2>(input_vector[i]);
    }
}

int max_in_vector(vector<array<int, 5>> vetor,unsigned const int index){
    int max_value = 0;
    for(unsigned i = 0; i < vetor.size(); i++){
        if(vetor[i][index] > max_value){
            max_value = vetor[i][index];
        }    
    }
    return max_value;
}

pair<int,int> get_matrix_dimentions(vector<array<int, 5>> vetor){
    pair<int,int> max_values;
    max_values.first = max_in_vector(vetor, 0);
    max_values.second = max_in_vector(vetor, 1);
    return max_values;
}

vector<array<int, 5>> process_inputs(string filename){
    ifstream file;
    file.open(filename);
    string line;
    std::vector<array<int, 5>> inputs;
    while(getline(file,line)){
        if (line.find(",") != std::string::npos){
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            work_line = line;
            delimiter = ",";
            work_line = work_line.substr(work_line.find(delimiter)+1, -1);
            int rating = atoi(work_line.substr(0, work_line.find(delimiter)).c_str());

            work_line = line;
            delimiter = ",";
            work_line = work_line.substr(work_line.find(delimiter)+1, -1);
            int timestamp = atoi(work_line.substr(work_line.find(delimiter)+1, -1).c_str());
            if(user == 0 and item == 0) continue;
            inputs.push_back({user, item, rating, timestamp, 0});
        }
        else{
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            int rating = 0;
            int timestamp = 0;
            if(user == 0 and item == 0) continue;
            inputs.push_back({user, item, rating, timestamp, 0});
        }
    }

    file.close();
    return inputs;
}


// vector<array<int, 5>> process_inputs2(string filename){
//     ifstream file;
//     file.open(filename);
//     string line;
//     std::vector<array<int, 5>> inputs;
//     while(getline(file,line)){
//         if (line.find(",") != std::string::npos){
//             string work_line = line;
//             string delimiter = ":";
//             int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

//             work_line = line;
//             delimiter = ":";
//             string delimiter2 = ",";
//             int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

//             work_line = line;
//             delimiter = ",";
//             work_line = work_line.substr(work_line.find(delimiter)+1, -1);
//             int rating = atoi(work_line.substr(0, work_line.find(delimiter)).c_str());

//             work_line = line;
//             delimiter = ",";
//             work_line = work_line.substr(work_line.find(delimiter)+1, -1);
//             int timestamp = atoi(work_line.substr(work_line.find(delimiter)+1, -1).c_str());
//             if(user == 0 and item == 0) continue;
//             inputs.push_back({user, item, rating, timestamp, 0});
//         }
//         else{
//             string work_line = line;
//             string delimiter = ":";
//             int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

//             work_line = line;
//             delimiter = ":";
//             string delimiter2 = ",";
//             int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

//             int rating = 0;
//             int timestamp = 0;
//             if(user == 0 and item == 0) continue;
//             inputs.push_back({user, item, rating, timestamp, 0});
//         }
//     }

//     file.close();
//     return inputs;
// }