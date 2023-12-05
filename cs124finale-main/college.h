#ifndef COLLEGE_H
#define COLLEGE_H

#include "variable.h"

class College
{
  public:
  //setters
  void set_school_names(std::string new_school_names);
  void set_student_grads(int new_student_grads);
  void set_fulltime_students(int new_fulltime_students);
  void set_aid_percentile(double new_aid_percentile);
  void set_student_count(int new_student_count);
  void set_school_size(double new_school_size);
  void set_avg_rewards(double new_avg_rewards);

  //getters
  std::string get_school_names() const;
  int get_student_grads() const;
  int get_fulltime_student() const;
  double get_aid_percentile() const;
  int get_student_count() const;
  double get_school_size() const;
  double get_avg_rewards() const;

  //member functions
  College();
  void pre_process(College*& c_array);
  void read_userfile(std::fstream& userfile, College*& userarray);
  void display_sort_criteria();
  int user_sort_criteria();
  void merge(int from, int mid, int to, int& sort_criteria, College*& c_array);
  void merge_sort(int from, int to, int& sort_criteria, College*& c_array);
  void user_file(std::fstream& userfile, College*& c_array, College*& user_array);
  void print_mergesort(int& sort_criteria, College*& c_array);
  void display_uc();
  void write_userlist_to_file(std::fstream& userfile, College*& user_array);
  void collegemenu(std::fstream& userfile, College*& c_array, College*& user_array);
  void display_colleges(College* c_array);
  void delete_college(College*& c_array, College*& user_array);


  private:
  std::string school_names;
  int student_grads;
  int fulltime_student;
  double aid_percentile;
  int student_count;
  double school_size;
  double avg_rewards;
  

};


#endif
