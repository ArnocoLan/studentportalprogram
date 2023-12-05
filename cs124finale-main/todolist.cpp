#include "todolist.h"

//Overloaded Operators

bool operator<(Date a, Date b)
{
	if(std::stoi(a.get_year()) < std::stoi(b.get_year()))
	{
		return true;
	}
	else if(std::stoi(a.get_year()) == std::stoi(b.get_year()))
	{
		if(std::stoi(a.get_month()) < std::stoi(b.get_month()))
		{
			return true;
		}
		else if(std::stoi(a.get_month()) == std::stoi(b.get_month()))
		{
			if(std::stoi(a.get_day()) < std::stoi(b.get_day()))
			{
				return true;
			}
		}
	}
	
	return false;
}

bool operator==(Date a, Date b)
{
	if(std::stoi(a.get_year()) == std::stoi(b.get_year()))
	{
		if(std::stoi(a.get_month()) == std::stoi(b.get_month()))
		{
			if(std::stoi(a.get_day()) == std::stoi(b.get_day()))
			{
				return true;
			}
		}
	}
	return false;
}

bool operator<=(Date a, Date b)
{
	if(std::stoi(a.get_year()) < std::stoi(b.get_year()))
	{
		return true;
	}
	else if(std::stoi(a.get_year()) == std::stoi(b.get_year()))
	{
		if(std::stoi(a.get_month()) < std::stoi(b.get_month()))
		{
			return true;
		}
		else if(std::stoi(a.get_month()) == std::stoi(b.get_month()))
		{
			if(std::stoi(a.get_day()) < std::stoi(b.get_day()))
			{
				return true;
			}
		}
	}
	if(a == b)
	{
		return true;
	}
	
	return false;
}





Date operator-(Date &a, int B) //Date - 7 days ago for example Calculates that
{
	int originalday = std::stoi(a.get_day());
	int originalmonth = std::stoi(a.get_month());
	int originalyear = std::stoi(a.get_year());

	int newday = originalday;
	int newmonth = originalmonth;
	int newyear = originalyear;

	bool isleapyear = a.check_if_leap_year(originalyear); //Checks to see if the inputted year is a leap year
	if(originalday - B <= 0) //Checks to see if the days go into the negatives or 0
	{
		newmonth--; //Goes back one month since days are negative

		if(newmonth == 2) //Checks if the month is Feb. 
		{
			if(isleapyear == true) //If leap year then days end on 29
			{
				newday = (originalday - B) + 28;
			}
			else
			{
				newday = (originalday - B) + 27; //If not leap year ends on 28
			}
		}
		else if(newmonth == 0) //If the previous month was jan. it goes to december and minus one year
		{
			newyear--;
			newmonth = 12;
			newday = (originalday - B) + 30;
		}
		else if(newmonth == 4 || newmonth == 6 || newmonth == 9 || newmonth == 11) //On April, June, September, and November are 30 days so + 29 for 30
		{
			newday = (originalday - B) + 29;
		}
		else
		{
			newday = (originalday - B) + 30; //Other months are 31 so + 30
		}
	}
	else
	{
		newday = originalday - B; //Does a normal newday - 7 if not less than or equal to 0
	}
	
	a.set_day(newday);
	a.set_month(newmonth);
	a.set_year(newyear);
	return a;
	
}



/*
    TO DO LIST NODE DEFINITIONS
*/
Todolistnode::Todolistnode()
{
    next = nullptr;
    assignment = "";
    link_to_assignment = "N/A";
}

Todolistnode::Todolistnode(std::string n, std::string link)
{
    next = nullptr;
    assignment_date.set_assignment_date();
    link_to_assignment = link;
    assignment = n;
}


/*
    TO DO LIST DEFINITIONS
*/

Todolist::Todolist()
{
    hp = nullptr;
    tp = nullptr;
    pasthp = nullptr;
    pasttp = nullptr;
}

