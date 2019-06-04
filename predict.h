#include <bits/stdc++.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#define LEARNING_RATE .0000001
#define EPOCHS 400
#define NUM_FEATURES 8
using namespace std;
using namespace rapidjson;

vector<array<int, 5>> process_inputs(string filename);

class Recommender{
    private:
        std::unordered_map<int, std::vector<std::array<int,2>>> user_ratings;
        std::unordered_map<int, float> user_mean;
        std::unordered_map<int, std::vector<std::array<int,2>>> item_ratings;
        std::unordered_map<int, float> item_mean;
        std::unordered_map<int, std::vector<float>> user_weigts;
        std::set<int> users;
        std::set<int> all_itens;
        std::vector<array<int, 5>> ratings;
        std::pair<std::vector<std::vector<int>>, std::vector<int>> train;
        std::unordered_map<int, std::vector<int>> itens;
        float mean;
    
    public:
        Recommender(std::unordered_map<int, std::vector<int>> itens, std::vector<std::array<int, 5>> ratings);
        std::vector<float> regression(std::vector<float> weights, int user);
        void get_mean();
        void get_prediction(string filename);
        void test(string filename);
        float predict(int item, int user, std::vector<float> weights);
        float get_error(int item, int user, int rating, std::vector<float> weights);
        std::vector<float> gradient(int item, int user, int rating, std::vector<float> weights);
        void train_weights();

};