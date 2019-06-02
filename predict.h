#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map> 
#include <cmath>
#include <set> 
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>
#include <iomanip>
#include <unordered_map> 
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>
#include <iostream>
#include <functional>
#include <string>
#include "matrix.h"

#define RECOMMENDER_DIMENTIONS 100
#define LEARNING_RATE .0000001
#define EPOCHS 200
using namespace std;
using namespace rapidjson;

class Recommender{
    public:
        // std::unordered_map<std::string, std::set<float>> itens_ratings;
        std::unordered_map<int, std::vector<std::array<int,2>>> user_ratings;
        std::unordered_map<int, std::vector<float>> user_weigts;
        std::set<int> users;
        std::set<int> all_itens;

        std::vector<array<int, 5>> ratings;
        std::pair<std::vector<std::vector<int>>, std::vector<int>> train;
        std::unordered_map<int, std::vector<int>> itens;
        float mean;
    
    Recommender(std::pair<std::vector<std::vector<int>>, std::vector<int>> train, std::unordered_map<int, std::vector<int>> itens, std::vector<std::array<int, 5>> ratings);
    std::vector<float> regression(std::vector<float> weights, int user);
    void get_mean();
    void get_prediction(string filename);
    void test(string filename);
    float predict(int item, int user, std::vector<float> weights);
    float get_error(int item, int user, int rating, std::vector<float> weights);
    std::vector<float> gradient(int item, int user, int rating, std::vector<float> weights);
    void train_weights();

};