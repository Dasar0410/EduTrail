/**
 * @file main.cpp
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no), Daniel Pietrzykowski Sarjomaa (NTNU)
 * @brief Main file of Edutrail project.
 * @version 0.1.1
 * @date 2022-03-14
 *  
 */
// fjernet include Checkpoint fordi den skal ikke brukes direkte av main og skapte mange errorer
#include "LesData2.h"
#include "Team.h" 
#include "Rebus.h"
#include "miscFunctions.h"

#include <string>
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
void load(fstream & input);
void listRebus();

vector <Rebus*> gAlleRebuser;         //alle rebuser i save filen blir lastet inn her.
Rebus * gMainRebus = new Rebus;                     //den aktive rebus vi jobber på.


fstream gMainFile("saveFile.dta", ios::in | ios::out);  //Åpner fil.

/**
 *  Main Program:
 */
int main(){
    int command;
    
    do{
        writeMainMenu();
        
        command = lesInt("Choose a numeric option",0,6);    // er egt bare 5 valg i hovedmenyen men valg 6 burde vel eksistere så brukere
                                                            // kan avslutte programmet, right? - Daniel
        cout << '\n';
        switch(command){ //funksjonsnavn kan endres
            case 0: cout << "Terminating Program..."; break;
            case 1: teamMenu(); break;
            case 2: postsMenu(); break; 
            case 3: showResult(); break;
            case 4: registerResult(); break;
            case 5: showSettings(); break;
            default: writeMainMenu();
        }
        
    }while (command != 0);
}   

void writeMainMenu(){
    cout << "Main Menu:\n"
         << "\t1. Teams menu\n"
         << "\t2. Posts menu\n"
         << "\t3. Show results\n"
         << "\t4. Register points \n"
         << "\t5. Settings \n"
         << "\t0. Exit program \n";
}
//Teams Meny nedenfor og alle tilhørende funksjoner
//kan flyttes til egen fil senere?
void teamMenu(){
    int command;
    do{                                 //Loops until the user returns to main menu by inputting 0
        cout << "Choose Option:\n"
            << "\t1. New Team\n"
            << "\t2. Edit/Delete Team\n"
            << "\t3. Display Teams\n"
            << "\t0. Return to main menu\n";
            command = lesInt("Choose a numeric option",0,3);

        switch(command){
            case 1: gMainRebus->newTeam(); break;
            case 2: gMainRebus->editTeam(); break; //Will finish theese later.
            case 3: gMainRebus->listTeams(true,true); break;
            default: break;
        }
    }while(command!=0);

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
    cout << '\n';

    switch(command){
        case 1: gMainRebus->newPost(); break;
        case 2: gMainRebus->editPost(); break;
        case 3: gMainRebus->deletePost(); break; 
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
    gMainRebus->registerPoints();


    }



//registrer nye poeng slutt


// settings funksjoner start
void showSettings(){
    int command;
    do{
        cout << "Choose Option:\n"
            << "\t1. Save Game\n"
            << "\t2. Load Game\n"
            << "\t3. New Game\n"
            << "\t0. Return to main menu.\n";
        command = lesInt("Choose a numeric option",0,3);
        switch(command){
            case 0: break;
            case 1: gMainRebus->save(); break;
            case 2: load(gMainFile); break;
            //case 2: newRebus(); break;
            default: break;
        }
    }while(command!=0);
}

//settings funksjoner slutt

/**
 * @brief Reads information from document to different objects.
 * 
 * @param input 
 */
void load(fstream & input){
    input.seekg(0,ios::beg);    //begynner å lese fra toppen av scriptet
    int command;
    int i=0;
    Rebus * nyRebus;
    while(input.eof()==false){
        nyRebus = new Rebus;
        nyRebus->load(input);
        gAlleRebuser.push_back(nyRebus);
    }
    cout << "Choose Save: \n";
    listRebus();
    command = lesInt("Choose a numeric option",1,gAlleRebuser.size());
    gMainRebus = gAlleRebuser[command-1];          //copies the chosen rebus into the main 
};

void listRebus(){
    for(int i=0;i<gAlleRebuser.size();i++){
        cout << "\t"<< i+1 << ": " << gAlleRebuser[i]->returnName() << "\n";
    }
};

