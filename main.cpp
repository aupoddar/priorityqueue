#include <iostream>
#include "json.hpp"
#include "priorityqueue.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <cstdlib>
#include <cmath>
#include <stdlib.h>

typedef double                  Key;
typedef std::pair<int, int>     Value; //Value.first() Value.second()
typedef std::pair<Key, Value>   KeyValuePair;

bool helper (int boy, int girl, std::vector <int> players) {
    for (int i = 0; i < players.size(); i++) {
        if (boy == players.at(i) || girl == players.at(i)) {
            return false;
        }
    }
    return true;
}

int main() {

    std::ifstream file;
    file.open("TestCase17.createteams.json");
    nlohmann::json jsonObject;
    if(file.is_open()){
        file >> jsonObject;
       // std::cout << jsonObject;
    }

    nlohmann::json final_tree;
    int max =jsonObject["metadata"]["numPlayers"];
    PriorityQueue Tree(max); //mazheapsizees
   // Value val = std::make_pair(2, 3);
   // KeyValuePair one = std::make_pair(1, val);
   // KeyValuePair two;
   // KeyValuePair three;

  //  Tree.insert(one);


    KeyValuePair min;
    std::vector<int> taken_players;
    int cap = jsonObject["metadata"]["numPlayers"];
    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) {

        std::string temp = itr.key(); //this loop goes through for each sample (key)

        if(temp != "metadata") {

            int i = 0;
            double n = jsonObject[temp][i]["winPercentage"]; //assigning min as first val
            nlohmann::json f;

            int ignore = 0;
            int first = jsonObject[temp][i]["playerOne"];
            int second = jsonObject[temp][i]["playerTwo"];
            double min = abs(50 - n);




            while(taken_players.size() < cap){ //loop until all players have been chosen
                min = 10000;
                for (auto arrayItr = jsonObject[temp].begin(); arrayItr != jsonObject[temp].end(); ++arrayItr) { //go through each stat
                    f = *arrayItr;
                    int boy = f["playerOne"];
                    int girl = f["playerTwo"];
                    double win = f["winPercentage"];

                    if (min > abs(50- win) && helper(boy, girl, taken_players)) { //if true, replace min ..absolute value
                            min = abs(50- win);
                            first = boy;
                            second = girl;
                    }


                }

                KeyValuePair aTeam = std::make_pair(min, std::make_pair(first, second));
                Tree.insert(aTeam);


                taken_players.push_back(first);
                taken_players.push_back(second);


            }
        }
    }

   std::vector<int>temp(2);

   for(int i = 0; i < Tree.size_; i++){
        temp[0]= Tree.nodes_.at(i).second.first;
        temp[1] = Tree.nodes_.at(i).second.second;
        final_tree["teams"][i] = temp;
    }
   std::cout << final_tree.dump(2);







    return 0;
}