//MENU of TODOLIST
void Todolist::options()
{
	//Moves all past assignments to the past assignment due date and pops queue and pops (CHECK LEAP YEARS AND MONTHS AND STUFF)
	//IMPORTANT DATES: WHEN THE PAST SEVEN DAYS ARE NOT IN THE SAME MONTH, WHEN THE DAY BECOMES A LEAP YEAR, WHEN THE YEAR CHANGES AND WHEN THE YEAR DOESNT CHANGE, KEEP TRACK OF YEAR AND STUFF
	

	
	
	Date current_date;
	current_date.set_current_date();
	Todolistnode* traverse = hp;
	
	while(traverse != nullptr && traverse->assignment_date == current_date) //Displays assignments that are due today on the system
	{
		current_date.set_current_date(); //Live updates the current date so you can stress in real time
		std::cout << "IMPORTANT ASSIGNMENTS!" << std::endl;
		std::cout << traverse->assignment << " - DUE TODAY" << std::endl; 
		traverse = traverse->next;
	}
	
	std::string answer;
	bool redo = true;
	
	while(redo == true)
	{
		do
		{

			std::cout << std::endl;
			std::cout << "To do List" << std::endl;
			std::cout << "1) Display Assignments" << std::endl;
			std::cout << "2) Add New Assignment" << std::endl;
			std::cout << "3) Look at Past Assignments" << std::endl;
			std::cout << "4) Exit Assignment List" << std::endl;	
			std::cin >> answer;
			std::cout << std::endl;
		}
		while(answer != "1" && answer != "2" && answer != "3" && answer != "4");
		
		
		
		if(answer == "1")
		{
			display_assignments();
		}
		
		else if(answer == "2")
		{
			add_assignment();
		}
		
		else if(answer == "3")
		{
			display_queue();
		}
		
		else
		{
			redo = false;
		}
		
	}
	
}

void Todolist::display_assignments()
{
    if(hp == nullptr) //If List is empty
    {
        std::cout << "There are no assignments!" << std::endl;
        std::cout << "Take it easy today!" << std::endl;
        return;
    }
    
    Todolistnode* traverse = hp;
    std::cout << "Today's Date: " << hp->assignment_date.get_current_date_as_string() << std::endl; 
    while(traverse != nullptr)
    {
		if(traverse->link_to_assignment == "N/A")
		{
			std::cout << traverse->assignment << "\t" <<"Due Date: " << traverse->assignment_date.get_assignment_date_as_string() << std::endl; 
		}
		else
		{
			std::cout << traverse->assignment << "\t" << "Due Date: " << traverse->assignment_date.get_assignment_date_as_string() << "\t" << "Link: " << traverse->link_to_assignment << std::endl;
		}
        traverse = traverse->next;
    }
}

void Todolist::display_queue()
{
	add_to_past_assignments(); //Checks the current list to see if any updates are needed. (i.e needs to remove current past queue if things are past 7 days or on the current linked list past the due date)
	std::cout << "PAST ASSIGNMENTS" << std::endl;
	std::cout << std::endl;
	
	if(pasthp == nullptr)
	{
		std::cout << "Starting Fresh with a New Beginning!" << std::endl;
		std::cout << "No Recent Assignments in the past week" << std::endl;
		return;
	}
	
	Todolistnode* traverse = pasthp;
	while(traverse != nullptr)
	{
		std::cout << traverse->assignment << " Due Date: " << traverse->assignment_date.get_assignment_date_as_string() << std::endl;
		traverse = traverse->next;
	}
}

