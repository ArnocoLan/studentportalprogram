#ifndef TODOLIST_H
#define TODOLIST_H

#include "variable.h"
#include "date.h"
/*
    To do list class by Lance A. Implemented Date Class created by Salma K. This is used for the queue and linked list requirement.
    The queue list shows the past assignments which is taken from the user input assignments which is a single linked list with two pointers.
*/

class Todolistnode
{

    public:
        //Constructors
        Todolistnode();
        Todolistnode(std::string n, std::string link);

    private:
	Date assignment_date;
        std::string assignment;
        std::string link_to_assignment;
        Todolistnode* next;
        friend class Todolist;

};

class Todolist
{

    public:
        //Default Constructor
        Todolist();
    
        //Displays Assignments/Things to User
        void display_assignments();

	//Displays Options in Todolist Menu to User
	void options();

	//Writing Homework to Userfile
	void write_homework_to_userfile(std::fstream& userfile);

	//Reading In Function
	void read_homework_from_userfile(std::fstream& userfile);
		
        //User Creates a new Assignment Node
        void add_assignment();
		
		//Helper Function That Sorts through the list to place the correct date
		void add_in_order(Todolistnode*& newassignment);

		//Add in Front
		void add_Front(Todolistnode*& newassignment);

		//Add in Back
		void add_Back(Todolistnode*& newassignment);

        //If any of the dates on the assignments are past the current run time date it calls this
        void add_to_past_assignments(); //Adds to Queue (Helper Function for check)
	
		void add_Back_Queue(Todolistnode*& oldassignment);

	        //Displays Past Assignments to User
	        void display_queue(); 
        

        //Iterates through list and checks if the date is past or not (KEEP TRACK OF LEAP YEARS TOO)
        void check_linked_list_for_past_due_date(); 

		void pop_Queue(); //Removes the front of the queue
		
        //Deletes Both Lists
        void delete_list();
        

    private:
        Todolistnode* hp;
        Todolistnode* tp;
        Todolistnode* pasthp;
        Todolistnode* pasttp;
};


#endif