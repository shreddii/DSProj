#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

miniGit::miniGit()
{
    commitsHead = new doublyNode();
    fs::create_directory(".minigit");
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

bool miniGit::inDirectory(string fileName)
{
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

void miniGit::remove()
{
    if (currCommit == nullptr)
    {
        cout << "Current commit is empty. No files to remove." << endl;
        return;
    }
    string fileName;
    cout << "Please enter fileName." << endl;
    cin >> fileName;
    singlyNode *prev = nullptr;
    singlyNode *tempFile = currCommit->head;
    while (tempFile != NULL)
    {
        if (tempFile->fileName == fileName)
        {
            prev->next = tempFile->next;
            delete tempFile;
            tempFile = prev->next;
            return;
        }
        prev = tempFile;
        tempFile = tempFile->next;
    }
    cout << "Removal unsuccessful: file not found." << endl;
}

void miniGit::commit()
{
    singlyNode *tempFile = currCommit->head;
    while (tempFile != NULL)
    {
        if (tempFile->fileVersion == "")
        { //if file version does not exist
            // copy the file from the current directory into the .minigit directory.
            // The newly copied file should get the name from the node’s fileVersion member.
            //(Note: this will only be the case when a file is added to the repository for the first time.)
        }
        else
        {   //if file version does exist in minigit
            //If the fileVersion file does exist in .minigit,
            //check whether the current direc- tory file has been changed
            //(i.e. has it been changed by the user?) with respect to the fileVersion file.
            //(To do the comparison, you can read in the file from the current directory into one string
            //and read in the file from the .minigit directory into another string, and check for equality.)
            //Based on the comparison result, do the following:
            //File is unchanged: do nothing.
            //File is changed: copy the file from the current directory to the .minigit directory,
            // and give it a name with the incremented version number. Also, update the SLL node member fileVersion to the incremented name.
        }
    }
}

bool isNumber(string s)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (isdigit(s.at(i)) == false)
            return false;
    }
    return true;
}

void miniGit::checkout()
{
    while (true)
    {   
        string entry;
        int number;
        cout << "\nPlease enter a commit number." << endl;
        cin >> entry;
        if (isNumber(entry))
        {
            number = stoi(entry);
            break;
        }
        else
        {
            cout << "Entry was not a valid number." << endl;
        }
    }
}