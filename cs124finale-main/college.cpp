#include "college.h"

//default constructor
College::College()
{
    school_names = " ";
    student_grads = 0;
    fulltime_student = 0;
    aid_percentile = 0.0;
    student_count = 0;
    school_size = 0.0;
    avg_rewards = 0.0;
}

//setters
  void College::set_school_names(std::string new_school_names)
  {
    school_names = new_school_names;
  }
  void College::set_student_grads(int new_student_grads)
  {
    student_grads = new_student_grads;
  }
  void College::set_fulltime_students(int new_fulltime_students)
  {
    fulltime_student = new_fulltime_students;
  }
  void College::set_aid_percentile(double new_aid_percentile)
  {
    aid_percentile = new_aid_percentile;
  }
  void College::set_student_count(int new_student_count)
  {
    student_count = new_student_count;
  }
  void College::set_school_size(double new_school_size)
  {
    school_size = new_school_size;
  }
  void College::set_avg_rewards(double new_avg_rewards)
  {
    avg_rewards = new_avg_rewards;
  }

  //getters
  std::string College::get_school_names() const
  {
    return school_names;
  }
  int College::get_student_grads() const
  {
    return student_grads;
  }
  int College::get_fulltime_student() const
  {
    return fulltime_student;
  }
  double College::get_aid_percentile() const
  {
    return aid_percentile;
  }
  int College::get_student_count() const
  {
    return student_count;
  }
  double College::get_school_size() const
  {
    return school_size;
  }
  double College::get_avg_rewards() const
  {
    return avg_rewards;
  }

void College::pre_process(College*& c_array)
{
  std::ifstream in_file; 
  in_file.open("collegedata.csv");
  int commas = 0;
  int i = 0;


  if (in_file.fail())
  {
    std::cout << "Cannot read from file." << std::endl;
  }
  else
  {
    std::string line;
    std::string word;
    std::getline(in_file, line);
    while(std::getline(in_file, line))
    {
        std::stringstream iss(line);
        while(std::getline(iss, word, ','))
        {
            
           if(commas == 0)
            {
               c_array[i].set_school_names(word);
            }
            

             if(commas == 7)
            {
                if(word == "")
                {
                   student_count = 0;
                   c_array[i].set_student_count(student_count);
                }
                else
                {
                  c_array[i].set_student_count(std::stod(word));
                }
    
            }


            if(commas == 8)
            {
                if(word == "")
                {
                  avg_rewards = 0;
                  c_array[i].set_avg_rewards(0);
                }
                else
                {
                  c_array[i].set_avg_rewards(std::stod(word));
                }
            
            }
            
    
            if(commas == 16)
            {
                if(word == "")
                {
                  fulltime_student = 0;
                  c_array[i].set_fulltime_students(0);
                }
                else
                {
                  c_array[i].set_fulltime_students(std::stoi(word));
                }
            }
    
    
            if(commas == 21)
            {
              if(word == "")
              {
                aid_percentile = 0;
                c_array[i].set_aid_percentile(0);
              }
              else
              {
                c_array[i].set_aid_percentile(std::stod(word));
              }
            }
    
    
              if(commas == 43)
              {
                if(word == "")
                {
                   student_grads = 0;
                   c_array[i].set_student_grads(0);
                }
                else
                {
                  c_array[i].set_student_grads(std::stoi(word));
                }
              }
      
        commas++; //where to place? here ig
      }
      i++;
      commas = 0;
    }
  }
    in_file.close();
}


void College::display_sort_criteria()
{
    std::cout << "Please choose one of the sorting criteria options." << std::endl;
    std::cout << "+-----------------------------------------------------+" << std::endl;
    std::cout << "|         Sorting Criteria Options                    |" << std::endl;
    std::cout << "+-----------------------------------------------------+" << std::endl;
    std::cout << "|     1. School Name                                  |" << std::endl;
    std::cout << "|     2. Student grads                                |" << std::endl; //change name
    std::cout << "|     3. Fulltime students                            |" << std::endl; //change name
    std::cout << "|     4. Aid percentile                               |" << std::endl;
    std::cout << "|     5. Student count                                |" << std::endl;
    std::cout << "|     6. School size                                  |" << std::endl;
    std::cout << "|     7. Average rewards                              |" << std::endl;
    std::cout << "+-----------------------------------------------------+" << std::endl;
}

int College::user_sort_criteria()
{
    std::cout << "Please choose one of the sorting criteria options (Select a number)." << std::endl;
    int sort_criteria;
    std::cin >> sort_criteria;
    while (sort_criteria != 1 && sort_criteria != 2 && sort_criteria != 3 && sort_criteria != 4 && sort_criteria !=5 && sort_criteria !=6 && sort_criteria !=7)
    {
        std::cout << "Invalid input. Please enter a number between 1-7." << std::endl;
        std::cin >> sort_criteria;
    }
    return sort_criteria;
}

