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



class Checkpoint{
    private:
        string name;
        string description;
        int mode;
        int maxPoints; // maxpoints able to be scored on a post
        int nr;
        int bestTime, worstTime;
        
    public:
        void readPostData();
        void writePostData();
        void editDescription();
        void editPostnr();
        void editMaxPoints();
        int postNumber();
        int returnMaxPoints();
        void fileRead(fstream & input);
        void fileWrite(fstream & output);
        int timeToPoints(int time);
        int returnType();
        void editName();
        void editGamemode();
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
    mode = lesInt("Choose post type (1 = Points, 2= Time)",1,2);
    maxPoints = lesInt("Maxpoints for post",1,99);
    if(mode==2){
        bestTime = lesInt("Time for best score(sec)",1,900);
        worstTime = lesInt("Worst time that still gives points(sec)",1,900);
    }else if(mode==1){
        bestTime=-1;
        worstTime=-1;
    }
}

/**
 * @brief Function that writes all data for one post
 */
void Checkpoint::writePostData(){
    cout << name << ":\t";
    if(bestTime==-1){
        cout << "Gamemode: Points";
        cout << "(Max " << maxPoints << ")";
    }else{
        cout << "Gamemode: Time";
        if(bestTime>worstTime){
            cout << "(Best result is " << maxPoints << " points at a time of " << bestTime << " seconds. A time lower than " << worstTime << " seconds yields no points.)";
        }else{
            cout << "(Best result is " << maxPoints << " points at a time of " << bestTime << " seconds. After " << worstTime << " seconds no points are rewarded.)";
        }
    }

}
/**
 * @brief Function that edits description for a post
 */
void Checkpoint::editDescription(){
    cout << "Current description: " << description << "\n";
    cout << "Write in new description: "; getline(cin,description);
}
/**
 * @brief Function that edits maxpoints for a post
 */
void Checkpoint::editMaxPoints(){
    cout << "Current maxpoints: " << maxPoints << '\n';
    maxPoints = lesInt("Write in new maxpoints",0,99);
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

/**
 * @brief Reads data from the file into a single checkpoint.
 * 
 * @param input 
 */
void Checkpoint::fileRead(fstream & input){
    cout << "Checkpoint::fileRead - reading new checkpoint from file.\n";
    getline(input,name);
    getline(input,description);
    input >> mode >> maxPoints >> bestTime >> worstTime;  
    cout << mode << " " << maxPoints << " " << bestTime << " " << worstTime << "\n";             
    input.ignore();                                     //ignores newline
}

/**
 * @brief Writes the content of a checkpoint into the file.
 * 
 * @param output 
 */
void Checkpoint::fileWrite(fstream & output){
    output << "2\n";
    output << name << "\n";
    output << description << "\n";
    output << mode << " " << maxPoints << " " << bestTime << " " << worstTime << "\n";
};


int Checkpoint::timeToPoints(int time){
    float fPercent;
    int iPercent, points, newWorstTime, newBestTime;
    if(bestTime > worstTime){ // jo lenger tid, jo mer poeng
        if(time>bestTime){time=bestTime;}
        if(time < worstTime){time = worstTime;}
        newBestTime = bestTime-worstTime;
        time = time-worstTime;
        fPercent = static_cast<float>(time) / static_cast<float>(newBestTime);
        iPercent = static_cast<int>(fPercent*100);
        points = (iPercent*maxPoints)/100;
    }else{                      //jo mindre tid, jo mer poeng
        if(time<bestTime){time=bestTime;}
        if(time > worstTime){time = worstTime;}
        newWorstTime=worstTime-bestTime;
        time = time-bestTime;

        fPercent = static_cast<float>(time) / static_cast<float>(newWorstTime);
        iPercent = static_cast<int>(fPercent*100);
        iPercent = 100-iPercent;
        points = (iPercent*maxPoints)/100;
    }
    return points;
};


int Checkpoint::returnType(){
    return mode;
}


void Checkpoint::editName(){
    cout << "Input new name: ";
    getline(cin,name);
    cout << "Name changed to \""<< name << "\".\n"; 
}

void Checkpoint::editGamemode(){
    char command;
    if(mode==1){
        cout << "Standard points mode is currently selected for this checkpoint.\n";
        command = lesChar("Switch to time based game mode?(y/n)");
        if(toupper(command)=='Y'){
            mode=2;
            bestTime=lesInt("Choose the time of completion that grants full score",1,900);
            worstTime=lesInt("Choose the time of completion that gives no longer gives points.",1,900);
            cout << "Changes to checkpoint has been saved.\n";
        }else{
            cout << "Canceling changes...\n";
        }
    }else if(mode==2){
        cout << "Time mode is currently selected for this checkpoint.\n";
        command = lesChar("Switch to point based game mode?(y/n)");
        if(toupper(command)=='Y'){
            mode=1;
            bestTime=-1;
            worstTime=-1;
            cout << "Changes to checkpoint has been saved.\n";
        }else{
            cout << "Canceling changes...\n";
        }
    }
}