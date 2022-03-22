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
        void writeEditMenu();
        void changeName();;
        void editParticipant();
        void deleteParticipant();
        void editPoints();
        void addPoints(int postchoice,int maxpoints); // for poeng registrering med makspoengsum hentet fra post
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
    cout << "Enter name of member: ";   
    getline(cin,tempName);              //gets string from user
    participants.push_back(tempName);   //Adds the string to the back of the participants vector.
    cout << "New participant \"" << tempName << "\" added to team.\n";
};
/**
 * @brief Reads in a new team and lets user add team members as long as he wants
 */
void Team :: readData(){
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
    cout << "Choose Option:\n";
    cout << "\t1. Change team name\n";
    cout << "\t2. Change name of participant\n";
    cout << "\t3. Delete participants\n";
    cout << "\t4. Set/Override points\n";
    cout << "\t0. Cancel\n";
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
    cout << "Name changed to " << participants[command-1] << "\nReturning...";
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
    points[1] = lesInt("How many points did the team score on this post",0,maxpoints);
}

/**
 * @brief i think my brain is in offline mode, so i really can't be bothered to find a better solution.
 *          what is this function used for?? enter answer here:
 * @return string 
 */
string Team :: returnName(){
    return name;
}