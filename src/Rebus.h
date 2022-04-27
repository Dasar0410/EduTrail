/**
 * @file Rebus.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Rebus class.
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
        string name;                                //name of rebus
        vector <Team*> teams;                       //vector containing all teams
        vector <Checkpoint*> posts;                 //vector containing alle checkpoints
        int checkpointAmount;                       //how many checkpoints there are in total

    public:
        void newTeam();
        void editTeam();
        void deleteTeam();
        void listTeams(const bool showName, const bool showMembers);
        void listPosts();
        void newPost();
        void editPost();
        void deletePost();
        void registerPoints(const string mode);
        void showAllResults();
        void showPostResult();
        void showTeamResult();
        void save(fstream & output);
        void load(fstream & input);
        void readData();
        string returnName();
        int returnPostNr();
        void oppdaterTeamNyPost();
        bool isBlackListed(int nr, vector <int> blacklist);
        bool readyToRead();
};

/**
 * @brief Creates a new team
 * 
 */
void Rebus :: newTeam(){
    Team * tempTeam = new Team;                     //Creates new team
    tempTeam->readData(returnPostNr());             //Reads data into team
    teams.push_back(tempTeam);                      //Adds new team to back of vector
}

/**
 * @brief Writes out the team edit menu, and waits for user input before executing chosen function.
 * 
 */
void Rebus :: editTeam(){
    int option;
    int command;
    if(teams.size() > 0){                           //checks if there are any teams
        listTeams(true,false);                      //lists out all teams
        command = lesInt("Choose team you want to edit",1,teams.size()); //User select teamt to edit
        do{
            teams[command-1]->writeEditMenu();      //prints out menu
            option = lesInt("Choose option:",0,3);  //reads input
            switch(option){
                case 0: break;
                case 1: cout << "\n\n"; teams[command-1]->changeName(); break;
                case 2: cout << "\n\n"; teams[command-1]->editParticipant(); break;
                case 3: cout << "\n\n"; teams[command-1]->deleteParticipant(); break;
            }
        }while(option != 0);
    }
    else{cout << "\nNo teams registered.\n";}       //If there are no teams in data rebus
}
    

/**
 * @brief Prints out all teams in rebus.
 * 
 * @param showName If enabled, team name is printed
 * @param showMembers If enabled, team participants are printed
 */
void Rebus :: listTeams(const bool showName, const bool showMembers){
    if(teams.size() > 0){                           //Checks if there are any teams to print
        for(int i=0;i<teams.size();i++){            //iterates through all teams and writes them out
            cout << "nr." << i+1 << ": ";
            teams[i]->writeData(showName,showMembers);
        }
    }
    else cout << "\nThere are no teams to edit!\n";
}

/**
 * @brief Creates a new checkpoint
 * 
 */
void Rebus :: newPost(){
    Checkpoint* tempPost = new Checkpoint;          //Creates checkpoint
    tempPost->readPostData();                       //Reads data into checkpoint
    posts.push_back(tempPost);                      //Adds it to the beck of the checkpoint vector
    oppdaterTeamNyPost();                           //Adds a new point value of 0 to the back of every teams points vector.
}


/**
 * @brief Function that first asks which post user wants to edit, and then show all ways user can edit the post,
 *        and let's the user thn pick one of said options.
 */
