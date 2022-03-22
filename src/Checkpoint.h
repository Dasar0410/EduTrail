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
        void readPostData();
        void newPost();
        void editPost();
        void writePostData();
        int postNumber();
        Checkpoint(){ // tom constructor cause why not
        }
};
/**
 * @brief Function that adds new post and adds to vector
 */
void Checkpoint::newPost(){
    Checkpoint* tempPost = new Checkpoint;
    tempPost->readPostData();
    posts.push_back(tempPost);
}
/**
 * @brief Function that reads in data for one post
 */
void Checkpoint::readPostData(){
    int userInput;
    cout << "Postname: "; getline(cin,name);
    cout << '\n';
    cout << "Description: "; getline(cin,description);
    cout << '\n';
    nr = lesInt("nr",0,99);
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
 * @brief Function that first prints out all posts and let's user choose a post and how to edit selected post
 */
void Checkpoint::editPost(){

}

/**
 * @brief Also lazy solution. returns nr
 */
int Checkpoint::postNumber(){
    return nr;
}

