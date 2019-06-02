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

#define HASH_LEN 100
using namespace rapidjson;

class ContentTable{
    public:
        std::unordered_map<int, std::string> itens;
        
        ContentTable(std::string filename);
        std::vector<int> create_representation(std::string content);
        std::pair<std::vector<std::vector<int>>, std::vector<int>> create_train(std::vector<std::array<int, 5>> ratings);
        std::unordered_map<int, std::vector<int>> itens_representation(std::vector<std::array<int, 5>> ratings);
};