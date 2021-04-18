#include <iostream>

using namespace std;

//each of doublyNodes corresponds to a single commit
struct doublyNode{
    int commitNumber;
    singlyNode *head;
    doublyNode *previous;
    doublyNode *next;
};

struct singlyNode{
    std::string fileName; //name of local file
    std::string fileVersion; //name of file in .minigit folder
    singlyNode *next;
};


