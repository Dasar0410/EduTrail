/**
 * @file Rebus.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Rebus class.
 * @date 2022-03-14
 * 
 * 
 */


#ifndef __CHECKPOINT_H
#define __CHECKPOINT_H

#include "Checkpoint.h"
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
        vector <Team*> teams;
        vector <Checkpoint*> posts;

    public:
        void newTeam();
        void editTeam();
        void deleteTeam();
        void listTeams(const bool showName, const bool showMembers);
        void listPosts(); //eventuelt legge til booler som ovenfor, ikke høy prioritet
        void registerPoints(); // registrerer resultat
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
    if(teams.size() > 0){ //if more than zero teams
    int option;
    int command;
    listTeams(true,false); // only show the team name, and not it's participants
    command = lesInt("Choose team you want to edit",1,teams.size()); 
    teams[command-1]->writeEditMenu(); // prints out menu
    
    do{
        option = lesInt("Choose option:",0,4);
        switch(option){
            case 0: break;
            case 1: teams[command-1]->changeName(); break;
            case 2: teams[command-1]->editParticipant(); break;
            case 3: teams[command-1]->deleteParticipant(); break;
            case 4: teams[command-1]->editPoints(); break;
        }
    }while(option != 0);
    }
    else cout << "\nThere are no teams to edit!\n";
}
    



void Rebus :: listTeams(const bool showName, const bool showMembers){
    if(teams.size() > 0){ // if more than zero teams
        for(int i=0;i<teams.size();i++){
            cout << "nr." << i+1 << ": ";
            teams[i]->writeData(showName,showMembers);
        }
    }
    else cout << "\nThere are no teams to edit!\n";
}

void Rebus::listPosts(){
    for(int i=0; i < posts.size();i++){
        cout << "nr." << posts[i]->postNumber() << ": ";
        posts[i]->writePostData();
        cout << '\n';
    }
}

void Rebus::registerPoints(){
    listTeams(true,false);
    int teamChoice = lesInt("Choose a team number to register points for",1,teams.size());
    listPosts();
    int postChoice = lesInt("Choose a post number to register points for",1,posts.size());
}

#endif