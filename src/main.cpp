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
void teamMenu();

/**
 *  Main Program:
 */
int main(){
    int command;
    
    do{
        writeMainMenu();
        
        command = lesInt("Choose a numeric option",1,6); // er egt bare 5 valg i hovedmenyen men valg 6 burde vel eksistere så brukere
                                                            // kan avslutte programmet, right? - Daniel
        cout << '\n';
        switch(command){ //funksjonsnavn kan endres
            case 1: teamMenu(); break;
            //case 2: postsMenu(); break; 
            //case 3: showResults(); break;
            //case 4: registerPoints(); break;
            //case 5: Settings(); break;
            case 6: break;
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

void teamMenu(){
    int command;
    cout << "Choose Option:\n"
         << "\t1. New Team\n"
         << "\t2. Edit Team\n"
         << "\t3. Delete Team\n";
    command = lesInt("Choose a numeric option",1,3);
    
    switch(command){
        //case 1: newTeam(); break;
        //case 2: editTeam(); break;
        //case 3: deleteTeam(); break;
        default: break;
        }




}



