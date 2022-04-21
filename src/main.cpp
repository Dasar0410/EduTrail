/**
 * @file main.cpp
 * @author Raphael Storm Larsen (raphaesl@stud.ntnu.no), Daniel Pietrzykowski Sarjomaa (NTNU)
 * @brief Main file of Edutrail project.
 * @version 2.1.3
 * @date 2022-04-21
 *  
 */
// fjernet include Checkpoint fordi den skal ikke brukes direkte av main og skapte mange errorer
#include "LesData2.h"
#include "Team.h" 
#include "Rebus.h"

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


vector <Rebus*> gAlleRebuser;                           //vector containing every rebus in data structure
Rebus * gMainRebus = new Rebus;                         //the currently active rebus' pointer is copied from gAlleRebuser over to gMainRebus. 

fstream gMainFile("saveFile.dta", ios::in | ios::out);  //Opens the save file

/**
 *  Main Program:
 */
int main(){
    if(gMainFile){                                      //checks if savefile exist
        gMainFile.seekg(0, ios::end);                   //sends file pointer to start of file
        if(gMainFile.tellg()==0){                       //if file is empty
            gMainRebus->readData();                     //User is promted with creating a new rebus
            gAlleRebuser.push_back(gMainRebus);         //new rebus stored in vector
        }else{                                          //If there is already content in the file  
            load(gMainFile,true,false);                 //Loads the file, and promts the user to choose what rebus to run
            createSpace(100);
        };

        int command;                
        do{                                             //loops until user types option '0' to exit
            writeMainMenu();  
            command = lesInt("Choose a numeric option",0,5);    
            cout << '\n';
            switch(command){                            //user choose a menu
                case 0: cout << "Terminating Program...\n"; break;
                case 1: createSpace(100); teamMenu(); break;
                case 2: createSpace(100); postsMenu(); break; 
                case 3: createSpace(100); gMainRebus->showAllResults(); break;
                case 4: createSpace(100); registerResult(); break;
                case 5: createSpace(100); showSettings(); break;
                default: createSpace(100); writeMainMenu();
            }                  
        }while (command != 0);
        save(gMainFile);                                //saves data to file before exiting program
    }else{                                              //if there is no file to read from, an error is displayed, and the program terminates
        cout << "Error: Cannot find file \"saveFile.dta\"\n";
        cout << "Terminating Program...\n";
    }
}   

/**
 * @brief Spaces out, then writes out main menu and a logo.
 * 
 */
void writeMainMenu(){
    createSpace(100);
                                                        //writes out logo
    cout << "           _    _______        _ _\n          | |  |__   __|      (_) |\n   ___  __| |_   _| |_ __ __ _ _| |\n  / _ \\/ _` | | | | | '__/ _` | | |\n |  __/ (_| | |_| | | | | (_| | | |\n  \\___|\\__,_|\\__,_|_|_|  \\__,_|_|_|\n\n";
    cout << " Main Menu: " << gMainRebus->returnName() << "\n"
         << "\t1. Teams menu\n"
         << "\t2. Posts menu\n"
         << "\t3. Show results\n"
         << "\t4. Register points \n"
         << "\t5. Manage Saves\n"
         << "\t0. Exit\n";
}


/**
 * @brief Writes out team menu and listens for user input, then executes chosen function.
 * 
 */
void teamMenu(){
    int command;                                    //variable to store user input
    do{                                             //Loops until the user returns to main menu by inputing 0
        createSpace(2);
        cout << "Choose Option:\n"                  //Displays menu      
            << "\t1. New Team\n"
            << "\t2. Edit Team\n"
            << "\t3. Display Teams\n"
            << "\t0. Return to main menu\n";
            command = lesInt("Choose a numeric option",0,3);

        switch(command){                            //listens for user input
            case 1: createSpace(2); gMainRebus->newTeam(); break;
            case 2: createSpace(2); gMainRebus->editTeam(); break; //Will finish theese later.
            case 3: createSpace(2); gMainRebus->listTeams(true,true); break;
            default: break;
        }
    }while(command!=0);

}


/**
 * @brief Writes out checkpoint menu and listens for user input, then executes chosen function.
 * 
 */
