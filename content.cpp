#include "content.h"

std::vector<int> ContentTable::create_representation(std::string content){
        Document doc;
        doc.Parse(content.c_str());
        int value;
        std::string False = "False";
        std::vector<int> representation;
        std::hash<std::string> hash_function;
        
        if(doc["Response"].GetString() != False){
            value =  (int)(hash_function(doc["Rated"].GetString())%HASH_LEN); 
            representation.push_back(value);

            value =  (int)(std::stoi(doc["Year"].GetString())); 
            representation.push_back(value - 1900);

            value =  (int)(hash_function(doc["Type"].GetString())%HASH_LEN); 
            representation.push_back(value);

            value =  (int)(hash_function(doc["Country"].GetString())%HASH_LEN); 
            representation.push_back(value);

            value =  (int)(hash_function(doc["Director"].GetString())%HASH_LEN); 
            representation.push_back(value);

            value =  (int)(hash_function(doc["Language"].GetString())%HASH_LEN); 
            representation.push_back(value);


            value = (int)(hash_function(doc["Genre"].GetString())%HASH_LEN); 
            representation.push_back(value);

            std::string runtime = doc["Runtime"].GetString();
            value = atoi(runtime.substr(0, runtime.find(" ")).c_str());
            representation.push_back(value);

        }else{
            for(int i = 0; i < 8; i++){
                representation.push_back(0);
            }
        }
        return representation;
}

ContentTable::ContentTable(std::string filename){
    bool First = true;
    std::ifstream file;
    file.open(filename);
    std::string line;

    while(getline(file,line)){
        if(First){
            First = false;
            continue;
        }

        std::string work_line = line;
        int item = atoi(work_line.substr(1, work_line.find(",")-1).c_str());
        std::string content = line.substr(line.find(",")+1,-1);
        this->itens.insert(std::make_pair(item, content));
    }

    file.close();
    return;
};


std::pair<std::vector<std::vector<int>>, std::vector<int>> ContentTable::create_train(std::vector<std::array<int, 5>> ratings){
    std::pair<std::vector<std::vector<int>>, std::vector<int>> train;
    for(unsigned int i = 0; i < ratings.size(); i++ ){
        std::vector<int> representation = create_representation(this->itens[ratings[i][1]]);
        train.first.push_back(representation);
        train.second.push_back(ratings[i][2]);
    }
    return train;
} 

std::unordered_map<int, std::vector<int>> ContentTable::itens_representation(std::vector<std::array<int, 5>> ratings){
    std::unordered_map<int, std::vector<int>> itens_representation;
    for(unsigned int i = 0; i < ratings.size(); i++ ){
        std::vector<int> representation = create_representation(this->itens[ratings[i][1]]);
        itens_representation.insert(std::make_pair(ratings[i][1], representation));
    }
    return itens_representation;
}