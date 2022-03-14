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
};