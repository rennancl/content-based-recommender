#include "content.h"

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
        std::cout << item << std::endl;
        this->itens.insert(std::make_pair(item, content));
    }

    file.close();
    return;
};