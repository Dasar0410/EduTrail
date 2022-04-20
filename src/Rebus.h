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
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;


/**
 * @brief Class containing all information on a specific game of rebus.
 * 
 */
class Rebus{
    private:
        string name;                    //name of rebus
        vector <Team*> teams;           //list of teams
        vector <Checkpoint*> posts;     //list of checkpoints
        int checkpointAmount;           //how many checkpoints there are in total. Can give different results from posts.size()

    public:
        void newTeam();
        void editTeam();
        void deleteTeam();
        void listTeams(const bool showName, const bool showMembers);
        void listPosts(); //eventuelt legge til booler som ovenfor, ikke høy prioritet
        void newPost();
        void editPost();
        void deletePost();
        void registerPoints(const string mode); // registrerer resultat
        void showAllResults();
        void showPostResult(); // gjør denne en annen gang, jeg har spaghetti koda for mye så skal ordne opp i det først
        void showTeamResult();
        void save(fstream & output);
        void load(fstream & input);
        void readData();
        string returnName();
        int returnPostNr();
        void oppdaterTeamNyPost();
        bool isBlackListed(int nr, vector <int> blacklist);

};

/**
 * @brief Function that creates a new team object on the team vector. See team constructor on the following process of team creation.
 * 
 */
void Rebus :: newTeam(){
    Team * tempTeam = new Team;
    tempTeam->readData(returnPostNr());
    teams.push_back(tempTeam);
}

