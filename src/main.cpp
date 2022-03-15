/**
 * @file main.cpp
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no)
 * @brief Main file of Edutrail project.
 * @version 0.0.0
 * @date 2022-03-14
 *  
 */

#include "LesData2.h"
/**
#include "Rebus.h"
#include "Checkpoint.h"
#include "Team.h"
#include "miscFunctions.h"
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void writeMainMenu();


int main(){
    char command;
    do{
        writeMainMenu();
        command = lesInt("Choose a number option",1,6); // er egt bare 5 valg i hovedmenyen men valg 6 burde vel eksistere så brukere
                                                            // kan avslutte programmet, right? - Daniel
        switch(command){
            //case '1': teamMenu(); break;
            //case '2': postsMenu(); break;
            //case '3': showResults(); break;
            //case '4': registerPoints(); break;
            //case '5': Settings(); break;
            //case '6': break;
            default: writeMainMenu();
        }
        
    }while (command != 6);
}   

void writeMainMenu(){
    cout << "Main Menu:\n"
         << "\t1. Teams menu\n"
         << "\t2. Posts menu\n"
         << "\t3. Show results\n"
         << "\t4. Register points \n"
         << "\t5. Settings \n"
         << "\t6. Exit program \n";
}