void Rebus::editPost(){
    if (posts.size() > 0){                          //Checks if there is any checkpoints
        int postChoice;                             //Stores user choice of checkpoint
        int command;                                //Stores user input
        listPosts();
        postChoice = lesInt("Choose post to edit",1,posts.size());
        do{                                         //Loops until user input 0
            cout << "\n\n";
            cout << "Choose Option:\n"
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

/**
 * @brief Deletes a checkpoint. This function is currently not in use as the file system cannot handle holes in teams/posts/points vectors.
 * 
 */
void Rebus::deletePost(){
    if (posts.size() > 0){
        int command;                                //Assisting variable to store user input.
        listPosts();                                //Writes out a list of team members with index.
        command = lesInt("Choose post to delete",1,posts.size());
        posts[command-1] = posts[posts.size()-1];
        posts.pop_back();
    }
    else cout << "No posts available\n";
}


/**
 * @brief Prints information on all checkpoints. Currently not complete or used in program.
 * 
 */
void Rebus::listPosts(){
    for(int i=0; i < posts.size();i++){
        cout << "nr." << i+1 << ": ";
        posts[i]->writePostData();
        cout << '\n';
    }
    
}

/**
 * @brief Writes out menu and lets users register points to teams in two different ways.
 * 
 * @param mode By sending "quick", a command-like input will be started. By sending "detailed", a more idiot-proof reading system will instead be used.
 */
void Rebus::registerPoints(const string mode){
    int postNr,                                     //Temporary storage of checkpoint index selected by user.  
        teamNr,                                     //Temporary storage of team index selected by user.
        points,                                     //Temporary storage of points input by user.
        time;                                       //Temporary storage of time score input by user.
    bool failed;                                    //To store failbit results of user input.

    if(mode=="detailed"){                           //If parameter "detailed" is enabled
        cout << "Teams:\n";                     //Prints and reads what team and checkpoint the user want to add points to.
        listTeams(true,false);
        teamNr = lesInt("Choose team",1,teams.size())-1;
        cout << "\nCheckpoints:\n";
        listPosts();
        postNr = lesInt("Choose checkpoint",1,posts.size())-1;
        
        if(posts[postNr]->returnType()==1){         //If the checkpoint is point-based. Then reads point input.
            points = lesInt("Input points",0,posts[postNr]->returnMaxPoints());
        }else if(posts[postNr]->returnType()==2){   //If the checkpoint is time-based.
            time = lesInt("Input time",1,900);      //Reads time input
            points = posts[postNr]->timeToPoints(time); //Converts time input to points
        };
        teams[teamNr]->regPoints(postNr,points);    //Registers point values that user input.

    }else if(mode=="quick"){                        //If paramterer "quick" is enabled
        do{                                         //Loops until user input 0
            for(int i=0;i<100;i++)cout << "\n";     //Creats 100 newlines to clear screen

            cout << "Teams:\n";                     //lists all teams and checkpoints on screen
            listTeams(true,false);
            cout << "\nCheckpoints:\n";
            listPosts();

            failed=false;                           //Reset failed detector. This variable is set to true if any non-numeric inputs are registerd.

            cout << "\nInput syntax: <team nr> <post nr> <points/time>\n";
            cout << "Input Points(0 to exit): ";
            teamNr = lesInt2();                     //Reads team number
            if(teamNr>teams.size()||teamNr<0){failed=true;} //If a non-integer was sendt, or a non-existent team, the command failed.
            teamNr--;                               //Adjust input to real index
            if(teamNr!=-1&&failed==false){          //If the user has not typed '0' to exit or typed an illegal input, the function continues.
                postNr = lesInt2();                 //Reads checkpoint number and checks if it was a legal input.
                if(postNr>posts.size()||postNr<0){failed=true;}
                postNr--;                           //Adjust for real index.
                if(failed==false){                  //If both previous inputs have been legan.
                    if(posts[postNr]->returnType()==1){ //If the chosen checkpointwas points based.
                        points = lesInt2();         //Reads point input and detects if it is an illegal input.
                        if(points==-1){failed=true; points = 0;}
                        if(points>posts[postNr]->returnMaxPoints()&&failed==false){ //A point value exeeding the maximum is lowered to match this value.
                            points=posts[postNr]->returnMaxPoints();
                        };
                                                    //If the chosen checkpoint is time based and all previous inputs are legal.
                    }else if(posts[postNr]->returnType()==2&&failed==false){    
                        time=lesInt2();             //Reads time from user
                        if(time==-1){               //If the input was illegal
                            failed=true; points=0;
                        }else{                      //If the input was legal, the time is translated to points.
                            points = posts[postNr]->timeToPoints(time);
                        }
                    };
                    if(failed==false){teams[teamNr]->regPoints(postNr,points);} //registers points if all inputs are legal.
                }else{
                    cout << "ERROR: One or more inputs were invalid. Ignoring input.\n";
                }
            }else{
                cout << "ERROR: One or more inputs were invalid. Ignoring input.\n";
            }
        }while(teamNr!=-1);
        cin.ignore();                               //Clears buffer
    }
}


/**
 * @brief Lists all teams sorted by total points.
 * 
 */
void Rebus::showAllResults(){
    vector <int> blacklist;                         //the blacklist contains the teams that has already been printed
    int mostPoints=0,                               //Variable storing the highest point value of all teams
        bestTeam,                                   //Variable storing the indexs of the team with the most points
        i, k=1;                                     //Loop variables

    while(blacklist.size()<teams.size()){           //Will loop until every team on the list has beed added to the blacklist, meaning that the sorting is complete
        for(i = 0;i<teams.size();i++){              //Iterates through all teams
            if(mostPoints<=teams[i]->getTotalPoints()&&isBlackListed(i,blacklist)==false){ //If team has more points than current record-holder and is not on the blacklist.
                mostPoints=teams[i]->getTotalPoints(); //Updates the mostpoints variable
                bestTeam = i;                       //Saves the index of the team with the most points
            }
        };
        cout << k << ": ";                          //Writes the team with the most points on the screen
        k++;
        teams[bestTeam]->writeData(true,false);
        blacklist.push_back(bestTeam);              //Blacklists the best team, and reset the mostPoints variable.
        mostPoints=0;
    }
    int done = lesInt("Input 0 to return",0,0);     //User must type "0" to return to main menu.
}

/**
 * @brief Checks if a certain team is on the blacklist. Used in Rebus::showAllResults(); to sort teams by points.
 * 
 * @param nr index of team
 * @param blacklist vector of black-listed teams
 * @return true = the team was on the blacklist
 * @return false = the team was not on the blacklist.
 */
bool Rebus::isBlackListed(int nr, vector <int> blacklist){
    for(int i = 0;i<blacklist.size();i++){          //Iterates through blacklist and returns true if it can find the number.
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
    int i = 0;                                      //counts rebuser
    int id = -1;                                    //variable to identify next object in file. 0=end of rebus. 1=team. 2=checkpoint.
    cout << "Rebus::load() - Reading new rebus from file.\n";

    getline(input,name);                            //reads name of entire rebus       
    input >> checkpointAmount; input.ignore();      //reads amount of checkpoint and vector infomration.
    input >> id; input.ignore();


    while(id!=0){                                   //loops as long as there is remaining checkpoints or teams on this rebus.
        if(id==1){
            Team * newTeam = new Team;              //creates new team
            newTeam->fileRead(input,checkpointAmount);//reads team information.
            teams.push_back(newTeam);               //adds team to list.
        }         
        else if(id==2){
            Checkpoint * newPost = new Checkpoint;
            newPost->fileRead(input);;              //reads checkpoint information.
            posts.push_back(newPost);
        }    
        input >> id;                                //reads new id.
        cout << "Next ID: " << id << "\n";
        input.ignore();    
    }
}


/**
 * @brief Writes data from rebus into file.
 * 
 * @param output file stream to save data to.
 */
void Rebus::save(fstream & output){
    if(output.tellg()!=0){                          //writes a newline unless it's at the top of the file
        output << "\n";
    };
    output << name << "\n";                         //writes basic information.
    output << posts.size() << "\n";

    for(int i=0;i<teams.size();i++){                //iterates through all teams
        teams[i]->fileWrite(output);                //Writes team to file
    }
    for(int i=0;i<posts.size();i++){                //iterates through all checkpoints
        posts[i]->fileWrite(output);                //Writes checkpoint to file
    }
    output << "0";                                  //Writes "0" to file to signify that this rebus has no more information.
};


/**
 * @brief Believe it or not, but this function actually returns name of the Rebus! Incredible, right!?
 * 
 * @return string 
 */
string Rebus::returnName(){
    return name;
};


/**
 * @brief Returns amount of elements in posts vector in the rebus.
 * 
 * @return int
 */
int Rebus::returnPostNr(){
    return posts.size();
}

/**
 * @brief Adds a new value '0' to the end of points vector in every team. Used after a new checkpoint has been created.
 * 
 */
void Rebus::oppdaterTeamNyPost(){
    for(int i=0;i<teams.size();i++){            //Iterates through teams
        teams[i]->addEmptyScore();              //Adds 0 to points vector
    }
};

/**
 * @brief Reads data of a new rebus.
 * 
 */
void Rebus::readData(){
    cout << "Name new tournament: ";
    getline(cin,name);
}

/**
 * @brief Displays how many points each team has gotten on a specific checkpoint. This function is unfinished.
 * 
 *//*
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

/**
 * @brief Displays how many points a specific team has gotten on all the different checkpoints. This function is unfinished.
 * 
 *//*
void Rebus::showTeamResult(){

};
*/

/**
 * @brief Checks if rebus contains at least 1 checkpoint and 1 team.
 * 
 * @return true: There is at least 1 checkpoint and 1 team.
 * @return false: There is not.
 */
bool Rebus::readyToRead(){
    int ok=0;                                   //This actually does nothing
    if(posts.size()>0&&teams.size()>0){         //If there is a checkpoint and a team
        return true;
    }else if(posts.size()>0){                   //If there is a checkpoint0 but no team
        cout << "Error: Not enough teams to use this feature.\n";
        ok = lesInt("Input 0 to return.",0,0);
    }else if(teams.size()>0){                   //If there is a team but no checkpoint
        cout << "Error: Not enough checkpoints to use this feature.\n";
        ok = lesInt("Input 0 to return.",0,0);
    }else{                                      //If there is neither a team or checkpoint
        cout << "Error: At least 1 checkpoint and team are required to use this feature.\n";
        ok = lesInt("Input 0 to return.",0,0);
    }
}

#endif
