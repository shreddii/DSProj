#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>

using namespace std;
//file system is library
namespace fs = std::__fs::filesystem;

miniGit::miniGit()
{   
    //fs can make a directory which is a folder in computer that holds files
    commitsHead = new doublyNode();
    fs::create_directory(".minigit");
    fs::remove_all(".minigit");
    
}

void miniGit::add()
{
    string fileName;
    cout << "Please enter fileName." << endl;
    cin >> fileName;
    while (!inDirectory(fileName))
    {
        cout << "Not in directory. Enter a valid file name.\n"
             << endl;
        cin >> fileName;
    }

    if (inSLL(fileName))
    {
        cout << "The file has already been added and it cannot be added twice.\n"
             << endl;
        return;
    }

    singlyNode *newSLL = new singlyNode();
    newSLL->fileName = fileName;

    //name of repository file
    newSLL->fileVersion = fileName + "00";
    newSLL->next = NULL;
}

//is it in the folder
bool miniGit::inDirectory(string fileName)
{
    //finish this function
    cout<<fs::current_path();

    return fs::exists(fileName);
}

bool miniGit::inSLL(string fileName)
{
    singlyNode *tempFile = currCommit->head;
    while (tempFile != NULL)
    {
        if (tempFile->fileName == fileName)
        {
            return true;
        }
        tempFile = tempFile->next;
    }
    return false;
}

bool miniGit::inDLL(string fileName)
{
    if (fileName == "")
    {
        return false;
    }
    doublyNode *tempCommit = commitsHead;
    while (tempCommit != NULL)
    {
        singlyNode *tempFile = tempCommit->head;
        while (tempFile != NULL)
        {
            if (tempFile->fileName == fileName)
            {
                return true;
            }
            tempFile = tempFile->next;
        }
        tempCommit = tempCommit->next;
    }
    return false;
}
