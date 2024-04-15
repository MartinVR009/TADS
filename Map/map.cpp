#include <iostream>
#include <map>
#include <string>

using super_map = std::map<std::string, std::map<char, std::string>>; 

using super_mapIterator = std::map<std::string, std::map<char, std::string>>::iterator;
using small_mapIterator = std::map<char, std::string>::iterator;

class Dictionary{
    private:
        super_map library;
        super_map reverse_library;
        super_mapIterator it;

    public:
        Dictionary(){
            for(char key1 = 'a'; key1 <= 'z'; key1++){
                for(char )
                library[][];
            }
        }
        void insert()

};




int main(){
    return 0;
}