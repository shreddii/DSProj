#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>
#include <string>
namespace fs = std::filesystem;
using namespace std;

miniGit::miniGit()
{
    fs::remove_all(".minigit");
    fs::remove_all(".current");
    DLLHead = new doublyNode();
    DLLHead->commitNumber = 0;
    fs::create_directory(".minigit");
    fs::create_directory(".current");
}

void miniGit::add()
{
    string fileName;
    cout << "Please enter fileName." << endl;
    cin >> fileName;
    while (inDirectory(fileName))
    {
        cout << "Already in directory. Enter a valid file name.\n"
             << endl;
        cin >> fileName;
    }

    if (inSLL(fileName))
    {
        cout << "The file has already been added and it cannot be added twice.\n"
             << endl;
        return;
    }

    singlyNode *newSLLNode = new singlyNode();
    newSLLNode->fileName = fileName;

    //name of repository file
    newSLLNode->fileVersion = fileName + "00";
    newSLLNode->next = NULL;

    if (DLLHead->head == nullptr)
    {
        DLLHead->head = newSLLNode;
    }
    else
    {
        singlyNode *SLLTempNode = DLLHead->head;
        while (SLLTempNode->next != nullptr)
        {
            SLLTempNode = SLLTempNode->next;
        }
        //fixed
        SLLTempNode->next = newSLLNode;
    }

    ofstream write;
    write.open("./.current/" + fileName);
    print();
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
    if (DLLHead->head == nullptr)
    {
        cout << "Current commit is empty. No files to remove." << endl;
        return;
    }

    //ask user for file
    string fileName;
    cout << "Please enter fileName." << endl;
    cin >> fileName;

    //remove from linked list
    if (DLLHead->head->fileName == fileName)
    {
        delete DLLHead->head;
        DLLHead->head = nullptr;
        fs::remove("./.current/" + fileName);
        return;
    }
    cout << "file is at the middle or end." << endl;
    singlyNode *prev = nullptr;
    singlyNode *tempFile = DLLHead->head;
    while (tempFile != nullptr)
    {
        if (tempFile->fileName == fileName)
        {
            cout << "file found!" << endl;
            prev->next = tempFile->next;
            delete tempFile;
            fs::remove("./.current/" + fileName);
            return;
        }
        prev = tempFile;
        tempFile = tempFile->next;
    }
    cout << "Removal unsuccessful: file not found." << endl;
    print();
}

void miniGit::commit()
{
    singlyNode *tempFile = DLLHead->head;
    while (tempFile != NULL) //go through all files in current commit
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
            // (Note: this will only be the case when a file is added to the repository for the first time.)
        }
        else //if file exists already
        {
            ifstream miniFile;
            miniFile.open("./minigit/" + tempFile->fileVersion);
            string miniLine;
            string sMini;

            ifstream currFile;
            currFile.open("./current/" + tempFile->fileVersion);
            string currLine;
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
    doublyNode *newCommit = new doublyNode();
    newCommit->next = DLLHead;
    DLLHead->previous = newCommit;
    DLLHead = newCommit;
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

void miniGit::print()
{
    doublyNode *DLLtemp = DLLHead;
    while (DLLtemp != nullptr)
    {
        cout << DLLtemp->commitNumber << ": ";
        singlyNode *SLLtemp = DLLHead->head;
        while (SLLtemp != nullptr)
        {
            cout << SLLtemp->fileName << ", ";
            SLLtemp = SLLtemp->next;
        }
        cout << endl;
        DLLtemp = DLLtemp->next;
    }
}