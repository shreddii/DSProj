#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;
using namespace std;

miniGit::miniGit()
{
    DLLHead = new doublyNode();
    fs::create_directory(".minigit");
    fs::create_directory(".current");
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

    ofstream write;
    write.open("./.current/" + fileName);
}

bool miniGit::inDirectory(string fileName)
{
    //finish this function
    //need to fix because path before name
    return fs::exists("./.current/" + fileName);
}

bool miniGit::inSLL(string fileName)
{
    singlyNode *tempFile = DLLHead->head;
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
    doublyNode *tempCommit = DLLHead;
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
    if (DLLHead == nullptr)
    {
        cout << "Current commit is empty. No files to remove." << endl;
        return;
    }
    string fileName;
    cout << "Please enter fileName." << endl;
    cin >> fileName;
    singlyNode *prev = nullptr;
    singlyNode *tempFile = DLLHead->head;
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
    singlyNode *tempFile = DLLHead->head;
    while (tempFile != NULL)
    {
        if (tempFile->fileVersion == "")
        { //if file version does not exist
            ofstream write;
            write.open("./minigit/" + tempFile->fileName);
            ifstream read;
            read.open("./current/" + tempFile->fileName);
            string line;
            while (getline(read, line))
            {
                write << line << endl;
            }
            // copy the file from the current directory into the .minigit directory.
            // The newly copied file should get the name from the node’s fileVersion member.
            //(Note: this will only be the case when a file is added to the repository for the first time.)
        }
        else
        {
            ifstream miniFile;
            ifstream currFile;
            miniFile.open("./minigit/" + tempFile->fileVersion);
            currFile.open("./current/" + tempFile->fileVersion);
            string miniLine;
            string currLine;
            string sMini;
            string sCurr;
            while (getline(miniFile, miniLine))
            {
                sMini += miniLine;
            }
            while (getline(currFile, currLine))
            {
                sCurr += currLine;
            }
            if (sMini.compare(sCurr) != 0)
            { //if they arent the same
                int currVersion = stoi(tempFile->fileVersion.erase(0, tempFile->fileName.size()));
                currVersion++;
                string newName = tempFile->fileName + to_string(currVersion);
                tempFile->fileVersion = newName;
                ofstream write;
                write.open("./minigit/" + tempFile->fileVersion);
                ifstream read;
                read.open("./current/" + tempFile->fileVersion);
                string line;
                while (getline(read, line))
                {
                    write << line << endl;
                }
            }
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
    int number;
    while (true)
    {
        string entry;
        cout << "\nPlease enter a commit number." << endl;
        cin >> entry;
        if (isNumber(entry))
        {
            number = stoi(entry);
            break;
        }
        else
        {
            cout << "Entry was not in number format." << endl;
        }
    }
    doublyNode *temp = DLLHead;
    while (temp != nullptr)
    {
        if (temp->commitNumber == number)
        {
            DLLHead->head = temp->head;
        }
    }
}