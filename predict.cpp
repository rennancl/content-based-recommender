#include "predict.h"
using namespace std;

Recommender::Recommender(std::pair<std::vector<std::vector<int>>, std::vector<int>> train, std::unordered_map<int, std::vector<int>> itens,std::vector<std::array<int, 5>> ratings){
    this->train = train;
    this->itens = itens;
    this->ratings = ratings;

}

float Recommender::predict(int item, int user,std::vector<float> weights){
    float prediction = 0;
    std::vector<int> representation = itens[item];
    representation.push_back(user);
    for(unsigned int i = 0; i < weights.size() - 1; i++){
        prediction += weights[i] * representation[i];
    }
    prediction += weights[weights.size() - 1];
    return prediction; 
}


void Recommender::get_mean(){
    int sum = 0;
    for(unsigned i = 0; i < this->ratings.size(); i++){
        sum += this->ratings[i][2];
    }
    this->mean = (float)sum/(float)this->ratings.size();
}


std::vector<float> Recommender::regression(std::vector<float> weights){
    
    std::vector<float> temp;
    std::vector<float> final_weights = weights;

    for(unsigned int k = 0; k < EPOCHS; k ++){
        for(unsigned int i = 0; i < weights.size(); i++) weights[i] = 0;
        for(unsigned int i = 0; i < ratings.size(); i ++){
            int user = ratings[i][0];
            int item = ratings[i][1];
            int rating = ratings[i][2];
            temp = gradient(item, user, rating, weights);
            for(unsigned int j = 0; j < temp.size(); j++) weights[j] += temp[j];
        }
        for(unsigned int i = 0; i < weights.size(); i++) weights[i] /= (float)weights.size();
        for(unsigned int i = 0; i < weights.size(); i++) final_weights[i] -= LEARNING_RATE*weights[i]; 

    }

    return  weights;
}

std::vector<float> Recommender::gradient(int item, int user, int rating, std::vector<float> weights){
    vector<float> new_weights;
    float error = get_error( item,  user,  rating,  weights);
    std::vector<int> representation = itens[item];
    representation.push_back(user);


    for(unsigned int i = 0; i < weights.size() - 1; i++){

        new_weights.push_back((-2)  * error * representation[i]);
    }
    new_weights.push_back((-2)  * error );
    return new_weights; 
}

float Recommender::get_error(int item, int user, int rating, std::vector<float> weights){
    return rating - predict(item, user, weights);
}
void Recommender::get_prediction(string filename){
    ifstream file;
    file.open(filename);
    bool First = true;
    string line;
    cout << "UserId:ItemId" << "," << "Prediction" << endl;
    

    std::vector<float> weights;
    for(unsigned int i = 0; i < train.first[0].size(); i++) weights.push_back(1);
    weights.push_back(1);
    weights = regression(weights);
    while(getline(file,line)){
            if(First){
                First = false;
                continue;
            }
            string work_line = line;
            string delimiter = ":";
            int user = atoi(work_line.substr(1, work_line.find(delimiter)-1).c_str());

            work_line = line;
            delimiter = ":";
            string delimiter2 = ",";
            int item = atoi(work_line.substr( work_line.find(delimiter)+2, work_line.find(delimiter2)).c_str());

            
            float prediction = predict(item, user, weights);
            if(prediction > 10) prediction = 10;
            if(prediction < 0) prediction = 0;

            std::cout << line << "," << prediction << std::endl;
        }   
    for(unsigned int i = 0; i < weights.size(); i++) std::cout << weights[i] << std::endl;

    file.close();
    return;
}