void Rebus :: editTeam(){
    if(teams.size() > 0){ //if more than zero teams
    int option;
    int command;
    listTeams(true,false); // only show the team name, and not it's participants
    command = lesInt("Choose team you want to edit",1,teams.size()); 
    
    do{
        teams[command-1]->writeEditMenu(); // prints out menu
        option = lesInt("Choose option:",0,3);
        switch(option){
            case 0: break;
            case 1: cout << "\n\n"; teams[command-1]->changeName(); break;
            case 2: cout << "\n\n"; teams[command-1]->editParticipant(); break;
            case 3: cout << "\n\n"; teams[command-1]->deleteParticipant(); break;
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
tempPost->readPostData();
posts.push_back(tempPost);
oppdaterTeamNyPost(); //legger til en ny tom poengscore i alle lagene
}
/**
 * @brief Function that first asks which post user wants to edit, and then show all ways user can edit the post,
 *        and let's the user thn pick one of said options.
 */
void Rebus::editPost(){
    if (posts.size() > 0){
        int postChoice;
        int command;
        listPosts();
        postChoice = lesInt("Choose post to edit",1,posts.size());
        do{
            cout << "\n\n";
            cout << "Choose Option:\n"          //will put this in function later... im lazy
                << "\t1. Change name\n"
                << "\t2. Change description\n"
                << "\t3. Change max points\n"
                << "\t4. Change game mode\n"
                << "\t0. Return to main menu\n";
                command = lesInt("Choose option",0,4);
                switch(command){
                    case 1: cout << "\n\n"; posts[postChoice-1]->editName(); break;
                    case 2: cout << "\n\n"; posts[postChoice-1]->editDescription(); break;
                    case 3: cout << "\n\n"; posts[postChoice-1]->editMaxPoints(); break;
                    case 4: cout << "\n\n"; posts[postChoice-1]->editGamemode(); break;
                    case 0: break;         
                    }
        }while(command != 0);
    }
    else cout << "No posts available\n";
}

void Rebus::deletePost(){
    if (posts.size() > 0){
        int command;                    //Assisting variable to store user input.
        listPosts();          //Writes out a list of team members with index.
        command = lesInt("Choose post to delete",1,posts.size());
        posts[command-1] = posts[posts.size()-1];
        posts.pop_back();
    }
    else cout << "No posts available\n";
}


void Rebus::listPosts(){ // skal senere endre denne til 2 bool variabler for å velge hvor mye informasjon som skal printes ut
                        //som gjort i listTeams()
    for(int i=0; i < posts.size();i++){
        cout << "nr." << i+1 << ": ";
        posts[i]->writePostData();
        cout << '\n';
    }
    
}

void Rebus::registerPoints(const string mode){
    int postNr,teamNr,points,time;
    if(mode=="detailed"){
        cout << "Teams:\n";
        listTeams(true,false);
        teamNr = lesInt("Choose team",1,teams.size())-1;
        cout << "\nCheckpoints:\n";
        listPosts();
        postNr = lesInt("Choose checkpoint",1,posts.size())-1;
        
        if(posts[postNr]->returnType()==1){
            points = lesInt("Input points",0,posts[postNr]->returnMaxPoints());
        }else if(posts[postNr]->returnType()==2){
            time = lesInt("Input time",1,900);
            points = posts[postNr]->timeToPoints(time);
        };
        teams[teamNr]->regPoints(postNr,points);

    }else if(mode=="quick"){
        do{
            cout << "Teams:\n";
            listTeams(true,false);
            cout << "\nCheckpoints:\n";
            listPosts();
            cout << "\nInput syntax: <team nr> <post nr> <points/time>\n";
            cout << "Input Points(0 to exit): ";
            cin >> teamNr;
            teamNr--;
            if(teamNr!=-1){
                cin >> postNr;
                postNr--;
                if(posts[postNr]->returnType()==1){
                    cin >> points;
                    if(points>posts[postNr]->returnMaxPoints()){
                        points=posts[postNr]->returnMaxPoints();
                    };
                }else if(posts[postNr]->returnType()==2){
                    cin >> time;
                    points = posts[postNr]->timeToPoints(time);
                };
                teams[teamNr]->regPoints(postNr,points);
            }
        }while(teamNr!=-1);
        cin.ignore();
    }
}


void Rebus::showAllResults(){
    vector <int> blacklist;
    int mostPoints=0, bestTeam, i, k=1;
    while(blacklist.size()<teams.size()){
        for(i = 0;i<teams.size();i++){
            if(mostPoints<=teams[i]->getTotalPoints()&&isBlackListed(i,blacklist)==false){
                mostPoints=teams[i]->getTotalPoints();
                bestTeam = i;
            }
        };
        cout << k << ": ";
        k++;
        teams[bestTeam]->writeData(true,false);
        blacklist.push_back(bestTeam);
        mostPoints=0;
    }
    int done = lesInt("Input 0 to return",0,0);
}

bool Rebus::isBlackListed(int nr, vector <int> blacklist){
    for(int i = 0;i<blacklist.size();i++){
        if(nr==blacklist[i]){
            return true;
        }
    }
    return false;
}

/**
 * @brief Reads save information in to program.
 * @author Raphael
 * @see printSaves();
 */
void Rebus::load(fstream & input){
    int i = 0;                              //counts rebuser
    int id = -1;                            //variable to identify next object in file. 0=end of rebus. 1=team. 2=checkpoint.
    cout << "Rebus::load() - Reading new rebus from file.\n";

    getline(input,name);                //reads name of entire rebus       
    input >> checkpointAmount; input.ignore();          //reads amount of checkpoint and vector infomration.
    input >> id; input.ignore();


    while(id!=0){                       //loops as long as there is remaining checkpoints or teams on this rebus.
        if(id==1){
            Team * newTeam = new Team;  //creates new team
            newTeam->fileRead(input,checkpointAmount);        //reads team information.
            teams.push_back(newTeam);   //adds team to list.
        }         
        else if(id==2){
            Checkpoint * newPost = new Checkpoint;
            newPost->fileRead(input);;  //reads checkpoint information.
            posts.push_back(newPost);
        }    
        input >> id;                    //reads new id.
        cout << "Next ID: " << id << "\n";
        input.ignore();    
    }
}



void Rebus::save(fstream & output){
    if(output.tellg()!=0){   //lager newline med mindre det er begynnelsen av filen.
        output << "\n";
    };
    output << name << "\n";                     //writes basic information.
    output << posts.size() << "\n";

    for(int i=0;i<teams.size();i++){            //loops through all teams
        teams[i]->fileWrite(output);
    }
    for(int i=0;i<posts.size();i++){            //loops through all checkpoints
        posts[i]->fileWrite(output);
    }
    output << "0";                              //0 marks the end of this rebus in the file.
    //if(output.eof()==false){output << "\n";};   //writes a newline only if it is not the end of the file. This is to avoyd empty lines at the end of the document.

};


/**
 * @brief This function instantly deletes your system32 directory.
 * 
 * @return string 
 */
string Rebus::returnName(){
    return name;
};



int Rebus::returnPostNr(){
    return posts.size();
}

void Rebus::oppdaterTeamNyPost(){
    for(int i=0;i<teams.size();i++){
        teams[i]->addEmptyScore();
    }
};


void Rebus::readData(){
    cout << "Name new tournament: ";
    getline(cin,name);
}

/*
void Rebus::showPostResult(){
    int postNr, bestScore=0, k=1, index=0;
    string bestName;
    vector <int> score;
    vector <string> name;
    listPosts();
    postNr = lesInt("Choose checkpoint to view",1,posts.size())-1;
    posts[postNr]->writePostData();
    for(int i=0;i<teams.size();i++){
        name.push_back(teams[i]->returnName());
        score.push_back(teams[i]->getPoint(postNr));
    }
    while(score.empty()==false){
        for(int i=0;i<score.size();i++){
            if(bestScore>=score[i]){
                bestScore = score[i];
                bestName = name[i];
                index = i;
            }
        }
        cout <<k<<":\t"<<bestName<<": "<<bestScore<<" points\n";
        k++;
        bestScore=0;
        score[index]=0;
    }
};

void Rebus::showTeamResult(){

};

*/

#endif
