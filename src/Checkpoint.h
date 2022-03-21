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
        vector <Checkpoint*> posts;
    public:
        void readData();
        void newPost(); // lager et nytt objekt og legger den inn i post vector
        Checkpoint(){
            
        }
};
/**
 * @brief Function that adds new post and adds to vector
 * 
 */
void Checkpoint::newPost(){
    Checkpoint* tempPost = new Checkpoint;
    tempPost->readData();
    posts.push_back(tempPost);
}
/**
 * @brief Function that adds new post and adds to vector
 * 
 */
void Checkpoint::readData(){
    int userInput;
    cout << "Postname: "; getline(cin,name);
    cout << '\n';
    cout << "Description: "; getline(cin,description);
    cout << '\n';
    nr = lesInt("nr",0,99);
    userInput = lesInt("Choose post type (points,standardTime,Rankedtime)",0,2);
    checkpointMode mode = static_cast<checkpointMode>(userInput);

}

