#include "predict.h"
using namespace std;

Recommender::Recommender(std::unordered_map<int, std::vector<int>> itens,std::vector<std::array<int, 5>> ratings){
    this->itens = itens;
    this->ratings = ratings;

    for(unsigned int i = 0; i < ratings.size(); i++){
        users.insert(ratings[i][0]);
        all_itens.insert(ratings[i][1]);

        std::array<int,2> rate = {ratings[i][1], ratings[i][2]} ;
        user_ratings[ratings[i][0]].push_back(rate);
        
        rate = {ratings[i][0], ratings[i][2]} ;
        item_ratings[ratings[i][1]].push_back(rate);
    }
}



void Recommender::get_mean(){
    int sum = 0;
    for(unsigned i = 0; i < this->ratings.size(); i++){
        sum += this->ratings[i][2];
    }
    this->mean = (float)sum/(float)this->ratings.size();

    for(std::set<int>::iterator it=users.begin(); it!=users.end(); ++it){
        int user_id = *it;
        float sum = 0;
        float count = 0;
        for(unsigned int i = 0; i < user_ratings[user_id].size(); i++){
            sum += user_ratings[user_id][i][1];
            count++;
        }
        user_mean[user_id] = (sum/count);
    }

    for(std::set<int>::iterator it=all_itens.begin(); it!=all_itens.end(); ++it){
        int item_id = *it;
        float sum = 0;
        float count = 0;
        for(unsigned int i = 0; i < item_ratings[item_id].size(); i++){
            sum += item_ratings[item_id][i][1];
            count++;
        }
        item_mean[item_id] = (sum/count);
    }

}

std::vector<float> Recommender::regression(std::vector<float> weights, int user){
    
    std::vector<float> temp;
    std::vector<float> final_weights = weights;

    for(unsigned int k = 0; k < EPOCHS; k ++){
        for(unsigned int i = 0; i < weights.size(); i++) weights[i] = 0;
        for(unsigned int i = 0; i < user_ratings[user].size(); i ++){
            int item = user_ratings[user][i][0];
            int rating = user_ratings[user][i][1];
            temp = gradient(item, user, rating, final_weights);
            for(unsigned int j = 0; j < temp.size(); j++) weights[j] += temp[j];
        }
        for(unsigned int i = 0; i < weights.size(); i++) weights[i] /= (float)weights.size();
        for(unsigned int i = 0; i < weights.size(); i++) final_weights[i] += LEARNING_RATE*weights[i]; 
    }
    return final_weights;
}

std::vector<float> Recommender::gradient(int item, int user, int rating, std::vector<float> weights){
    vector<float> new_weights;
    float error = get_error( item,  user,  rating,  weights);
    std::vector<int> representation = itens[item];
    representation.push_back(user % 100);
    
    for(unsigned int i = 0; i < representation.size(); i++){

        new_weights.push_back((2)  * error * representation[i]);
    }
    new_weights.push_back((2)  * error );
    return new_weights; 
}

float Recommender::predict(int item, int user,std::vector<float> weights){
    float prediction = 0;
    std::vector<int> representation = itens[item];
    for(unsigned int i = 0; i < representation.size(); i++){
        prediction += weights[i] * representation[i];
    }
    prediction += weights[(int)weights.size() - 1];
    return prediction; 
}

float Recommender::get_error(int item, int user, int rating, std::vector<float> weights){
    return rating - predict(item, user, weights);
}

void Recommender::train_weights(){
    std::vector<float> weights;
    for(unsigned int i = 0; i < NUM_FEATURES; i++) weights.push_back(0); weights.push_back(mean);
    
    for (std::set<int>::iterator it=users.begin(); it!=users.end(); ++it){
        int user = *it;
        //for(unsigned int i = 0; i < NUM_FEATURES; i++) weights[i] = 0; weights[weights.size() - 1] = user_mean[user];
        weights = regression(weights, user);
        user_weigts.insert(std::make_pair(user, weights));
    }
}

void Recommender::get_prediction(string filename){
    ifstream file;
    file.open(filename);
    bool First = true;
    string line;
    cout << "UserId:ItemId" << "," << "Prediction" << endl;

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
    
            bool user_is_in = users.find(user) != users.end();
            bool item_is_in = all_itens.find(item) != all_itens.end();

            if(user_is_in == false and item_is_in == true){
                std::cout << line << "," << item_mean[item] << std::endl;
                continue;
            }

            if(user_is_in == true and item_is_in == false){
                std::cout << line << "," << user_mean[user] << std::endl;
                continue;
            }

            if(user_is_in == false and item_is_in == false){
                std::cout << line << "," << mean << std::endl;
                continue;
            }

            float prediction = predict(item, user, user_weigts[user]);
            if(prediction > 10) prediction = 10;
            if(prediction < 0) prediction = 0;
            std::cout << line << "," << prediction << std::endl;
        }   

    file.close();
    return;
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