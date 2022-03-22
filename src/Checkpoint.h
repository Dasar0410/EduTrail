/**
 * @file Checkpoint.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containg the definitions and functions of the Checkpoint class.
 * @version 0.0.0
 * @date 2022-03-14
 * 
 * 
 */

#include "LesData2.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


enum checkpointMode{points,standardTime,rankedTime};        //Enum containing the game-types a checkpoint may use.

class Checkpoint{
    private:
        string name;
        string description;
        enum checkpointMode mode;
        int maxPoints; // maxpoints able to be scored on a post
        int nr;
    public:
        void readPostData();
        void writePostData();
        void editDescription();
        void editPostnr();
        void editMaxPoints();
        int postNumber();
        int returnMaxPoints();
        void fileRead(fstream & input);
        Checkpoint(){

        }
};

/**
 * @brief Function that reads in data for one post
 */
void Checkpoint::readPostData(){
    int userInput;
    cout << "Postname: "; getline(cin,name);
    cout << '\n';
    cout << "Description: "; getline(cin,description);
    cout << '\n';
    userInput = lesInt("Choose post type (points,standardTime,Rankedtime)",0,2);
    checkpointMode mode = static_cast<checkpointMode>(userInput); // effective method to convert userInput to chosen enum
    maxPoints = lesInt("Maxpoints for post",1,99);
}
/**
 * @brief Function that writes all data for one post
 */
void Checkpoint::writePostData(){
    cout << "postname: " << name << ", Maxpoints: " << maxPoints;

}
/**
 * @brief Function that edits description for a post
 */
void Checkpoint::editDescription(){

}
/**
 * @brief Function that edits maxpoints for a post
 */
void Checkpoint::editMaxPoints(){

}

int Checkpoint :: returnMaxPoints(){
    return maxPoints;
}

/**
 * @brief Also lazy solution. returns nr
 *          not currently used
 */
int Checkpoint::postNumber(){
    return nr;
}


void Checkpoint::fileRead(fstream & input){
    cout << "Checkpoint::fileRead - reading new checkpoint from file.\n";
    int tempMode;                                       //variable for storing game mode as integer before casting
    getline(input,name);
    getline(input,description);
    input >> tempMode >> maxPoints >> nr;               
    mode = static_cast <enum checkpointMode>(tempMode); //gjør om int til enum.
    input.ignore();                                     //ignores newline
}

