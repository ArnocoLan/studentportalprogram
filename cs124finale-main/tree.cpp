#include "tree.h"

//File Created/Worked by Lance Arnoco

/*
    TREENODE DEFINITIONS
*/
/*
    CONSTRUCTORS
*/
Treenode::Treenode() //Default Constructor
{
  left = nullptr;
  right = nullptr;
  data = ' '; 
}

Treenode::Treenode(std::string n)
{
  data = n;
  left = nullptr;
  right = nullptr;
}

/*
    TREE DEFINITIONS
*/

/*
    CONSTRUCTORS
*/
Tree::Tree()
{
    root = new Treenode("Do you prefer a CSU or UC?");
    //Left Side Questions
    root->left = new Treenode("Are you okay with writing Personal Interest Questions?");
    root->left->right = new Treenode("Maybe Look into CSUs");
    root->left->left = new Treenode("Are you okay with paying high tuition costs?");
    root->left->left->right = new Treenode("Maybe look into CSUs");
    root->left->left->left = new Treenode("SHOW COLLEGE DATA");

    //Right Side Questions
    root->right = new Treenode("Are you interested in schools with high prestige?");
    root->right->left = new Treenode("Maybe look into UCs");
    root->right->right = new Treenode("Do you enjoy Theoretical Approaches");
    root->right->right->left = new Treenode("Maybe look into UCs");
    root->right->right->right = new Treenode("EXPLAIN BENEFITS");
}

Tree::Tree(std::string n)
{
  root = new Treenode(n);
  root->left = nullptr;
  root->right = nullptr;
}

/*
    DELETE FUNCTIONS
*/

void Tree::delete_tree(Treenode*& parent)
{
    if(parent == nullptr)
    {
        return;
    }
    
    delete_tree(parent->left);
    delete_tree(parent->right);
    delete parent;
    
}

void Tree::delete_tree()
{
    
    std::cout << "Deleting Tree..." << std::endl;
    delete_tree(root);
    std::cout << "DELETED" << std::endl;
    
}
/*
    PRINT FUNCTIONS
*/

void Tree::print_tree() //Initial Call of Print
{
  std::cout << "Do you want to print the current the Binary tree?" << std::endl;
  std::string answer;
  do
  {
    std::cout << "Answer Y/N" << std::endl;
    
    std::cin >> answer;
  }
  while(answer != "Y" && answer != "y" && answer != "N" && answer != "n");
  
  if(answer == "Y" || answer == "y")
  {
    print_tree(root);
  }
  else
  {
    return;
  }
}

void Tree::print_tree(Treenode* parent) //Post order print
{
    
    if(parent == nullptr)
    {
        return;
    }
    
    std::cout << parent->data << " ";
    
    print_tree(parent->left);

    print_tree(parent->right);

}


void Tree::print_current_node(College helper)
{
    Treenode* traverse = root;
    std::cout << traverse->data << std::endl;

    std::string answer;
    do
    {
        std::cout << "UC/CSU" << std::endl;
        std::cin >> answer;
    }
    while(answer != "UC" && answer != "CSU");

    if(answer == "UC")
    {
        traverse = traverse->left;
    }
    else
    {
        traverse = traverse->right;
    }
    continue_questions(traverse, helper);
    
}

void Tree::continue_questions(Treenode* traverse, College helper)
{
    if(traverse == nullptr || traverse->data.find("Maybe") != std::string::npos)
    {
		std::cout << std::endl;
		std::cout << traverse->data << std::endl;
		std::cout << std::endl;
        return;
    }
    
    else
    {
		std::cout << std::endl;
        std::cout << traverse->data << std::endl;
        std::string answer;
        do
        {
            std::cout << "Y/N" << std::endl;
            std::cin >> answer;
        }
        while(answer != "Y" && answer != "N" && answer != "y" && answer != "n");
    
        if(answer == "Y" || answer == "y")
        {
            traverse = traverse->left;
        }
        else
        {
            traverse = traverse->right;
        }
        
        if(traverse->data == "EXPLAIN BENEFITS")
        {
			std::cout << std::endl;
			std::cout << "CSUs ARE MEANT FOR YOU however..." << std::endl;
			std::cout << std::endl;
			
            std::cout << "UCs tend to teach students more theoretical approaches to their craft to better encourage \"expansions\" in the respective field" << std::endl;
            std::cout << "Theoretical lessons encourage students to explore and test new ideas to improve the knowledge of the entire world rather than just get started in the work force!" << std::endl;
            std::cout << "This does not mean you should not attend UCs if you dislike thinking beyond but instead understand the types of lessons you may be encouraged/forced to take" << std::endl;
            std::cout << "Both types of schools provide a good foundation in achieving your goals so do not be afraid of either one!" << std::endl;
            std::cout << std::endl;
            std::cout << "Talk to a counselor if you have any more questions!" << std::endl;
            std::cout << std::endl;
            return;
        }
        else if (traverse->data == "SHOW COLLEGE DATA")
        {
			
			std::cout << "UCs ARE MEANT FOR YOU and..." << std::endl;
			std::cout << std::endl;
			
            //Display all UCs Information 
            helper.display_uc();
            return;
            
        }
        else if (traverse != nullptr)
        {
            continue_questions(traverse, helper);
        }
        else
        {
            std::cout << "Finished Questions" << std::endl;
            return;
        }
    }
    
}
