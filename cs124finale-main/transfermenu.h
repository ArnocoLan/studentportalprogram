#ifndef TRANSFERMENU_H
#define TRANSFERMENU_H

/*
    Transfer Menu Class will be used to keep track of GE course requirements as well as keep track of user GPA.
    Elvin Ong and Lance Arnoco will work on this class. 
    Elvin worked on GPA and GE Course Requirements (Hashtable Structure)
    Lance will work on Tree Questions and Help GE Course Requirements USER INTERFACE
*/
#include "tree.h"
#include "hashtable.h"
#include "college.h"

//READ ME
//If we keep it as private data members we do not need to have the object in the parameters cause it would already be "PASSED"

class Transfermenu
{

    public:
        Transfermenu();
        
        //USER INTERFACE function
        void menu(College helper, std::fstream& userfile); //Displays options of transfer menu

        //Actual Functions that the user will ask the questions
        void ask_user_questions(College helper);

        //Setters and Getters
        void calculate_gpa(Hashtable& courselist);
        double get_GPA() const;

        //Display Functions
        void display_GPA(); //Display GPA //Hashtable courselist
        void display_GEcourselist(); //Display all the areas and stuff //Hashtable courselist

        //Edit Functions
        void add_course(); //Hashtable& courselist

        //Write Functions
        void write_transfer_to_userfile(std::fstream& userfile); //Hashtable courselist

        //Read Functions
        void read_from_userfile(std::fstream& userfile); //Hashtable& courselist
        void read_userfile_to_GEcourselist(); //Hashtable& courselist

        //Delete Call Functions
        void delete_tree(); //Tree& questions
        void delete_hashtable(); //Hashtable& courselist
        
    private:
        double GPA;
        Tree questions;
        Hashtable courselist;
        bool userfileread;
        

};

#endif