void Todolist::add_assignment() //More than 60 Lines of Code (Sorry)
{
	
	bool redo = true;
	
	while(redo == true)
	{
		Todolistnode* new_assignment = new Todolistnode;
		std::string name;
		std::string answer;
		
		do
		{
			std::cout << "What is the name of the assignment?" << std::endl;
			std::cin.ignore();
			std::getline(std::cin, name);
			std::cout << std::endl;
			std::cout << "Is " << name << " the correct name of your assignment?" << std::endl;
			std::cout << "Y/N" << std::endl;
			std::cin >> answer;
			std::cout << std::endl;
		}
		while(answer != "Y" && answer != "y");
		new_assignment->assignment = name;
		
		std::cout << "What is the due date of the assignment?" << std::endl;
		
		do
		{
			new_assignment->assignment_date.set_assignment_date();
			std::cout << std::endl;
			
			std::cout << "Is this the correct date?" << std::endl;
			std::cout << "Y/N" << std::endl;
			std::cin >> answer;
		}
		while(answer != "Y" && answer != "y");
		
		std::string newlink;
		do
		{
			std::cout << "Would you like to leave a link to your assignment?" << std::endl;
			std::cout << "Y/N" << std::endl;
			std::cin >> answer;
			
			if(answer == "Y" || answer == "y")
			{
				std::cout << "What is the link of the assignment?" << std::endl;
				std::cin >> newlink;
				std::cout << "Is " << newlink << " the correct link?" << std::endl;
				std::cout << "Y/N" << std::endl;
				std::cin >> answer;
			}
			else if(answer == "N" || answer == "n")
			{
				answer = "1";
			}
			
		}
		while(answer != "Y" && answer != "y" && answer != "1");
		
		if(answer == "Y" || answer == "y")
		{
			new_assignment->link_to_assignment = newlink;
		}
		
		else
		{
			new_assignment->link_to_assignment = "No Link";
		}
		Date today;
		today.set_current_date();
		
		if(today <= new_assignment->assignment_date)
		{
			add_in_order(new_assignment);
		}
		else
		{
			delete new_assignment;
		}		

		std::cout << "Would you like to add another assignment?" << std::endl;
		std::cout << "Y/N" << std::endl;
		std::cin >> answer;
		if(answer == "N" || answer == "n")
		{
			redo = false;
		}
	
	}
	
	
}

void Todolist::add_Front(Todolistnode*& newassignment) 
{
    if (hp == nullptr) // checks if first node is empty, e.g the list is empty
    {
        hp = newassignment;
        tp = newassignment;
    } 
    else // if the list is not empty
    {
        newassignment->next = hp;
        hp = newassignment;
    }
}

void Todolist::add_Back(Todolistnode*& newassignment)
{
    if (hp == nullptr) // checks if first node is empty, e.g the list is empty
    {
        hp = newassignment;
        tp = newassignment;
    }
    
    else // if the list is not empty
    {
        tp->next = newassignment;
        tp = newassignment;
    }
}

void Todolist::add_in_order(Todolistnode*& newassignment) //Arranges by Date
{

	Todolistnode* traverse = hp;
	Todolistnode* previous = nullptr;
	if(hp == nullptr || newassignment->assignment_date < hp->assignment_date) //If the date is before the first date or empty
	{
		add_Front(newassignment);
	}
	else 
	{
		while(traverse != nullptr && traverse->assignment_date < newassignment->assignment_date)
		{
			previous = traverse;
			traverse = traverse->next;
		}

		if(traverse == nullptr)
		{
			add_Back(newassignment);
		}
		else
		{
			previous->next = newassignment;
			newassignment->next = traverse;
			
		}
	}
}

void Todolist::add_to_past_assignments()  //Checks Linked List for Past Due
{
	Date currentday;
	currentday.set_current_date();
	
	if(hp == nullptr)
	{
		return;
	}
	else
	{
		
		while(hp != nullptr && hp->assignment_date < currentday)
		{
			Todolistnode* nextone = hp;
			Todolistnode* hpafter = hp->next;
			nextone->next = nullptr; //Erases All Pointers Associated with the Assignment past due
			add_Back_Queue(nextone); //Adds to Queue
			hp = hpafter; //Moves hp forward one
			
			
		}
	}

	
}

void Todolist::add_Back_Queue(Todolistnode*& oldassignment) //Queue is in order already since the original linked list is in order
{
    if (pasthp == nullptr) // checks if first node is empty, e.g the list is empty
    {
        pasthp = oldassignment;
        pasttp = oldassignment;
    } 
    else // if the list is not empty
    {
        pasttp->next = oldassignment;
        pasttp = oldassignment;
    }	
}

