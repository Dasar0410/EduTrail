/**
 * @file Team.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Team class.
 * @version 0.3.0
 * @date 2022-03-14
 * 
 * 
 */


#include "LesData2.h"
#include <iostream>
#include <vector>
#include <cctype>
#include <string>
using namespace std;

class Team{
    private:
        string name;
        vector <string> participants;           //liste med navn på alle gruppemedlemmene.
        vector <int> points;                    //hvor mange poeng laget har for øyeblikket

    public:
        void readData();
        void newMember();
        void writeData(const bool showName,const bool showMembers);
        int getTotalPoints();
        void edit();
        void writeEditMenu();
        void changeName();;
        void editParticipant();
        void deleteParticipant();
        void editPoints();
        string returnName();

        Team(){                         //Reads data to team upon it's creation.
            readData();
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
    cin.ignore();
    cout << "Enter name of member: ";   
    getline(cin,tempName);              //gets string from user
    participants.push_back(tempName);   //Adds the string to the back of the participants vector.
    cout << "New participant \"" << tempName << "\" added to team.\n";
};

void Team :: readData(){
    char option;                        //assisting variable to store user menu input
    cout << "Choose a team name: ";
    getline(cin,name);                  //gets team tame from user as a string
    cout << "Do you want to add a new member? (y/n): ";
    cin >> option;                      //reads menu choice from user
    while(toupper(option)=='Y'){        //Will loop as long as user answers 'y' when asked if they want to add another member.
        newMember();                    //adds a new member. see function documentation.
        cout << "Do you want to add another member? (y/n): ";
        cin >> option;                  //reads in user input to restart loop.
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


/**
 * @brief Writes on a menu to use when editing teams.
 * 
 */
void Team :: writeEditMenu(){
    cout << "Choose Option:\n";
    cout << "\t1. Change team name\n";
    cout << "\t2. Change name of participant\n";
    cout << "\t3. Delete participants\n";
    cout << "\t4. Set/Override points\n";
    cout << "\t5. Cancel\n";
}


/**
 * @brief Function to let users change the name of the team.
 * 
 */
void Team :: changeName(){
    string tempNewName;
    cout << "Current team name: " << name;
    cout << "\n Choose new team name: ";
    getline(cin,tempNewName);
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
    cout << "Name changed to " << participants[command-1] << ". Returning...";
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
    cout << "Participant " << participants[command-1] << "chosen. Deleting...";
    participants[command-1] = participants[participants.size()-1];
    participants.pop_back();
}

void Team :: editPoints(){
    //hmmm
}

/**
 * @brief i think my brain is in offline mode, so i really can't be bothered to find a better solution.
 * 
 * @return string 
 */
string Team :: returnName(){
    return name;
}