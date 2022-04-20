/**
 * @file Team.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Team class.
 * @date 2022-03-14
 * 
 * 
 */


#include "LesData2.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <string>
#include <list>
using namespace std;

class Team{
    private:
        string name;
        vector <string> participants;           //liste med navn på alle gruppemedlemmene.
        //!!!! point index for checkpoints that was removed must be set to -1.
        vector <int> points;                    //hvor mange poeng laget har for øyeblikket

    public:
        void readData(int antallPoster);
        void newMember();
        void writeData(const bool showName,const bool showMembers);
        int getTotalPoints();
        void writeEditMenu();
        void changeName();
        void editParticipant();
        void deleteParticipant();
        void editPoints();
        void addPoints(int postchoice,int maxpoints); // for poeng registrering med makspoengsum hentet fra post
        //void addPostPoint(){}
        void fileRead(fstream & input,int checkpointLength);
        void fileWrite(fstream & output);
        void addEmptyScore();
        string returnName();
        void regPoints(const int postNr, const int newPoints);
        int getPoint(const int postNr);

        Team(){

        }

        ~Team(){

        }
};


/**
 * @brief Simple fuction to add a single new member to the team.
 * 
 */
void Team :: newMember(){
    string tempName;                    //Assisting varaible
    cout << "Enter name of member: ";   
    getline(cin,tempName);              //gets string from user
    participants.push_back(tempName);   //Adds the string to the back of the participants vector.
    cout << "New participant \"" << tempName << "\" added to team.\n";
};
/**
 * @brief Reads in a new team and lets user add team members as long as he wants
 */
void Team :: readData(int antallPoster){
    char option;                        //assisting variable to store user menu input
    cout << "Choose a team name: ";
    getline(cin,name);                  //gets team tame from user as a string
    cout << "Do you want to add a new member? (y/n): ";
    cin >> option;                      //reads menu choice from user
    cin.ignore();                       //Deletes remaining \n
    while(toupper(option)=='Y'){        //Will loop as long as user answers 'y' when asked if they want to add another member.
        newMember();                    //adds a new member. see function documentation.
        cout << "Do you want to add another member? (y/n): ";
        cin >> option;                  //reads in user input to restart loop.
        cin.ignore();                   //Ignores remaining \n that was not reginsterd by the cin commmand.
    }
    
    for(int i=0;i<antallPoster;i++){ //adds default scores into points vector
        points.push_back(0);
    }


    cout << "New team \"" << name << "\" added.\n";
};

/**
 * @brief Writes out the informnation of the team in a readable format for the user.
 * 
 * @param showMembers If set to true, the function will also display each individual team member. 
 * 
 * @see getTotalPoints()
 */
void Team :: writeData(const bool showName,const bool showMembers){
    if(showName==true){                                 //shows name and points if setting is enabled
        cout << "\t" << name;
        cout << ": " << getTotalPoints() << " poeng.\n";
    }
    if(showMembers==true){
        for(int i = 0; i<participants.size();i++){      //loops through all participants in vector.
            if(showName==true){cout << "\t";}           //add one extra tab if team name is shown.
            else{cout << i+1 << ":";}                   //Shows index if in participants only mode
            cout << "\t" << participants[i] << "\n";
        }
    }
}

/**
 * @brief Returns the tootal of all indexes of points.
 * 
 * @return The total point value.
 */
int Team :: getTotalPoints(){
    int total=0;
    for(int i = 0;i<points.size();i++){         //Loops through all indexes/checkpoints in points vector.
        total = total + points[i];              //adds current index to total value
    }
    return total;
}


/* foreløpig visklet ut pga bedre løsning i rebus.cpp?
void Team :: edit(){
    int command;
    writeEditMenu();
    command = lesInt("Choose Option",1,5);

    switch(command){
        case 1: changeName(); break;
        case 2: editParticipant(); break;
        case 3: deleteParticipant(); break;
//        case 4: editPoints(); break;
        default: cout << "Returning to main menu...\n"; break;
    }
}
*/

/**
 * @brief Writes on a menu to use when editing teams.
 * 
 */
void Team :: writeEditMenu(){
    cout << "\n\n";
    cout << "Choose Option:\n";
    cout << "\t1. Change team name\n";
    cout << "\t2. Change name of participant\n";
    cout << "\t3. Delete participants\n";
    cout << "\t0. Cancel\n";
}


