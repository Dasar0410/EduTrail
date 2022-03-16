/**
 * @file main.cpp
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no), Daniel Pietrzykowski Sarjomaa (NTNU)
 * @brief Main file of Edutrail project.
 * @version 0.1.0
 * @date 2022-03-14
 *  
 */

#include "LesData2.h"
#include "Checkpoint.h"
#include "Team.h"
#include "Rebus.h"
#include "miscFunctions.h"

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

void writeMainMenu();
void teamMenu();
void postsMenu();
void showResult();
void registerResult();
void showSettings();


Rebus gMainRebus;           //den aktive rebus vi jobber på

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
            case 2: postsMenu(); break; 
            case 3: showResult(); break;
            case 4: registerResult(); break;
            case 5: showSettings(); break;
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
//Teams Meny nedenfor og alle tilhørende funksjoner
//kan flyttes til egen fil senere?
void teamMenu(){
    int command;
    cout << "Choose Option:\n"
         << "\t1. New Team\n"
         << "\t2. Edit Team\n"
         << "\t3. Delete Team\n";
    command = lesInt("Choose a numeric option",1,3);

    switch(command){
        case 1: gMainRebus.newTeam(); break;
//        case 2: gMainRebus.editTeam(); break; //Will finish theese later.
//        case 3: gmainRebus.deleteTeam(); break;
        default: break;
        }
}
// team funksjoner slutt



// posts meny funksjoner
void postsMenu(){
    int command;
    cout << "Choose Option:\n"
         << "\t1. New post\n"
         << "\t2. Edit post\n"
         << "\t3. Delete post\n";
    command = lesInt("Choose a numeric option",1,3);

    switch(command){
        //case 1: newPost(); break;
        //case 2: editPost(); break;
        //case 3: deletePost(); break;
        default: break;
        }
}

//post funksjoner slutt

//resultat funksjoner start
void showResult(){
    int command;
    cout << "Choose Option:\n"
         << "\t1. Show all results\n"
         << "\t2. Show points for select team\n"
         << "\t3. Show points for select post\n";
    command = lesInt("Choose a numeric option",1,3);

    switch(command){
        //case 1: showAllResults(); break;
        //case 2: showTeamResult(); break;
        //case 3: showPostResult(); break;
        default: break;
        }
}

// resultat funksjoner slutt

//registrer poeng funksjoner start
void registerResult(){
    // registrer poeng for ett lag

    }



//registrer nye poeng slutt


// settings funksjoner start
void showSettings(){
    int command;
    cout << "Choose Option:\n"
         << "\t1. Save tournament\n"
         << "\t2. Create new tournament\n";
    command = lesInt("Choose a numeric option",1,3);

    switch(command){
        //case 1: saveTournament(); break;
        //case 2: createTournament(); break;
        default: break;
        }
}

//settings funksjoner slutt