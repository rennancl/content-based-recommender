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

#define HASH_LEN 100
#define RECOMMENDER_DIMENTIONS 50
#define LEARNING_RATE .002
#define EPOCHS 100
using namespace std;
using namespace rapidjson;

class Recommender{
    public:
        // std::unordered_map<std::string, std::set<float>> itens_ratings;
        // std::unordered_map<std::string, std::set<float>> user_ratings;
        std::vector<array<int, 5>> ratings;
        std::pair<std::vector<std::vector<int>>, std::vector<int>> train;
        std::unordered_map<int, std::vector<int>> itens;
        float mean;
    
    Recommender(std::pair<std::vector<std::vector<int>>, std::vector<int>> train, std::unordered_map<int, std::vector<int>> itens, std::vector<std::array<int, 5>> ratings);
    std::vector<float> regression(std::vector<float> weights);
    void get_mean();
    void get_prediction(string filename);
    float predict(int item, int user, std::vector<float> weights);
    float get_error(int item, int user, int rating, std::vector<float> weights);
    std::vector<float> gradient(int item, int user, int rating, std::vector<float> weights);

};