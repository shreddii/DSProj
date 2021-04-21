#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;

miniGit::miniGit()
{
    commitsHead = new doublyNode();
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
    //finish this function
    return false;
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

void miniGit::remove(){
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
    cout<<"Removal unsuccessful: file not found."<<endl;
}