/**
 * @brief Function to let users change the name of the team.
 * 
 */
void Team :: changeName(){
    string tempNewName;
    cout << "Current team name: " << name << "\n";
    cout << "Choose new team name: ";
    getline(cin,tempNewName);
    name = tempNewName;
    cout << "Changed team name to " << tempNewName << ".\n";
    
}


/**
 * @brief Function to let user change name of participants.
 * 
 */
void Team :: editParticipant(){
    int command;
    cout << "All participants\n";
    writeData(false,true);
    command = lesInt("Choose participant",1,participants.size());
    cout << "Participant " << participants[command-1] << "chosen.\nEnter new name: ";
    getline(cin,participants[command-1]);
    cout << "Name changed to " << participants[command-1] << "\n";
}


/**
 * @brief Function to let users delete a member of a team.
 * 
 */
void Team :: deleteParticipant(){
    int command;                    //Assisting variable to store user input.
    cout << "All participants\n";  
    writeData(false,true);          //Writes out a list of team members with index.
    command = lesInt("Choose participant",1,participants.size());
    cout << "Participant " << participants[command-1] << "chosen. Deleting...\n";
    participants[command-1] = participants[participants.size()-1];
    participants.pop_back();
}
/**
 * @brief Function to let users edit points for all avaible posts for one team
 * 
 */
void Team :: editPoints(){ 
    if(points.size() < 0){
    cout << "Team: " << name << "\nCurrent points: " << getTotalPoints() << '\n'; //føler at points vectoren er litt rar å jobbe med
    for (int i = 0; i < points.size();i++){
        cout << "Points for post nr." << i+1 << ": " << points[i] << '\n'; //shows points for each post 
        points[i] = lesInt("Change points for this post",0,99); // 
    }
    cout << "Updated total points for team is now: " << getTotalPoints(); //shows updated total points for users
    }
    else cout << "There are no posts registered on team";
    //hmmm hmmm hmmm
}

void Team :: addPoints(int postchoice,int maxpoints){
    if(1 == 1){ // skal legge til sjekk her
    int tempPoints;
    tempPoints = lesInt("Skriv inn nye poeng for valgt post",0,maxpoints);
    points[postchoice] = tempPoints;    //inserts the points at the index of the post
    }
}



/**
 * @brief Reads a short snippet of information from the main document. Made to work in sequesne with other read functions.
 * 
 * @param input file object.
 * @param checkpointLength Amount of enabled indexes in the posts vector.
 */
void Team :: fileRead(fstream & input,int checkpointLength){
    string newParticipant;  //temporary storage for participant name.
    cout << "Team::fileRead - Reading new team from file.\n";
    cout << "Team::fileRead - Checkpoint length: " << checkpointLength << "\n";
    getline(input,name);
    do{                                 //Loops and records particiapnts until there is a line with "0"
        getline(input,newParticipant);
        //cout << "\tTeam::fileRead - New Participant: \"" << newParticipant << "\"\n";
        participants.push_back(newParticipant);
    }while(newParticipant!="return");
    participants.pop_back();            //deletes last string containing "0"
    cout << "\tTeam::fileRead - All participants added. In total " << participants.size() << " were added to team.\n";

    int tempPoints;
    for(int i=0;i<checkpointLength;i++){ //loops through all checkpoints
        input >> tempPoints;
        points.push_back(tempPoints);
        input.ignore();
    };
    cout << "\tTeam::fileRead - Points added from file.\n";
};

/**
 * @brief Writes the content of a team into the file.
 * 
 * @param output 
 */
void Team::fileWrite(fstream & output){
    output << "1\n";                        //identiefies this as a team
    output << name << "\n";
    for(int i=0;i<participants.size();i++){ //loops thorugh all participants and writes them out.
        output << participants[i] << "\n";
    };
    output << "return\n";                   //"return" marks the end of the participant list
    for(int i=0;i<points.size();i++){       //this will probably break at some point, but i would rather not think ahead and plan right now so it will stay like this for now.
        output << points[i] << " ";         //writes out points from each individual checkpoint
    }
    output << "\n";
};

/**
 * @brief Adds 0 at end of points vector. For use after a new post has been made.
 * 
 */
void Team::addEmptyScore(){
    points.push_back(0);
}


void Team::regPoints(const int postNr, const int newPoints){
    points[postNr]=newPoints;
};


int Team::getPoint(const int postNr){
    return points[postNr];
};
