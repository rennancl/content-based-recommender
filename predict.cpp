#include "predict.h"
using namespace std;

Recommender::Recommender(std::pair<int, int> dimentions, std::vector<array<int, 5>> ratings){
//    this->itens_ratings.insert(std::make_pair(ratings[1], std::set::empty()));
//    this->user_ratings.insert(std::make_pair(ratings[0], std::set::empty()));
    this->ratings = ratings;
}

void Recommender::get_prediction(string filename){
    ifstream file;
    file.open(filename);
    string line;
    float prediction;
    cout << "UserId:ItemId" << "," << "Prediction" << endl;
    while(getline(file,line)){
            break;
        }   

    file.close();
    return;
}

void Recommender::get_mean(){
    int sum = 0;
    for(unsigned i = 0; i < this->ratings.size(); i++){
        sum += this->ratings[i][2];
    }
    this->mean = (float)sum/(float)this->ratings.size();
}