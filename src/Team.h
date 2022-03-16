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
        void writeData(const bool showMembers);
        int getTotalPoints();

        Team(){                         //Reads data to team upon it's creation.
            readData();
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
void Team :: writeData(const bool showMembers){
    cout << "\t" << name;
    cout << ": " << getTotalPoints() << " poeng.\n";
    if(showMembers==true){
        for(int i = 0; i<participants.size();i++){      //loops through all participants in vector.
            cout << "\t\t" << participants[i] << "\n";
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