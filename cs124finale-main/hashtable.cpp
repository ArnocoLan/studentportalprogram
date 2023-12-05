#include "hashtable.h"

// -------------------------------- Node Class Functions -------------------------------- //

Node::Node()
{
    Course course;
    course.grade = 0.0;
    course.units = 0;
    course.area = 0;
    course_info["course"] = course;
    next = nullptr;
}

Node::Node(const std::string& course, double grade, int units, int area)
{
    Course newcourse;
    newcourse.grade = grade;
    newcourse.units = units;
    newcourse.area = area;
    course_info[course] = newcourse;
    next = nullptr;
}

std::string Node::get_course() const
{
    return course_info.begin()->first;
}

double Node::get_grade() const
{
    return course_info.at(get_course()).grade;
}

int Node::get_units() const
{
    return course_info.at(get_course()).units;
}

int Node::get_area() const
{
    return course_info.at(get_course()).area;
}

Node* Node::get_next() const
{
    return next;
}

// -------------------------------- Iterator Class Functions -------------------------------- //

std::string Iterator::get_course() const
{
    return current->get_course();
}

double Iterator::get_grade() const
{
    return current->get_grade();
}

int Iterator::get_units() const
{
    return current->get_units();
}

int Iterator::get_area() const
{
    return current->get_area();
}

void Iterator::next()
{
    if (current != nullptr && current->get_next() != nullptr)
    {
        // Advance in the same bucket
        current = current->get_next();
    }
    else
    {
        // Move to the next bucket
        do
        {
            bucket_index++;
        } while (bucket_index < container->TABLE_SIZE && container->buckets[bucket_index] == nullptr);

        if (bucket_index < container->TABLE_SIZE)
        {
            // Start of the next bucket
            current = container->buckets[bucket_index];
        }
        else
        {
            // No more buckets
            current = nullptr;
        }
    }
}

bool Iterator::equals(const Iterator& other) const
{
    return current == other.current;
}

// -------------------------------- Hashtable Class Functions -------------------------------- //

// Constructor
Hashtable::Hashtable()
{
    current_size = 0;
    area1completed = false;
    area2completed = false;
    area3completed = false;
    area4completed = false;
    area5completed = false;
    area6completed = false;
    area7completed = false;
    buckets = new Node*[TABLE_SIZE];
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        buckets[i] = nullptr;
    }
}

// Destructor
Hashtable::~Hashtable()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* current = buckets[i];
        while (current != nullptr)
        {
            Node* next = current->get_next();
            delete current;
            current = next;
        }
    }
    delete[] buckets;
}

int Hashtable::size() const
{
    return current_size;
}

void Hashtable::insert(const std::string& course, double grade, int units, int area)
{
    int index = hash_compression(course);
    Node* newnode = new Node(course, grade, units, area);

    newnode->next = buckets[index];
    buckets[index] = newnode;

    current_size++;
}

// Note - unused so far
bool Hashtable::search(const std::string& course, double& grade, int& units, int& area)
{
    int index = hash_compression(course);
    Node* current = buckets[index];

    // Traverse the bucket to find the node with the specified course
    while (current != nullptr)
    {
        if (current->get_course() == course)
        {
            // Course found, update the parameters and return true
            grade = current->get_grade();
            units = current->get_units();
            area = current->get_area();
            return true;
        }
        current = current->get_next();
    }
    // Course not found
    return false;
}

// Note - unused so far
void Hashtable::remove(const std::string& course)
{
    int index = hash_compression(course);
    Node* current = buckets[index];
    Node* prev = nullptr;

    // Traverse the bucket to find the node with the specified course
    while (current != nullptr)
    {
        if (current->get_course() == course)
        {
            // Course found, update the pointers to remove the node
            if (prev != nullptr)
            {
                prev->next = current->get_next();
            }
            else
            {
                // If the node to be removed is the first in the bucket
                buckets[index] = current->get_next();
            }

            delete current;

            current_size--;

            return;
        }

        prev = current;
        current = current->get_next();
    }
}

Iterator Hashtable::begin() const
{
    Iterator iter;
    iter.current = nullptr;
    iter.bucket_index = -1;
    iter.container = this;
    iter.next();
    return iter;
}

Iterator Hashtable::end() const
{
    Iterator iter;
    iter.current = nullptr;
    iter.bucket_index = current_size;
    iter.container = this;
    return iter;
}

std::string Hashtable::hash_code(const std::string& str)
{
    int h = 0;
    for (char character : str)
    {
        h = 31 * h + character;
    }
    std::string code = std::to_string(h);
    return code;
}

int Hashtable::hash_compression(const std::string& str)
{
    std::string code = hash_code(str);
    int x = std::stoi(code);
    x = x % TABLE_SIZE;
    if (x < 0)
    {
        x = -x;
    }
    return x;
}

double Hashtable::calculate_gpa() const
{
    double totalgpa = 0.0;
    int totalunits = 0;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* current = buckets[i];

        while (current != nullptr)
        {
            const std::string& coursename = current->get_course();

            totalgpa += current->course_info[coursename].grade * current->course_info[coursename].units;
            totalunits += current->course_info[coursename].units;

            current = current->get_next();
        }
    }

    if (totalunits > 0)
    {
        return totalgpa / totalunits;
    }
    else
    {
        return 0.0;
    }
}

