/**
 * @file Team.h
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief File containing definitions and functions of Team class.
 * @version 0.0.0
 * @date 2022-03-14
 * 
 * 
 */


#include "LesData2.h"

#include <vector>
using namespace std;

class Team{
    private:
        string name;
        vector <string> participants;
        vector <int> points;
};