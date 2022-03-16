/**
 * @file Rebus.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Rebus class.
 * @version 0.0.0
 * @date 2022-03-14
 * 
 * 
 */


#include "Checkpoint.h"

#include <vector>
using namespace std;


/**
 * @brief Class containing all information on a specific game of rebus.
 * 
 */
class Rebus{
    private:
        vector <Checkpoint*> checkpoints;
        vector <Team*> teams;

    public:
        void newTeam();
};


/**
 * @brief Function that creates a new team object on the team vector. See team constructor on the following process of team creation.
 * 
 */
void Rebus :: newTeam(){
    Team * tempTeam = new Team;
    teams.push_back(tempTeam);
}