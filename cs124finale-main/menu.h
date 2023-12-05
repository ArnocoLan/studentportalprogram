#ifndef MENU_H
#define MENU_H
/*
  Menu Class that will act as a main hub for the program
  Will contain Tree Class File, College Class file, To Do List Class File, Transfer menu Class file
  Worked on by Lance, Elvin, and Salma
*/


#include "transfermenu.h" //Includes College.h
#include "todolist.h"
#include "college.h"

class Menu
{
  public:
	
	Menu();
	
	
	
    //Greet and End Program Functions
    bool greet_user();
    void end_program();


    //Helper Functions for Reading in
    void create_new_file(); //For Newbies
    void read_in_previous_file(); //For returning 
    
    //Display Options
    bool menu_options(); //Function that displays the Options for the program
	void explain_menu();
	
    //Write to File Functions
	void write_all(); //First Function Call that calls the other stuff
    void write_transfermenu_to_userfile(); //This will just be a call function and the actual transfermenu class will include the actual writing to file
    void write_usercollegelist_to_userfile(); //This will just be a call function same as above
    void write_todolist_to_userfile(); //This will just be a call function

    //Read in File Functions
	void read_all(); //First Function Call that calls the other stuff
	
    //Call Transfer Menu Function
    void opentransfermenu(College usercollegelist); //I need to pass this 
    
    //Call College Menu
    void opencollegelistmenu();

    //Call todolist function
    void opentodolist();

  private:
    std::fstream userfile;
    Todolist userhwlist;
    Transfermenu transfer;
    College usercollegelist;
    College* user_array = new College[5];
    College* c_array = new College[SIZE];
    
    
};

#endif