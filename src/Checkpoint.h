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

enum checkpointMode{points,standardTime,rankedTime};        //Enum containing the game-types a checkpoint may use.

class Checkpoint{
    private:
        string name;
        string description;
        enum checkpointMode mode;
        int maxPoints;
        int nr;
};