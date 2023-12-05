#ifndef TREE_H
#define TREE_H

/*
    Tree class constructed by Lance Arnoco. Inspiration from Zybooks starting code
*/

#include "variable.h"
#include "college.h"


class Treenode
{
    public:
        Treenode();

        Treenode(std::string n);

    private: 
        Treenode* left;

        Treenode* right;

        std::string data;

        friend class Tree;
};

class Tree
{
    public:

        //Constructors
        Tree();
        Tree(std::string question);

        //Delete Functions
        void delete_tree(Treenode*& parent); //Post-order delete function
        void delete_tree();

        //Print Functions
        void print_tree(Treenode* parent); //In order print function
        void print_tree();

        //User Functions
        void print_current_node(College helper);
        void continue_questions(Treenode* traverse, College helper);

    private:
        Treenode* root;
        



};

#endif