void Hashtable::display() const
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* current = buckets[i];

        while (current != nullptr)
        {
            std::cout << "Course: " << current->get_course() << ", "
                      << "Grade: " << current->get_grade() << ", "
                      << "Units: " << current->get_units() << ", "
                      << "Area: " << current->get_area() << std::endl << std::endl;

            current = current->get_next();
        }
    }
}

void Hashtable::write_GEcourselist_to_userfile(std::fstream& userfile)
{
    userfile << "User Courses:" << std::endl;
    userfile << "Coursename" << "\t" << "Grade" << "\t" << "Units" << "\t" << "Area" << std::endl;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        Node* current = buckets[i];

        while (current != nullptr)
        {
            userfile << current->get_course() << "\t" << current->get_grade() << "\t" << current->get_units() << "\t" << current->get_area() << std::endl;

            current = current->get_next();
        }
    }
    userfile << std::endl;
}

void Hashtable::check_IGETC()
{
    // Array to hold the counters for each area
    int area_count[7] = {0, 0, 0, 0, 0, 0, 0};

    // Iterate through each bucket in the hashtable
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Start with the first node in the current bucket
        Node* current = buckets[i];

        // Iterate through the nodes in the current bucket
        while (current != nullptr)
        {
            // Get the area for the current node
            int coursearea = current->get_area();

            // Increment the corresponding area counter
            if (coursearea >= 1 && coursearea <= 7)
            {
                area_count[coursearea - 1]++;
            }

            // Move to the next node in the current bucket
            current = current->get_next();
        }
    }
    std::string area1info = area1(area_count[0]);
    std::string area2info = area2(area_count[1]);
    std::string area3info = area3(area_count[2]);
    std::string area4info = area4(area_count[3]);
    std::string area5info = area5(area_count[4]);
    std::string area6info = area6(area_count[5]);
    std::string area7info = area7(area_count[6]);

    std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
    std::cout << area1info << std::endl << area2info << std::endl << area3info << std::endl << area4info << std::endl;
    std::cout << area5info << std::endl << area6info << std::endl << area7info << std::endl;
    if (area1completed == true && area2completed == true && area3completed == true && area4completed == true && area5completed == true && area6completed == true && area7completed == true)
    {
        std::cout << "You are eligible for IGETC transfer!" << std::endl;
    }
    else
    {
        std::cout << "Sorry, you are not yet eligible for IGETC transfer." << std::endl << std::endl;
    }
    
}

// Area 1 - English
std::string Hashtable::area1(int num)
{
    std::cout << "Area 1: " << num << " courses completed." << std::endl;
    if (num >= 2)
    {
        std::string answer;
        do
        {
            std::cout << "You have 2 English courses completed. Do they fulfill the IGETC requirements of: " << std::endl;
            std::cout << "One course in English composition and one course in critical thinking/English composition? Y/N" << std::endl;
            std::cin >> answer;
            if (answer == "Y" || answer == "y")
            {
                std::string csu;
                do
                {
                    std::cout << "Are you interested in applying to a CSU?" << std::endl;
                    std::cin >> csu;
                    if (csu == "Y" || csu == "y")
                    {
                        std::string communications;
                        do
                        {
                            std::cout << "If so, have you taken a course of communications? Y/N" << std::endl;
                            std::cin >>communications;
                            if (communications == "Y" || communications == "y")
                            {
                                std::cout << "Congratulations! You have completed Area 1 requirements for IGETC for UCs and CSUs." << std::endl;
                                area1completed = true;
                                return "Area 1 requirements for IGETC fulfilled.";
                            }
                            else if (communications == "N" || communications == "n")
                            {
                                std::cout << "Take a communications class to be eligible for IGETC for CSUs." << std::endl;
                                return "Area 1 requirements for IGETC unfulfilled.";
                            }
                        } 
                        while (communications != "Y" && communications != "y" && communications != "N" && communications != "n");
                    }
                    else if (csu == "N" || csu == "n")
                    {
                        std::cout << "Congratulations! You have completed Area 1 requirements for IGETC for UCs." << std::endl;
                        area1completed = true;
                        return "Area 1 requirements for IGETC fulfilled.";
                    }
                } 
                while (csu != "Y" && csu != "y" && csu != "N" && csu != "n");
            }
            else if (answer == "N" || answer == "n")
            {
                std::cout << "Take a English composition class and finish the requirements for Area 1 IGETC!" << std::endl;
                return "Area 1 requirements for IGETC unfulfilled.";
            }
        }
        while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");
    }
    else if (num == 1)
    {
        std::cout << "Take another English composition class and finish the requirements for Area 1 IGETC!" << std::endl;
        return "Area 1 requirements for IGETC unfulfilled.";
    }
    else if (num == 0)
    {
        std::cout << "Take two English courses! One course in English composition and one course in critical thinking/English composition." << std::endl;
        return "Area 1 requirements for IGETC unfulfilled.";
    }
    return "";
}

