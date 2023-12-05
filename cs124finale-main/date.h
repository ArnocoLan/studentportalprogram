#ifndef DATE_H
#define DATE_H

#include "variable.h"

/*
    Date Class worked on by Salma K. and Lance A. Used to implement the todolist and get the date of the current runtime.
    Reference Cplusplus.com https://cplusplus.com/reference/chrono/system_clock/to_time_t/
*/

//If you work on this just std::stoi() when comparing
//If you see this I did most of it cause I needed it for my Todolist - Lance
//All you have to do is basic setters

class Date
{

    public:

	//Constructors
	Date();
		
        //Setters for Assignment Date and Current Date
        void set_assignment_date(); //Sets Assignment Date with User Input
        void set_current_date(); //Helper Function to set current Date Object as the current date
        void read_in_assignment_date(std::string word);

        //Getters for Displaying current date and Assignment Date
        std::string get_current_date_as_string(); //Used to print out the date like MM/DD/YEAR
        std::string get_assignment_date_as_string(); //Used to Print out the Date like MM/DD/YEAR
        
        //Important Date Checker
        bool check_if_leap_year(int n);
        
        //Setters (Do Basic Setters)
		void set_year(int new_year);
		void set_day(int new_day);
		void set_month(int new_month);
        
        //Getters
		std::string get_year() const;
		std::string get_day() const;
		std::string get_month() const;




    private:
        std::string year;
        std::string day;
        std::string month;
};



#endif
