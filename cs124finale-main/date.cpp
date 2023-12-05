#include "date.h"

/*
	CONSTRUCTOR
*/

Date::Date()
{
	year = "0";
	day = "0";
	month = "0";
}

//Important Date Functions
bool Date::check_if_leap_year(int n)
{
	if((n % 4 == 0 && n % 100 != 0) || (n % 400 == 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
    TODOLIST FUNCTIONS
*/



//Setter

void Date::set_assignment_date()
{

    int useryear;
    int userday;
    int usermonth;

    do
    {
        std::cout << "What month was this assignment assigned?" << std::endl;
        std::cout << "Please input a numer between 1-12" << std::endl;
        std::cin >> usermonth;
        std::cout << std::endl;
    }
    while(usermonth <= 0 || usermonth >= 13);
        
    bool leapyear;
    do
    {
        std::cout << "What year was this assignment assigned?" << std::endl;
        std::cout << "Please input a year past 2022" << std::endl;
        std::cin >> useryear;
        std::cout << std::endl;
    }
    while(useryear <= 2022); 
    
    leapyear = check_if_leap_year(useryear);
    
    bool correct = false;
    
    do
    {
		
		
		
		std::cout << "What day was this assignment assigned?" << std::endl;
		std::cout << std::endl;
		
		if(leapyear == true && usermonth == 2)
		{
			std::cout << "Please input a number between 1-29" << std::endl;
		}
		else if(leapyear == false && usermonth == 2)
		{
			std::cout << "Please input a number between 1-28" << std::endl;		
		}
		else if(usermonth == 4 || usermonth == 6 || usermonth == 9 || usermonth == 11)
		{
			std::cout << "Please input a number between 1-30" << std::endl;
		}
		else
		{
			std::cout << "Please input a numer between 1-31" << std::endl;			
		}
		
        std::cin >> userday;
        std::cout << std::endl;
        
        if(leapyear == true && usermonth == 2)
		{
			if(userday >= 1 && userday <= 29)
			{
				correct = true;
			}
		}
		else if(leapyear == false && usermonth == 2)
		{
			if(userday >= 1 && userday <= 28)
			{
				correct = true;				
			}

		}
		else if(usermonth == 4 || usermonth == 6 || usermonth == 9 || usermonth == 11)
		{
			if(userday >= 1 && userday <= 30)
			{
				correct = true;			
			}

		}
		else 
		{
			if(userday >= 1 && userday <= 31)
			{
				correct = true;
			}
		}
		
    }
    while(correct == false); 


    
    std::cout << "The date you inputted is " << usermonth << "/" << userday << "/" << useryear << std::endl;
    month = std::to_string(usermonth);
    day = std::to_string(userday);
    year = std::to_string(useryear);
    
}

void Date::set_current_date() //Helper Function for setting up comparisons to the current date
{
    std::time_t currentTime = std::time(0);

    // Convert the current time to a tm structure
    std::tm* localTime = std::localtime(&currentTime);
    
	int current_year = localTime->tm_year + 1900;  // Years since 1900
    int current_month = localTime->tm_mon + 1;     // Months are 0-based
    int current_day = localTime->tm_mday;          // Day of the month
    
    year = std::to_string(current_year);
    month = std::to_string(current_month);
    day = std::to_string(current_day);
    
}

void Date::read_in_assignment_date(std::string word)
{
	std::string newmonth;
	std::string newday;
	std::string newyear;
	std::string number;
	int counter = 0;
	for(int i = 0; i < word.size(); i++)
	{
		if(word[i] != '/')
		{
			number = number + word[i];
		}
		else
		{
			if(counter == 0)
			{
				newmonth = number;
				number = "";
				counter++;
			}
			else if(counter == 1)
			{
				newday = number;
				number = "";
				counter++;
			}
		}
	}
	newyear = number;
	year = newyear;
	month = newmonth;
	day = newday;
}


//GETTERS

std::string Date::get_assignment_date_as_string()
{
    std::string result = month + "/" + day + "/" + year;
    return result;
}

std::string Date::get_current_date_as_string()
{
    std::time_t currentTime = std::time(0);

    // Convert the current time to a string
    std::string currentTimeString = std::ctime(&currentTime);

    // Print the current time
    return currentTimeString;

}

//Basic Setters (NOT DONE)
void Date::set_year(int new_year)
{
   year = std::to_string(new_year);
}
void Date::set_day(int new_day)
{
   day = std::to_string(new_day);
}
void Date::set_month(int new_month)
{
   month = std::to_string(new_month);
}


//Basic Get Functions
std::string Date::get_year() const
{
	return year;
}

std::string Date::get_month() const
{
	return month;
}

std::string Date::get_day() const
{
	return day;
}

 // equality operator (==)
 //    bool operator==(const Date& lhs) const {
 //        return (year == lhs.year) && (month == lhs.month) && (day == lhs.day);
 //    }

 // inequality operator (!=)
 //    bool operator!=(const Date& lhs) const {
 //        return !(*this == lhs); // Make use of the == operator
 //    }

 // less than operator (<)
 //    bool operator<(const Date& lhs) const {
 //        if (year != lhs.year) {
 //            return std::stoi(year) < std::stoi(lhs.year);
 //        }
 //        if (month != lhs.month) {
 //            return std::stoi(month) < std::stoi(lhs.month);
 //        }
 //        return std::stoi(day) < std::stoi(lhs.day);
 //    }

 // greater than operator (>)
 //    bool operator>(const Date& lhs) const {
 //        return lhs < *this; // Utilize the < operator
 //    }

 // less than or equal to operator (<=)
 //    bool operator<=(const Date& lhs) const {
 //        return !(*this > lhs); // Make use of the > operator
 //    }

 // greater than or equal to operator (>=)
 //    bool operator>=(const Date& lhs) const {
 //        return !(*this < lhs); // Make use of the < operator
 //    }

//OVERLOADED OPERATORS (NOT DONE EITHER)

//Overloaded operators (PLEASE MAKE ONE FOR <, >, >=, <=, and ==) THANK YOU
//Put the definitions here and then Ill move it to todolist 
//I ALREADY DID ==





