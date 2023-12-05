/*
STUDENT PORTAL PROGRAM by Lance Arnoco, Elvin Ong, and Salma Khaliqi
This program will allow students to condense their needs into one program. This will implement ideas from canvas, GE transfer requirements tracker, and offer 
general support for student needs.
Task Delegation:
Lance - | Menu Class | Binary Question Tree inside of Transfer Menu | Reading/Writing Binary Question Tree | Allocation/Deallocation management |
Salma - | Creating new File for College | College Class | Reading/Writing College User List | Merge Sorting Algorithim | Menu Class |
Elvin - | Menu Class | GPA Calculator of Transfer Menu | Hashtable Course Requirement of Transfer Menu | Allocation/Deallocation management | Reading/Writing Transfer Menu |
*/
#include "menu.h"



Menu mainmenu;
Date current_day_today;

int main()
{
	std::cout << std::endl;
	std::cout << "Current Date: " << current_day_today.get_current_date_as_string() << std::endl;
	bool startprogram = mainmenu.greet_user();
	
	if(startprogram == true)
	{
		mainmenu.explain_menu();
	}
	
	while(startprogram == true)
	{
		startprogram = mainmenu.menu_options();
	}

	mainmenu.end_program();
	
}

