#include "predict.h"
using namespace std;

Recommender::Recommender(std::pair<std::vector<std::vector<int>>, std::vector<int>> train, std::unordered_map<int, std::vector<int>> itens,std::vector<std::array<int, 5>> ratings){
    this->train = train;
    this->itens = itens;
    this->ratings = ratings;

    for(unsigned int i = 0; i < ratings.size(); i++){
        std::vector<std::array<int,2> > empty;
        user_ratings.insert(std::make_pair(ratings[i][0], empty));
        users.insert(ratings[i][0]);
        all_itens.insert(ratings[i][1]);

    }
    for(unsigned int i = 0; i < ratings.size(); i++){
        std::array<int,2> rate = {ratings[i][1], ratings[i][2]} ;
        user_ratings[ratings[i][0]].push_back(rate);
    }

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

    for(unsigned int i = 0; i < ratings.size(); i++){
        std::array<int,2> rate = {ratings[i][0], ratings[i][2]} ;
        item_ratings[ratings[i][1]].push_back(rate);
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

float Recommender::predict(int item, int user,std::vector<float> weights){
    float prediction = 0;
    std::vector<int> representation = itens[item];
    for(unsigned int i = 0; i < representation.size(); i++){
        prediction += weights[i] * representation[i];
    }
    prediction += weights[(int)weights.size() - 1];
    return prediction; 
}


void Recommender::get_mean(){
    int sum = 0;
    for(unsigned i = 0; i < this->ratings.size(); i++){
        sum += this->ratings[i][2];
    }
    this->mean = (float)sum/(float)this->ratings.size();
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

    //std::cout << error << std::endl;
    
    for(unsigned int i = 0; i < representation.size(); i++){

        new_weights.push_back((2)  * error * representation[i]);
    }
    new_weights.push_back((2)  * error );
    return new_weights; 
}

float Recommender::get_error(int item, int user, int rating, std::vector<float> weights){
    return rating - predict(item, user, weights);
}

void Recommender::train_weights(){
    std::vector<float> weights;
    for(unsigned int i = 0; i < train.first[0].size(); i++) weights.push_back(0);
    weights.push_back(mean);
    for (std::set<int>::iterator it=users.begin(); it!=users.end(); ++it){
            weights = regression(weights, *it);
            user_weigts.insert(std::make_pair(*it, weights));
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



void Recommender::test(string filename){
    ifstream file;
    file.open(filename);
    bool First = true;
    string line;
    
    float sum = 0;
    int count = 0;

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
    
            work_line = line;
            delimiter = ",";
            work_line = work_line.substr(work_line.find(delimiter)+1, -1);
            int rating = atoi(work_line.substr(0, work_line.find(delimiter)).c_str());
            
            
            bool user_is_in = users.find(user) != users.end();
            bool item_is_in = all_itens.find(item) != all_itens.end();

            if(user_is_in == false and item_is_in == true){
                sum += (rating - mean) * (rating - mean);
                count++;
                continue;
            }

            if(user_is_in == true and item_is_in == false){
                sum += (rating - mean) * (rating - mean);
                count++;
                continue;
            }

            if(user_is_in == false and item_is_in == false){
                sum += (rating - mean) * (rating - mean);
                count++;
                continue;
            }

            float prediction = predict(item, user, user_weigts[user]);
            if(prediction > 10) prediction = 10;
            if(prediction < 0) prediction = 0;

            sum += (rating - prediction) * (rating - prediction);
            count++;
            //std::cout  << rating - prediction << std::endl;
        }   
    
    std::cout  << "Erro de teste" << sqrt(sum/count) << std::endl;
    file.close();
    return;
}

