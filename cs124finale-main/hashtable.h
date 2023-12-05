#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "variable.h"

class Hashtable;
class Iterator;

struct Course 
{
    double grade;
    int units;
    int area;
};

class Node
{
public:
    Node();
    Node(const std::string& course, double grade, int units, int area);
    std::string get_course() const;
    double get_grade() const;
    int get_units() const;
    int get_area() const;
    Node* get_next() const;

private:
    std::unordered_map<std::string, Course> course_info;
    Node* next;

    friend class Hashtable;
    friend class Iterator;
};

class Iterator
{
public:
    std::string get_course() const;
    double get_grade() const;
    int get_units() const;
    int get_area() const;
    void next();
    bool equals(const Iterator& other) const;

private:
    const Hashtable* container;
    int bucket_index;
    Node* current;

    friend class Hashtable;
};

class Hashtable
{
public:
    Hashtable();
    ~Hashtable();
    int size() const;
    void insert(const std::string& course, double grade, int units, int area);
    bool search(const std::string& course, double& grade, int& units, int& area);
    void remove(const std::string& course);

    Iterator begin() const;
    Iterator end() const;

    std::string hash_code(const std::string& str);
    int hash_compression(const std::string& str);

    double calculate_gpa() const;
    void display() const;
    void write_GEcourselist_to_userfile(std::fstream& userfile);


    // GE Course functions 
    void check_IGETC();
    std::string area1(int num);
    std::string area2(int num);
    std::string area3(int num);
    std::string area4(int num);
    std::string area5(int num);
    std::string area6(int num);
    std::string area7(int num);

private:
    static const int TABLE_SIZE = 10;
    Node** buckets;
    int current_size;
    bool area1completed;
    bool area2completed;
    bool area3completed;
    bool area4completed;
    bool area5completed;
    bool area6completed;
    bool area7completed;
    friend class Iterator;
};

#endif
