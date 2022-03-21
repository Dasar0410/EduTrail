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
    int option;
    int command;
    listTeams(true,false); // only show the team name, and not it's participants
    command = lesInt("Choose team u want to edit",1,teams.size()); 
    teams[command-1]->writeEditMenu(); // prints out menu
    
    do{
        option = lesInt("Choose option:",0,4);
        switch(option){
            case 0: break;
            case 1: teams[command-1]->changeName(); break;
            case 2: 
        }
    }while(option != 0);
}
    



void Rebus :: listTeams(const bool showName, const bool showMembers){
    for(int i=0;i<teams.size();i++){
        teams[i]->writeData(showName,showMembers);
    }
}