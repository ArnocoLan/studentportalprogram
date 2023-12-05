#include "menu.h"
#include "college.h"

/*
    GREET USER FUNCTION
*/

Menu::Menu()
{
	//userfile.open("userfile.txt", std::ios::in | std::ios::out);
}

void Menu::read_in_previous_file() //For returning
{
	std::cout << "What is the name of the file?" << std::endl;
	std::string filename;
	bool valid = false;
	while(valid == false)
	{
		std::cin >> filename;
		std::cout << std::endl;
		if(filename.find(".txt") == std::string::npos)
		{
			filename = filename + ".txt";
		}
		std::cout << "Is this your file?" << std::endl;
		std::cout << "File: " << filename << std::endl;
		std::string answer;
		do
		{
			std::cout << "Y/N?" << std::endl;
			std::cin >> answer;
			std::cout << std::endl;
		}
		while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");
		if(answer == "Y" || answer == "y")
		{
			userfile.open(filename);
			valid = true;
		}
	}
	
}

bool Menu::greet_user()
{
    std::cout << "Welcome to the Aphantasia Commmunity College Transfer to UC/CSU Assistant!" << std::endl;
    std::cout << "Do you have a file with us?" << std::endl;
    std::string answer;
    do
    {
        std::cout << "Y/N" << std::endl;
        std::cin >> answer;
        std::cout << std::endl;
    }
    while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");

    if(answer == "N" || answer == "n")
    {
        std::cout << "Welcome to the program!" << std::endl;
        std::cout << "This program will assist you in picking the right school you want to transfer to!" << std::endl;
        std::cout << "As well as help organize your work and keep you on top of important deadlines!" << std::endl;
        std::cout << "Would you like to make a file with us?" << std::endl;
        do
        {
            std::cout << "Y/N" << std::endl;
            std::cin >> answer;
            std::cout << std::endl;
        }
        while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");

        if(answer == "Y" || answer == "y")
        {
            return true;
        }
        else
        {
            std::cout << "Thank you for checking out our program!" << std::endl;
            return false;
        }
        
    }
        
    else
    {
        std::cout << "Welcome Back!" << std::endl;
        read_in_previous_file(); //Asks User for File Name
        read_all(); //Reads in All information
        return true;
    }

    
}

/*
    DISPLAY OPTIONS FUNCTION
*/

void Menu::explain_menu()
{
    std::cout << "Option 1) Course Tracker and College Questionnaire" << std::endl;
    std::cout << "Course Tracker Offers a IGETC tracker allowing you to manage what classes you have completed regarding the 7 Areas for Community College." << std::endl;
    std::cout << "You can input courses regarding each area and the program will provide which classes you need to complete certain areas." << std::endl;
    std::cout << "The college questionnaire is a generic outline of what CSUs/UCs offer and helps you determine what college is right for you!" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Option 2) College User List" << std::endl;
    std::cout << "College User List offers information on a majority of CSUs/UCs and allows you to identify your favorite colleges." << std::endl;
    std::cout << "You can make a personalized list of colleges that can be changed or added to at any time ranking your top colleges!" << std::endl;
    std::cout << std::endl;
    
    std::cout << "Option 3) To do List" << std::endl;
    std::cout << "A digitalized agenda where you can add assignments and keeps track when the assignment is due." << std::endl;
    std::cout << std::endl;
	
	std::cout << "Option 4) Exit & Save Files" << std::endl;
	std::cout << "Exits program and allows you to save your information if you choose to do so" << std::endl;
	std::cout << std::endl;
}
bool Menu::menu_options()
{
    std::cout << "Main Menu" << std::endl;
    std::cout << std::endl;
    std::string answer;

    
    
    do
    {
        std::cout << "1) Course Tracker and College Question" << std::endl; //Not trademark 
        std::cout << "2) College User List" << std::endl;
        std::cout << "3) To do List" << std::endl;
        std::cout << "4) Exit & Save Files" << std::endl;
        std::cin >> answer; 
    }
    while(answer != "1" && answer != "2" && answer != "3" && answer != "4");

    if(answer == "1")
    {
        opentransfermenu(usercollegelist);
    }

    else if(answer == "2")
    {
		usercollegelist.collegemenu(userfile, c_array, user_array);
    }

    else if(answer == "3")
    {
        opentodolist();
    }

    else
    {
        return false;
    }
    
    return true;
    
}


/*
	WRITE FUNCTIONS
*/
void Menu::write_all()
{

	std::cout << "Would you like to save your information?" << std::endl;
	std::string filename;
	std::string answer;
	do
	{
		std::cout << "Y/N?" << std::endl;
		std::cin >> answer;
	}
	while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");

	if(answer == "Y" || answer == "y")
	{
		std::cout << "What would you like to name your file?" << std::endl;
		
		do
		{
			std::cin >> filename;
			std::cout << std::endl;
			if(filename.find(".txt") == std::string::npos)
			{
				filename = filename + ".txt";
			}
			std::cout << "Are you sure you want to name your file " << filename << "?" << std::endl;
			do
			{
				std::cout << "Y/N?" << std::endl;
				std::cin >> answer;
				std::cout << std::endl;
			}
			while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");
		
		}
		while(answer != "Y" && answer != "y");
		
		if(answer == "Y" || answer == "y")
		{
			std::cout << "Open" << std::endl;
			std::cout << filename << std::endl;
			userfile.open(filename, std::ios::out | std::ios::trunc);
			usercollegelist.pre_process(c_array);
			usercollegelist.user_file(userfile, c_array, user_array);
			usercollegelist.write_userlist_to_file(userfile, user_array);
			transfer.write_transfer_to_userfile(userfile);
			userhwlist.write_homework_to_userfile(userfile);
			userfile.close();
		}
		

	}
	
}


/*
	READ FUNCTION CALLS
*/

void Menu::read_all()
{
	std::cout << "Reading in All Information!" << std::endl;
	std::cout << std::endl;
	
	/*
	std::cout << "Reading in User College List" << std::endl;
	
	usercollegelist.read_userfile(userfile, user_array);
	std::cout << std::endl;
	*/
	
	std::cout << "Reading in General Course Completion" << std::endl;
	transfer.read_from_userfile(userfile);
	std::cout << std::endl;
	
	std::cout << "Reading in Homework Assignments" << std::endl;
	userhwlist.read_homework_from_userfile(userfile);
	std::cout << std::endl;
	
	userfile.close();
	
}

/*
    CALLING OBJECT MENU FUNCTIONS
*/

void Menu::opentransfermenu(College collegedata)
{
	std::cout << std::endl;
    std::cout << "Opening Transfer Menu" << std::endl;
    std::cout << std::endl;
    
    transfer.menu(collegedata, userfile);
}

void Menu::opentodolist()
{
	std::cout << std::endl;
	std::cout << "Opening Assignments" << std::endl;
	std::cout << std::endl;
	
	userhwlist.options();
	
}

void Menu::opencollegelistmenu()
{
	usercollegelist.display_sort_criteria();
}

/*
	END PROGRAM (NOT FINISHED)
*/ 
void Menu::end_program() 
{
	write_all();
	userhwlist.delete_list();
	transfer.delete_tree();
	usercollegelist.delete_college(c_array, user_array);
	
}