void College::merge(int from, int mid, int to, int& sort_criteria, College*& c_array)
{
  int n = to - from + 1;
  College* b = new College[n];
  int i1 = from;
  int i2 = mid + 1;
  int j = 0;

  while (i1 <= mid && i2 <= to) {
      switch(sort_criteria) {
          case 1:
              if (c_array[i1].get_school_names() < c_array[i2].get_school_names()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 2:
              if (c_array[i1].get_student_grads() < c_array[i2].get_student_grads()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 3:
              if (c_array[i1].get_fulltime_student() < c_array[i2].get_fulltime_student()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 4:
              if (c_array[i1].get_aid_percentile() < c_array[i2].get_aid_percentile()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 5:
              if (c_array[i1].get_student_count() < c_array[i2].get_student_count()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 6:
              if (c_array[i1].get_school_size() < c_array[i2].get_school_size()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
          case 7:
              if (c_array[i1].get_avg_rewards() < c_array[i2].get_avg_rewards()) {
                  b[j] = c_array[i1];
                  i1++;
              } else {
                  b[j] = c_array[i2];
                  i2++;
              }
              j++;
              break;
      }
  }

  while (i1 <= mid) {
      b[j] = c_array[i1];
      i1++;
      j++;
  }

  while (i2 <= to) {
      b[j] = c_array[i2];
      i2++;
      j++;
  }

  for (j = 0; j < n; j++) {
      c_array[from + j] = b[j];
  }

  delete[] b;
}

void College::merge_sort(int from, int to, int& sort_criteria, College*& c_array)
{
    if (from == to) 
    { 
       return; 
    }

    int mid = (from + to) / 2;
    merge_sort(from, mid, sort_criteria, c_array);
    merge_sort(mid + 1, to, sort_criteria, c_array);
    merge(from, mid, to, sort_criteria, c_array);
}

void College::print_mergesort(int& sort_criteria, College*& c_array)
{
    std::cout << std::setw(20) << "School Name" << std::setw(15) << "Student Grads" << std::setw(20) << "Fulltime Students" << std::setw(15) << "Aid Percentile"
              << std::setw(15) << "Student Count" << std::setw(15) << "School Size" << std::setw(15) << "Average Rewards" << std::endl;
    std::cout << "+------------------------------------------------------------------------------------------------------------------------+" << std::endl;

    // Print all sorted criteria
    for (int i = 0; i < SIZE; i++) 
    {
        std::cout << std::setw(20) << c_array[i].get_school_names()
                  << std::setw(15) << c_array[i].get_student_grads()
                  << std::setw(20) << c_array[i].get_fulltime_student()
                  << std::setw(15) << c_array[i].get_aid_percentile()
                  << std::setw(15) << c_array[i].get_student_count()
                  << std::setw(15) << c_array[i].get_school_size()
                  << std::setw(15) << c_array[i].get_avg_rewards()
                  << std::endl;
    }

}


/* void user_file()
  {
    I have 28 universities in my c_array so it will list out each university with a number next to it which is the index number 
    it will then ask the user which universities information they would like to save and they enter the number or index of that university to choose it
    next it will go to that index and save the universities name along with its other information into a text file 
    
  } */

void College::user_file(std::fstream& userfile, College*& c_array, College*& user_array) 
{
    // Display a numbered list of universities
    std::cout << "List of Universities:" << std::endl;
    for (int i = 0; i < 28; i++) 
    {
        std::cout << i << ". " << c_array[i].get_school_names() << std::endl;
    }

    int collegenum;
    do
    {
      std::cout << "How many colleges would you like to save to the list (1-5)" << std::endl;
      std::cin >> collegenum;
      
    } 
    while (collegenum != 1 && collegenum != 2 && collegenum != 3 && collegenum != 4 && collegenum != 5); 
      

    // Ask the user to choose a university
    int arraysize = 0;
    for (int i = 0; i < collegenum; i++)
    {
      int user_choice;
      std::cout << "Enter the number of the university you want to save: ";
      std::cin >> user_choice;

      // Validate the user's input
      while (user_choice < 1 || user_choice > SIZE) 
      {
        std::cout << "Invalid input. Please enter a number between 1 and " << SIZE << ": ";
        std::cin >> user_choice;
      }
      // Adjust indexing
      int university_index = user_choice;

      // Save the information to list
      user_array[i] = c_array[university_index];
      arraysize++;
    }

    if (arraysize < 5)
    {
      user_array[arraysize].set_school_names("empty");
    }
}

void College::display_uc()
{
  std::cout << "University of California at Berkeley, Student Count: 25951, Student Graduates: N/A, Full-time Students: 97.2%, Aid percentile: 99, Average Rewards: 27.6%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Davis, Student Count: 26533, Student Graduates: N/A, Full-time Students: 97.3%, Aid percentile: 98, Average Rewards: 26.6%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Irvine, Student Count: 23530, Student Graduates: N/A, Full-time Students: 98.3%, Aid percentile: 99, Average Rewards: 26.5%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Los Angeles, Student Count: 28674, Student Graduates: N/A, Full-time Students: 97.9%, Aid percentile: 100, Average Rewards: 26.8%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Riverside, Student Count: 18621, Student Graduates: N/A, Full-time Students: 97.8%, Aid percentile: 100, Average Rewards: 21.9%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at San Diego, Student Count: 23805, Student Graduates: N/A, Full-time Students: 97.3, Aid percentile: 99, Average Rewards: 26.3%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Santa Barbara, Student Count: 19362, Student Graduates: N/A, Full-time Students: 98.5, Aid percentile: 99, Average Rewards: 26.7%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Santa Cruz, Student Count: 15695, Student Graduates: N/A, Full-time Students: 97.6, Aid percentile: 100, Average Rewards: 24.9%" << std::endl;
  std::cout << std::endl;
  std::cout << "University of California at Santa Cruz, Student Count: 15695, Student Graduates: N/A, Full-time Students: 97.6, Aid percentile: 100, Average Rewards: 24.9%" << std::endl;
  std::cout << std::endl;
}

//count columns/commas for pre-processing and skipping unnecessary fields
//college menu
//college user list
//menu user interface
//show user all sorting criteria
//once they pick ask if they would like to save college data to personal list
//save everything from file to list
/*
void College::read_userfile(std::fstream& userfile, College*& userarray)
{
    
    std::string line;
    std::getline(userfile, line); //Skips Header
    std::getline(userfile, line); //Skips Labels
    int array_index = 0;
    while(std::getline(userfile, line))
    {
		line.erase(0, line.find_first_not_of(" \t\r\n"));
		line.erase(line.find_last_not_of(" \t\r\n") + 1);
        if(line == "")
        {
            break;
        }
        else
        {
            std::string word;
            std::stringstream str(line);
            int count = 0;
            int intword;
            double doubleword;
            while(std::getline(str, word, ','))
            {
                if(count == 0)
                {
                    userarray[array_index].set_school_names(word);
                }
                else if(count == 1)
                {
                    intword = std::stoi(word);
                    userarray[array_index].set_student_count(intword);
                }
                else if(count == 2)
                {
                    doubleword = std::stod(word);
                    userarray[array_index].set_avg_rewards(doubleword);
                }
                else if(count == 3)
                {
                    intword = std::stoi(word);
                    userarray[array_index].set_fulltime_students(intword);
                }
                else if(count == 4)
                {
                    doubleword = std::stod(word);
                    userarray[array_index].set_aid_percentile(doubleword);
                }
                else if(count == 5)
                {
                    intword = std::stoi(word);
                    userarray[array_index].set_student_grads(intword);
                }
                count++;
            }
        }
        array_index++;
    }
}
*/
void College::write_userlist_to_file(std::fstream& userfile, College*& user_array)
{
  // Write header
  userfile << "User College List:" << std::endl;
  userfile << "college_name	student_grads	fulltime_student	aid_percentile	student_count	school_size	avg_rewards" << std::endl;

  // Traverse user list array and write to file
  for (int i = 0; i < 5; i++)
  {
    if (user_array[i].get_school_names() != "empty")
    {
      std::string university_info = user_array[i].get_school_names() +
                                 "," + std::to_string(user_array[i].get_student_grads()) +
                                 "," + std::to_string(user_array[i].get_fulltime_student()) +
                                 "," + std::to_string(user_array[i].get_aid_percentile()) +
                                 "," + std::to_string(user_array[i].get_student_count()) +
                                 "," + std::to_string(user_array[i].get_school_size()) +
                                 "," + std::to_string(user_array[i].get_avg_rewards());
      userfile << university_info << std::endl;
    }
    else
    {
      break;
    }
  }
  userfile << std::endl;
}

void College::collegemenu(std::fstream& userfile, College*& c_array, College*& user_array)
{
  pre_process(c_array);
  display_sort_criteria();
  int choice = user_sort_criteria();
  merge_sort(0, 28, choice, c_array);
  display_colleges(c_array);

}

void College::display_colleges(College* c_array)
{
  for (int i = 0; i < 28; i++)
  {
    std::string university_info = "University Name: " + c_array[i].get_school_names() +
                                 "\nStudent Grads: " + std::to_string(c_array[i].get_student_grads()) +
                                 "\nFulltime Students: " + std::to_string(c_array[i].get_fulltime_student()) +
                                 "\nAid Percentile: " + std::to_string(c_array[i].get_aid_percentile()) +
                                 "\nStudent Count: " + std::to_string(c_array[i].get_student_count()) +
                                 "\nSchool Size: " + std::to_string(c_array[i].get_school_size()) +
                                 "\nAverage Rewards: " + std::to_string(c_array[i].get_avg_rewards());
    std::cout << university_info << std::endl << std::endl;
  }
}

void College::delete_college(College*& c_array, College*& user_array)
{
	std::cout << "Deleting Colleges" << std::endl;
	delete[] c_array;
	delete[] user_array;
	std::cout << "DELETED" << std::endl;
}
