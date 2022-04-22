/**
 * @file Checkpoint.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containg the definitions and functions of the Checkpoint class.
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
 * @brief Reads user input to fill post data.
 */
void Checkpoint::readPostData(){            
    int userInput;                              //reads user input
    cout << "Postname: "; getline(cin,name);
    cout << '\n';
    cout << "Description: "; getline(cin,description);
    cout << '\n';
    mode = lesInt("Choose post type (1 = Points, 2= Time)",1,2);
    maxPoints = lesInt("Maxpoints for post",1,99);
    if(mode==2){                                //If the checkpoint is time based
        bestTime = lesInt("Time for best score(sec)",1,900);
        worstTime = lesInt("Worst time that still gives points(sec)",1,900);
    }else if(mode==1){                          //If the checkpoint is point based
        bestTime=-1;
        worstTime=-1;
    }
}

/**
 * @brief Function that writes all data for one post
 */
void Checkpoint::writePostData(){
    cout << name << ":\t";
    if(mode==1){                                //If bestTime=-1 the checkpoint is purely point based.
        cout << "Gamemode: Points";
        cout << "(Max " << maxPoints << ")";
    }else{                                      //If checkpoint is time based
        cout << "Gamemode: Time";
        if(bestTime>worstTime){                 //If the checkpoint is a "faster is better" type
            cout << "(Best result is " << maxPoints << " points at a time of " << bestTime << " seconds. A time lower than " << worstTime << " seconds yields no points.)";
        }else{                                  //if the checkpoint is a "the longer time the better score" type
            cout << "(Best result is " << maxPoints << " points at a time of " << bestTime << " seconds. After " << worstTime << " seconds no points are rewarded.)";
        }
    }

}
/**
 * @brief Let user edit description for a post
 */
void Checkpoint::editDescription(){
    cout << "Current description: " << description << "\n";
    cout << "Write in new description: "; getline(cin,description);
}

/**
 * @brief Lets user edit maxpoints for a post
 */
void Checkpoint::editMaxPoints(){
    cout << "Current maxpoints: " << maxPoints << '\n';
    maxPoints = lesInt("Write in new maxpoints",0,99);
}

/**
 * @brief Returns the max amout of points you can get from a checkpoint.
 * 
 * @return int 
 */
int Checkpoint :: returnMaxPoints(){
    return maxPoints;
}

/**
 * @brief Returns the index of the post. Not currently used.
 */
int Checkpoint::postNumber(){
    return nr;
}

/**
 * @brief Reads data from the file into a single checkpoint.
 * 
 * @param input The file stream that the function reads from.
 */
void Checkpoint::fileRead(fstream & input){
    cout << "Checkpoint::fileRead - reading new checkpoint from file.\n";
    getline(input,name);
    getline(input,description);
    input >> mode >> maxPoints >> bestTime >> worstTime;  
    cout << mode << " " << maxPoints << " " << bestTime << " " << worstTime << "\n";             
    input.ignore();                                 //ignores newline
}

/**
 * @brief Writes the content of a checkpoint into the file.
 * 
 * @param output The file stream that the function writes to.
 */
void Checkpoint::fileWrite(fstream & output){
    output << "2\n";                                //All "elements" in the file begins with an ID number.
    output << name << "\n";
    output << description << "\n";
    output << mode << " " << maxPoints << " " << bestTime << " " << worstTime << "\n";
};


/**
 * @brief Calculates how many points are rewarded based on the specific checkpoints settings and the time.
 * 
 * @param time The time that will be translated to points.
 * @return int: How many points are given.
 */
int Checkpoint::timeToPoints(int time){
    float   fPercent;                               //Float value containging how many percent of the maximum amount of points will be given.
    int     iPercent,                               //The same as above, but as an integer.
            points,                                 //Contains how many points will be given.
            newWorstTime,                           //worst time after removing the part of the time that doesn't matter for the score.
            newBestTime;                            //best time after removing the part of the time that doesn't matter for the score.

    if(bestTime > worstTime){                       //If the checkpoint is a "more time, better score" type, this will run.
        if(time>bestTime){time=bestTime;}           //Adjust time so that it doesn't exeed the best or worst value, and stays within the allowed margins.
        if(time < worstTime){time = worstTime;}
        newBestTime = bestTime-worstTime;           //finds the span of time witch points are counted.
        time = time-worstTime;                      //Removes the worst time from the time
        fPercent = static_cast<float>(time) / static_cast<float>(newBestTime);  //Finds how many percent of the point-giving duration the participant had.
        iPercent = static_cast<int>(fPercent*100);  //Converts to integer
        points = (iPercent*maxPoints)/100;          //Multiplies the percentage of perfect time with the maximum score, giving the amount of points rewarded for the checkpoint.
    }else{                                          //If the checkpoint is a "faster is better" type, this will run.
        if(time<bestTime){time=bestTime;}           //Adjust time so that it doesn't exeed the worst and best time.
        if(time > worstTime){time = worstTime;}
        newWorstTime=worstTime-bestTime;            //the new worst time is the duration when the amount of points diminish
        time = time-bestTime;                       //removes the non-point giving part of the time

        fPercent = static_cast<float>(time) / static_cast<float>(newWorstTime); //Finds how many percent of the point-giving duration the time was.
        iPercent = static_cast<int>(fPercent*100);  //Converts to integer
        iPercent = 100-iPercent;                    //Inverts the percentage, so that it will give more points when time is lower.
        points = (iPercent*maxPoints)/100;          //Percent of perfect time multiplied by max points gives the rewarded amount of points.
    }
    return points;                                  //Returns the amount of points.
};


/**
 * @brief Returns the type of the checkpoint
 * 
 * @return int: 1=point, 2=time
 */
int Checkpoint::returnType(){
    return mode;
}

/**
 * @brief Lets user edit checkpoint name
 * 
 */
void Checkpoint::editName(){
    cout << "Input new name: ";
    getline(cin,name);
    cout << "Name changed to \""<< name << "\".\n"; 
}

/**
 * @brief Lets user change the gamemode.
 * 
 */
void Checkpoint::editGamemode(){
    char command;                                   //Stores user input
    if(mode==1){                                    //If the checkpoint is already point based
        cout << "Standard points mode is currently selected for this checkpoint.\n";
        command = lesChar("Switch to time based game mode?(y/n)");
        if(toupper(command)=='Y'){                  //If user confirms change of game mode
            mode=2;
            bestTime=lesInt("Choose the time of completion that grants full score",1,900);
            worstTime=lesInt("Choose the time of completion that gives no longer gives points.",1,900);
            cout << "Changes to checkpoint has been saved.\n";
        }else{
            cout << "Canceling changes...\n";
        }
    }else if(mode==2){                              //if the checkpoint is already time based
        cout << "Time mode is currently selected for this checkpoint.\n";
        command = lesChar("Switch to point based game mode?(y/n)");
        if(toupper(command)=='Y'){                  //If user confirms change of game mode
            mode=1;
            bestTime=-1;                            //Sets time values to -1, wich is recognized by other functions as mode 1
            worstTime=-1;
            cout << "Changes to checkpoint has been saved.\n";
        }else{
            cout << "Canceling changes...\n";
        }
    }
}