void Todolist::check_linked_list_for_past_due_date()
{
	Date aweekago;
	aweekago.set_current_date();
	aweekago = aweekago - 7;
	if(pasthp == nullptr)
	{
		return;
	}
	else
	{
		while(pasthp != nullptr && pasthp->assignment_date <= aweekago)
		{
			std::cout << "Removing " << pasthp->assignment << " from Past Assignments!" << std::endl;
			pop_Queue();
		}
	}
}

void Todolist::pop_Queue()
{
	if(pasthp == nullptr)
	{
		std::cout << "Past Assignment Already Empty" << std::endl;
		return;
	}
	else
	{
		Todolistnode* removed = pasthp;
		pasthp = pasthp->next;
		delete removed;
	}
}

void Todolist::write_homework_to_userfile(std::fstream& userfile) 
{
	userfile << "User Agenda:" << std::endl;
	userfile << "HomeworkName" << "\t" << "DueDate" << "\t" << "AssignmentLink" << std::endl;
	userfile << std::endl;
	Todolistnode* traverse = hp;
	while(traverse != nullptr) //Separates all Data Elements by a Tab to make reading easier for txt file
	{
		if(traverse->link_to_assignment != "")
		{
			userfile << traverse->assignment << "\t" <<traverse->assignment_date.get_assignment_date_as_string() << "\t" << traverse->link_to_assignment << std::endl;
		}
		else
		{
			userfile << traverse->assignment << "\t" << traverse->assignment_date.get_assignment_date_as_string() << "\t" << "N/A" << std::endl;	
		}
		traverse = traverse->next;
	}

}

void Todolist::read_homework_from_userfile(std::fstream& userfile)
{
	std::string header = "User Agenda:";
	std::string check;
	
	while(std::getline(userfile, check, '\n')) //Reads Line until it finds the Main Header
	{
		//Basically this finds the first character that is not a tab character endline or white space then deletes the rest afterward
		check.erase(0, check.find_first_not_of(" \t\r\n")); //Deletes the empty space past the get line
        check.erase(check.find_last_not_of(" \t\r\n") + 1); //Finds the end of the empty space of get line 
        
		if(check == header)
		{
			break;
		}
		std::cout << "Removed - " << check << std::endl;
	}
	
	std::getline(userfile, check, '\n'); //Skips Sub-header
	std::cout << std::endl;
	std::cout << check << std::endl;
	std::cout << std::endl;
	
	while(std::getline(userfile, check, '\n')) //Reads line
	{
		
		Todolistnode* new_assignment = new Todolistnode();
		std::stringstream str(check);
		check.clear();
		std::string word;
		int data = 0;
		while(std::getline(str, word, '\t')) //Gets individual Word
		{
			if(data == 0)
			{
				new_assignment->assignment = word;
			}
			else if(data == 1)
			{
				new_assignment->assignment_date.read_in_assignment_date(word);
			}
			else if(data == 2)
			{
				if(word == "N/A")
				{
					break;
				}
				else
				{
					new_assignment->link_to_assignment = word;
				}
			}
			data++;
		}
		Date today;
		today.set_current_date();
		
		if(today <= new_assignment->assignment_date) //If the due date is still valid input
		{
			std::cout << "Adding: - " << new_assignment->assignment << std::endl;
			add_in_order(new_assignment);
		}
		else //If the due date has passed dont add
		{
			std::cout << "Due Date Passed! Removed - " << new_assignment->assignment << std::endl;
			delete new_assignment;
		}
	}
}

void Todolist::delete_list() 
{
	std::cout << "Deleting HW List" << std::endl;
	Todolistnode* traverse = hp;
	while(pasthp != nullptr) //Pops all Queue Values
	{
		pop_Queue();
	}
	
	
	while(traverse != nullptr)
	{
		Todolistnode* removed = traverse;
		removed = traverse;
		traverse = traverse->next;
		delete removed;
	}
	
	hp = nullptr;
	tp = nullptr;
	pasthp = nullptr;
	pasttp = nullptr;
	std::cout << "Deleted" << std::endl;

}