// Area 2 - Math
std::string Hashtable::area2(int num)
{
    std::cout << "Area 2: " << num << " courses completed." << std::endl;
    if (num >= 1)
    {
        std::cout << "Area 2 requirements for IGETC fulfilled!" << std::endl;
        area2completed = true;
        return "Area 2 requirements for IGETC fulfilled.";
    }
    else
    {
        std::cout << "Take a math class to fulfill Area 2 IGETC requirements!" << std::endl;
        return "Area 2 requirements for IGETC unfulfilled.";
    }
    return "";
}

// Area 3 - Arts and Humanities
std::string Hashtable::area3(int num)
{
    std::cout << "Area 3: " << num << " courses completed." << std::endl;
    if (num >= 3)
    {
        std::string answer;
        do
        {
            std::cout << "Area 3 requires three courses with at least one from the arts and one from the humanities. Do you fulfill these conditions? Y/N" << std::endl;
            std::cin >> answer;
            if (answer == "Y" || answer == "y")
            {
                std::cout << "Congratulations! You have completed Area 3 requirements for IGETC." << std::endl;
                area3completed = true;
                return "Area 3 requirements for IGETC fulfilled.";
            }
            if (answer == "N" || answer == "n")
            {
                std::cout << "Make sure you take at least one arts and one humanities class, and the additional one from either!" << std::endl;
                return "Area 3 requirements for IGETC unfulfilled.";
            }
        } 
        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n");
    }
    else
    {
        std::cout << "Make sure you take at least one arts and one humanities class, and the additional one from either!" << std::endl;
        return "Area 3 requirements for IGETC unfulfilled.";
    }
    return "";
}

// Area 4 - Social and Behavioral Sciences
std::string Hashtable::area4(int num)
{
    std::cout << "Area 4: " << num << " courses completed." << std::endl;
    if (num >= 2)
    {
        std::cout << "You have fulfilled the requirements for Area 4 - Social and Behavioral Sciences." << std::endl;
        area4completed = true;
        return "Area 4 requirements for IGETC fulfilled.";
    }
    else if (num == 1)
    {
        std::cout << "Complete another area 4 eligible course to fullfill this requirement." << std::endl;
        return "Area 4 requirements for IGETC unfulfilled.";
    }
    else
    {
        std::cout << "Complete two area 4 eligible courses of social and behavioral sciences to fullfill this requirement." << std::endl;
        return "Area 4 requirements for IGETC unfulfilled.";
    }
    return "";
}

// Area 5 - Physical and Biological Sciences
std::string Hashtable::area5(int num)
{
    std::cout << "Area 5: " << num << " courses completed." << std::endl;
    if (num >= 2)
    {
        std::string answer;
        do
        {
            std::cout << "Have you completed at least one physical science course and one biological science or course, at least one of which includes a lab? Y/N" << std::endl;
            std::cin >> answer;
            if (answer == "Y" || answer == "y")
            {
                std::cout << "Congratulations! You have completed the area 5 requirements for IGETC." << std::endl;
                area5completed = true;
                return "Area 5 requirements for IGETC fulfilled.";
            }
            else if (answer == "N" || answer == "N")
            {
                std::cout << "Make sure to take at least one physical science course and one biological science or course, at least one of which includes a lab!" << std::endl;
                return "Area 5 requirements for IGETC unfulfilled.";
            }
        } 
        while (answer != "Y" && answer != "y" && answer != "N" && answer != "n");
    }
    else
    {
        std::cout << "Make sure to take at least one physical science course and one biological science or course, at least one of which includes a lab!" << std::endl;
        return "Area 5 requirements for IGETC unfulfilled.";
    }
    return "";
}

// Area 6
std::string Hashtable::area6(int num)
{
    std::cout << "Area 6: " << num << " courses completed." << std::endl;
    std::string answer;
    do
    {
        std::cout << "Have you completed the equivalent of 2 years of high school language courses?" << std::endl;
        std::cin >> answer;
        if (answer == "Y" || answer == "y")
        {
            std::cout << "Congratulations! You have completed the area 6 requirements for IGETC." << std::endl;
            area6completed = true;
            return "Area 6 requirements for IGETC fulfilled.";
        }
        else if (answer == "N" || answer == "n")
        {
            std::cout << "Complete at least the equivalent of 2 years of high school language courses to fulfill this area requirement." << std::endl;
            return "Area 6 requirements for IGETC unfulfilled.";
        }
    } 
    while (answer != "Y" && answer != "y" && answer != "N" && answer != "n");
    return "";
}

// Area 7 - Ethnic Studies
std::string Hashtable::area7(int num)
{
    std::cout << "Area 7: " << num << " courses completed." << std::endl;
    if (num >= 1)
    {
        std::cout << "Congratulations! You have completed the area 7 requirements for IGETC." << std::endl;
        area7completed = true;
        return "Area 7 requirements for IGETC fulfilled.";
    }
    else
    {
        std::cout << "Complete at least one course of ethnic studies to fulfill this area requirement." << std::endl;
        return "Area 7 requirements for IGETC unfulfilled.";
    }
    return "";
}