void postsMenu(){
    int command;                                    //variable to store user input
    do{                                             //continues looping until user input 0
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


/**
 * @brief Writes out results menu and listens for user input, then executes chosen function. 
 * This function is not in use, as two of the three options are unfinished. The one working option is instead directly avaliable from the main menu.
 * 
 */
void showResult(){
    int command;                                    //variable to store user input
    do{                                             //continues looping until user input 0
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


/**
 * @brief Writes out point registration menu and listens for user input, then executes chosen function.
 * 
 */
void registerResult(){
    int command;                                    //variable to store user input
    if(gMainRebus->readyToRead()){                  //chekcs if there is at least 1 team and 1 checkpoint in active rebus. If not then this menu is not avaliable.
        do{                                         //loops until user inputs 0
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
    };
    
}




/**
 * @brief Writes out settings menu and listens for user input, then executes chosen function.
 * 
 */
void showSettings(){
    int command;                                    //variable to store user input
    do{                                             //loops until user input 0
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
            case 2: createSpace(100); save(gMainFile); load(gMainFile,false,false); break;              //program must save before loading to avoid a number of file related bugs.
            case 3: createSpace(100); save(gMainFile); load(gMainFile,false,true); newRebus(); break;   //again, to avoid a lot of buggy behavior i found it best to "refresh" the file before changing anything major in the datastructure.
            default: createSpace(100); break;
        }
    }while(command!=0);
}



/**
 * @brief Loads all information from the saveFile into the program. Promts user with option to choose active rebus or asks to create a new rebus.
 * 
 * @param input File stream to load from
 * @param promptNew If set to true, function will add a [new rebus] option at the rebus selection menu.
 * @param skipSelect If set to true, the function will skip teh rebus selection menu entierly, and instead user the old gMainRebus.
 */
void load(fstream & input, const bool promptNew, const bool skipSelect){
    input.seekg(0,ios::beg);                        //sets file pointer to beginning of file
    int command;                                    //variable to store user input
    int i=0,                                        //loop variable 
        nmbr;                                       //assisting variable for deciding minimum allowed user input
    Rebus * nyRebus;                                //Pointer variable to store newly created rebus

    while(input.eof()==false){                      //Loops as long as there is more content in file
        nyRebus = new Rebus;                        //creates a new rebus
        nyRebus->load(input);                       //reads information from file into newly created rebus
        gAlleRebuser.push_back(nyRebus);            //adds new rebus to the back of gAlleRebuser
    }

    if(skipSelect==false){                          //If option is enabled, this section is ignored
        createSpace(100);                               
        cout << "Choose Save: \n";                  //writes out menu to choose active rebus
        listRebus();
        if(promptNew){                              //if parameter is enabled, the new tournament menu option is written
            cout << "\t0: [New Tournament]\n";
        };
        if(promptNew){nmbr=0;}else{nmbr=1;};        //sets the minimum input to 0 if the new rebus parameter is true.
        command = lesInt("Choose a numeric option",nmbr,gAlleRebuser.size());

        if(command==0){                             //if user choose to create a new rebus
            newRebus();
        }else{                                      //if user choose to load an existing rebus
            gMainRebus = gAlleRebuser[command-1];   //copies the chosen rebus' pointer onto the main variable
        }
    }
    createSpace(100);
};

/**
 * @brief Writes out a list of all rebus' in the data structure.
 * 
 */
void listRebus(){
    int i=0;
    for(i;i<gAlleRebuser.size();i++){               //iterates through all rebus' and writes them out.
        cout << "\t"<< i+1 << ": " << gAlleRebuser[i]->returnName() << "\n";
    }

};

/**
 * @brief Saves all information is data structure to a file.
 * 
 * @param output The file stream that data is saved to.
 */
void save(fstream & output){
    cout << "Saving... \n";
    output.clear();                                 //clears any potentially stored inputs/outputs
    output.seekg(0,ios::beg);                       //moves file pointer to start of file
    for(int i=0;i<gAlleRebuser.size();i++){         //iterates through all rebus' in data structure
        cout << "...\n";
        gAlleRebuser[i]->save(output);              //Saves rebus to file
        delete gAlleRebuser[i];                     //Deletes rebus from data structure
    }
    gAlleRebuser.clear();                           //Empties vector
}

/**
 * @brief Creates an entierly new rebus in gMainRebus
 * 
 */
void newRebus(){
    gMainRebus=new Rebus;                           //Creates new rebus
    gMainRebus->readData();                         //Reads data into newly created rebus
    gAlleRebuser.push_back(gMainRebus);             //Adds new rebus to the back of the vector
    
}

/**
 * @brief Prints out newlines equal to the parameter.
 * 
 * @param newLines How many newlines of space the function will print.
 */
void createSpace(const int newLines){
    for(int i = 0;i<newLines;i++){
        cout << "\n";
    }
}