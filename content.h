#include <bits/stdc++.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#define HASH_LEN 50
using namespace rapidjson;

class ContentTable{
    private:
        std::unordered_map<int, std::string> itens;

    public:
        ContentTable(std::string filename);
        std::vector<int> create_representation(std::string content);
        std::pair<std::vector<std::vector<int>>, std::vector<int>> create_train(std::vector<std::array<int, 5>> ratings);
        std::unordered_map<int, std::vector<int>> itens_representation(std::vector<std::array<int, 5>> ratings);
};