/**
 * @file Rebus.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Rebus class.
 * @date 2022-03-14
 * 
 * 
 */


//#include "Checkpoint.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;


/**
 * @brief Class containing all information on a specific game of rebus.
 * 
 */
class Rebus{
    private:
//        vector <Checkpoint*> checkpoints;
        vector <Team*> teams;

    public:
        void newTeam();
        void editTeam();
        void deleteTeam();
        void listTeams(const bool showName, const bool showMembers);
};


/**
 * @brief Function that creates a new team object on the team vector. See team constructor on the following process of team creation.
 * 
 */
void Rebus :: newTeam(){
    Team * tempTeam = new Team;
    teams.push_back(tempTeam);
}

void Rebus :: editTeam(){

}

void Rebus :: listTeams(const bool showName, const bool showMembers){
    for(int i=0;i<teams.size();i++){
        teams[i]->writeData(showName,showMembers);
    }
}