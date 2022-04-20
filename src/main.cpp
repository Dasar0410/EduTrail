/**
 * @file main.cpp
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no), Daniel Pietrzykowski Sarjomaa (NTNU)
 * @brief Main file of Edutrail project.
 * @version 2.1.0
 * @date 2022-04-14
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
void load(fstream & input, const bool promptNew, const bool skipSelect);
void save(fstream & output);
void listRebus();
void newRebus();
void createSpace(const int newLines);


vector <Rebus*> gAlleRebuser;         //alle rebuser i save filen blir lastet inn her.
Rebus * gMainRebus = new Rebus;       //den aktive rebus vi jobber på.

fstream gMainFile("saveFile.dta", ios::in | ios::out);  //Åpner fil.

/**
 *  Main Program:
 */
int main(){
    if(gMainFile){
        gMainFile.seekg(0, ios::end);  
        if(gMainFile.tellg()==0){   //detects if file is empty
            gMainRebus->readData();
            gAlleRebuser.push_back(gMainRebus);
        }else{
            load(gMainFile,true,false);
            createSpace(100);
        };


        int command;    
        do{
            writeMainMenu();
            
            command = lesInt("Choose a numeric option",0,5);    // er egt bare 5 valg i hovedmenyen men valg 6 burde vel eksistere så brukere
                                                                // kan avslutte programmet, right? - Daniel
            cout << '\n';
            switch(command){ //funksjonsnavn kan endres
                case 0: cout << "Terminating Program...\n"; break;
                case 1: createSpace(100); teamMenu(); break;
                case 2: createSpace(100); postsMenu(); break; 
                case 3: createSpace(100); gMainRebus->showAllResults(); break;
                case 4: createSpace(100); registerResult(); break;
                case 5: createSpace(100); showSettings(); break;
                default: createSpace(100); writeMainMenu();
            }                  
        }while (command != 0);
        save(gMainFile);
    }else{
        cout << "Error: Cannot find file \"saveFile.dta\"\n";
        cout << "Terminating Program...\n";
    }
    

}   
void writeMainMenu(){
    createSpace(100);
    cout << "           _    _______        _ _\n          | |  |__   __|      (_) |\n   ___  __| |_   _| |_ __ __ _ _| |\n  / _ \\/ _` | | | | | '__/ _` | | |\n |  __/ (_| | |_| | | | | (_| | | |\n  \\___|\\__,_|\\__,_|_|_|  \\__,_|_|_|\n\n";
    cout << " Main Menu: " << gMainRebus->returnName() << "\n"
         << "\t1. Teams menu\n"
         << "\t2. Posts menu\n"
         << "\t3. Show results\n"
         << "\t4. Register points \n"
         << "\t5. Manage Saves\n"
         << "\t0. Exit\n";
}
//Teams Meny nedenfor og alle tilhørende funksjoner
//kan flyttes til egen fil senere?
void teamMenu(){
    int command;
    do{                                 //Loops until the user returns to main menu by inputting 0
        createSpace(2);
        cout << "Choose Option:\n"
            << "\t1. New Team\n"
            << "\t2. Edit Team\n"
            << "\t3. Display Teams\n"
            << "\t0. Return to main menu\n";
            command = lesInt("Choose a numeric option",0,3);

        switch(command){
            case 1: createSpace(2); gMainRebus->newTeam(); break;
            case 2: createSpace(2); gMainRebus->editTeam(); break; //Will finish theese later.
            case 3: createSpace(2); gMainRebus->listTeams(true,true); break;
            default: break;
        }
    }while(command!=0);

}
// team funksjoner slutt



// posts meny funksjoner
void postsMenu(){
    int command;
    do{
        createSpace(2);
        cout << "Choose Option:\n"
            << "\t1. New post\n"
            << "\t2. Edit post\n"
            << "\t0. Return to main menu\n";
        command = lesInt("Choose a numeric option",0,2);
        cout << '\n';

        switch(command){
            case 1: createSpace(2); gMainRebus->newPost(); break;
            case 2: createSpace(2); gMainRebus->editPost(); break; 
            default: break;
            }
    }while(command != 0);
}

//post funksjoner slutt

