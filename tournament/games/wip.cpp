#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct card{
    int color;
    string type;
};

bool uno(const string & t1, const string & t2){
    vector<string> pack(15);
    vector<int> all_color(4);
    vector<card> cardsP1;
    vector<card> cardsP2;
    string number = "0123456789";
    for(size_t i = 0; i < 10; i++){
        pack[i] = number[i];
    }
    for (size_t i = 0; i < 4; i++)
    {
        all_color[i] = i;
    }
    pack[10] = "10";
    pack[11] = "skip";
    pack[12] = "rev";
    pack[13] = "+2";
    pack[14] = "+4";

}
