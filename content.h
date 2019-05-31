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
using namespace rapidjson;

class ContentTable{
    public:
        std::unordered_map<int, std::string> itens;

    ContentTable(std::string filename);
};