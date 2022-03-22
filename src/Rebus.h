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
        void newPost();
        void editPost();
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
/**
 * @brief Function that adds new post and adds to vector
 */
void Rebus :: newPost(){
Checkpoint* tempPost = new Checkpoint;
posts.push_back(tempPost);
}
/**
 * @brief Function that first asks which post user wants to edit, and then show all ways user can edit the post,
 *        and let's the user thn pick one of said options.
 */
void Rebus::editPost(){
    int postChoice;
    int command;
    listPosts();
    postChoice = lesInt("Choose post to edit",1,posts.size());
    
    do{
        cout << "Choose Option:\n"          //will put this in function later... im lazy
            << "\t1. Change post nr\n"
            << "\t2. Change description\n"
            << "\t3. Change Maxpoints\n"
            << "\t0. Cancel\n";
            command = lesInt("Choose option",0,3);
            switch(command){
                case 1: posts[postChoice]->editPostnr(); break;
                case 2: posts[postChoice]->editDescription(); break;
                case 3: posts[postChoice]->editMaxPoints(); break;
                case 4: break;
                
            }
}while(command != 0);
}

void Rebus::listPosts(){ // skal senere endre denne til 2 bool variabler for å velge hvor mye informasjon som skal printes ut
                        //som gjort i listTeams()
    for(int i=0; i < posts.size();i++){
        cout << i+1 << "." << ": ";
        posts[i]->writePostData();
        cout << '\n';
    }
}

void Rebus::registerPoints(){
    listTeams(true,false);
    int teamChoice = lesInt("Choose a team number to register points for",1,teams.size());
    listPosts();
    int postChoice = lesInt("Choose a post number to register points for",1,posts.size());
    teams[teamChoice]->addPoints(postChoice,posts[postChoice]->returnMaxPoints());
}

#endif