/**
 * @Denne funkjsonen er ikke aktiv akkurat nå fordi showTeam og showPost ikke er aktive.
 * 
 */
void showResult(){
    int command;
    do{
        createSpace(2);
        cout << "Choose Option:\n"
            << "\t1. Show all results\n"
            << "\t2. Show points for select team\n"
            << "\t3. Show points for select post\n"
            << "\t0. Return to main menu\n";
        command = lesInt("Choose a numeric option",0,3);
        switch(command){
            case 1: createSpace(2); gMainRebus->showAllResults(); break;
            //case 2: createSpace(2); gMainRebus->showTeamResult(); break;
            //case 3: createSpace(2); gMainRebus->showPostResult(); break;
            default: break;
        }
    }while(command!=0);
}

// resultat funksjoner slutt

//registrer poeng funksjoner start
void registerResult(){
    int command;
    do{
        createSpace(2);
        cout << "Choose Option:\n"
            << "\t1. Quick Input\n"
            << "\t2. Detailed Input\n"
            << "\t0. Return to main menu\n";
        command = lesInt("Choose a numeric option",0,2);
        switch(command){
            case 1: createSpace(2); gMainRebus->registerPoints("quick"); break;
            case 2: createSpace(2); gMainRebus->registerPoints("detailed"); break;
            default: break;
        };
    }while(command!=0);
}




//registrer nye poeng slutt


// settings funksjoner start
void showSettings(){
    int command;
    do{
        createSpace(2);
        cout << "Choose Option:\n"
            << "\t1. Save Game\n"
            << "\t2. Load Game\n"
            << "\t3. New Game\n"
            << "\t0. Return to main menu.\n";
        command = lesInt("Choose a numeric option",0,3);
        switch(command){
            case 0: createSpace(100); break;
            case 1: createSpace(100); save(gMainFile); break;
            case 2: createSpace(100); save(gMainFile); load(gMainFile,false,false); break;
            case 3: createSpace(100); save(gMainFile); load(gMainFile,false,true); newRebus(); break;
            default: createSpace(100); break;
        }
    }while(command!=0);
}

//settings funksjoner slutt

/**
 * @brief Reads information from document to different objects.
 * 
 * @param input 
 */
void load(fstream & input, const bool promptNew, const bool skipSelect){
    input.seekg(0,ios::beg);    //begynner å lese fra toppen av scriptet
    int command;
    int i=0, nmbr;
    Rebus * nyRebus;
    while(input.eof()==false){
        nyRebus = new Rebus;
        nyRebus->load(input);
        gAlleRebuser.push_back(nyRebus);
    }
    if(skipSelect==false){
        for(int i = 0;i<100;i++)cout << "\n";
        cout << "Choose Save: \n";
        listRebus();
        if(promptNew){
            cout << "\t0: [New Tournament]\n";
        };
        if(promptNew){nmbr=0;}else{nmbr=1;};
        command = lesInt("Choose a numeric option",nmbr,gAlleRebuser.size());

        if(command==0){
            newRebus();
        }else{
            gMainRebus = gAlleRebuser[command-1];          //copies the chosen rebus into the main 
        }
    }
    createSpace(100);
};

void listRebus(){
    int i=0;
    for(i;i<gAlleRebuser.size();i++){
        cout << "\t"<< i+1 << ": " << gAlleRebuser[i]->returnName() << "\n";
    }

};

/**
 * @brief Initializes a series of functions that write data on teams, checkpoints and scores into a file.
 * 
 * @param output 
 */
void save(fstream & output){
    cout << "Saving... \n";
    output.clear();
    output.seekg(0,ios::beg);    //begynner å skrive fra toppen av scriptet
    for(int i=0;i<gAlleRebuser.size();i++){ //loops through all rebus' in memory
        cout << "...\n";
        gAlleRebuser[i]->save(output);
        delete gAlleRebuser[i];
    }
    gAlleRebuser.clear();
}


void newRebus(){
    gMainRebus=new Rebus;
    gMainRebus->readData();
    gAlleRebuser.push_back(gMainRebus);
    
}


void createSpace(const int newLines){
    for(int i = 0;i<newLines;i++){
        cout << "\n";
    }
}