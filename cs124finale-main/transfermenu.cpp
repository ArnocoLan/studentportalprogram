#include "transfermenu.h"

/*
	CONSTRUCTOR
*/ 

Transfermenu::Transfermenu()
{
	GPA = 0.0;
}

/*
    TRANSFER MENU FUNCTION
*/
void Transfermenu::menu(College helper, std::fstream& userfile)
{
    
    for(int i = 0; i < 20; i++)
    {
        std::cout << "-";
    }
    std::cout << std::endl;

    std::cout << "Welcome to the Transfer Menu!" << std::endl;
    std::cout << std::endl;
    std::string answer;
    bool redo = true;
   
    while(redo == true)
    {
        do
        {
            std::cout << "1) General Education Course List" << std::endl;
            std::cout << "2) College Recommendation Questionnaire" << std::endl;
            std::cout << "3) Calculate GPA" << std::endl;
            std::cout << "4) Add Courses" << std::endl;
            std::cout << "5) Display Courses" << std::endl;
            std::cout << "6) Exit Transfer Menu" << std::endl;
            std::cin >> answer;
            std::cout << std::endl;
        }
        while(answer != "1" && answer != "2" && answer != "3" && answer != "4" && answer != "5" && answer != "6");
    
        if(answer == "1")
        {
            courselist.check_IGETC();
        }
            
        else if(answer == "2")
        {
            ask_user_questions(helper);
        }
    
        else if(answer == "3")
        {
            calculate_gpa(courselist);
            display_GPA();
        }
    
        else if(answer == "4")
        {
            add_course();
        }
        else if (answer == "5")
        {
            display_GEcourselist();
        }
        else if (answer == "6")
        {
            redo = false;
        }
    }

}

/*
    QUESTIONS FUNCTIONS
*/

void Transfermenu::ask_user_questions(College helper)
{
    questions.print_current_node(helper);
}

/*
    DELETE FUNCTIONS
*/
void Transfermenu::delete_tree()
{
    questions.delete_tree();
}

/*
GPA FUNCTIONS
*/

void Transfermenu::calculate_gpa(Hashtable& courselist)
{
    GPA = courselist.calculate_gpa();
}

double Transfermenu::get_GPA() const
{
    return GPA;
}

void Transfermenu::display_GEcourselist()
{
    courselist.display();
}

void Transfermenu::add_course()
{
    std::string answer;
    do
    {
        std::cout << "Would you like to add a course? You would need to provide the course name, grade, units, and IGETC area. Y/N?" << std::endl;
        std::cin >> answer;
        if (answer == "Y" || answer == "y")
        {
            std::string course;
            double grade;
            int units, area;
            bool cont = false;
            std::string check;
            do
            {
                std::cout << "Please enter the course name:" << std::endl;
                std::cin >> course;
                std::cout << "Please enter the course grade (A = 4.0, A- = 3.7, B+ = 3.3, B = 3.0, etc.):" << std::endl;
                std::cin >> grade;
                std::cout << "Please enter the course units:" << std::endl;
                std::cin >> units;
                std::cout << "Please enter the course area requirement it counts toward for IGETC (1-7):" << std::endl;
                std::cin >> area;
                std::cout << "Is this information correct? Y/N" << std::endl;
                std::cout << "| Course: " << course << " | Grade: " << grade << " | Units: " << units << " | Area: " << area << std::endl;
                std::cin >> check;
                std::cout << std::endl;
                if (check == "Y" || check == "y") 
                {
                    courselist.insert(course, grade, units, area);
                    cont = true;
                }
            } 
            while (check != "Y" && check != "y" && check != "N" && check != "n" && cont != true);
        }
    } 
    while (answer != "Y" && answer != "y" && answer != "N" && answer != "n");
}

void Transfermenu::display_GPA()
{
	std::cout << std::endl;
    std::cout << "Your GPA is " << get_GPA() << std::endl;
    std::cout << std::endl;
}

void Transfermenu::write_transfer_to_userfile(std::fstream& userfile)
{
    courselist.write_GEcourselist_to_userfile(userfile);
}

void Transfermenu::read_from_userfile(std::fstream& userfile)
{
    if (!userfile.is_open())
    {
        std::cerr << "Error: File is not open." << std::endl;
        return;
    }

    std::string line;

    // Find the start of the "User Courses" section
    while (getline(userfile, line))
    {
		line.erase(0, line.find_first_not_of(" \t\r\n"));
        line.erase(line.find_last_not_of(" \t\r\n") + 1);

        if (line == "User Courses:")
        {
            break;
        }
	}
        // Read and discard the header line (coursename, grade, units, area)
        std::getline(userfile, line);
		line.clear();
        std::string course;
        double grade;
        int units, area;

        // Read courses until a blank line is encountered
        while (getline(userfile, line) && !line.empty())
        {
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if(line == " " || line.empty())
            {
                break;
            }

            std::istringstream iss(line);
            line.clear();
            
            if (iss >> course >> grade >> units >> area)
            {

                std::cout << "Read course: " << course << ", grade: " << grade << ", units: " << units << ", area: " << area << std::endl;
                courselist.insert(course, grade, units, area);
            }
            else
            {
                std::cerr << "Error: Unable to parse line - " << line << std::endl;
            }
        }
}
