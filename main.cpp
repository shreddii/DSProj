#include <iostream>
using namespace std;
#include <filesystem>
#include "miniGit.hpp"

//Leeb's bruh knowledge:
//To make changes to the repo
//make the change
//In terminal
//git add .
//git commit -m "message"
//git push

//always git pull before editing and usually before get push (if get error)

// bool isNumber(string s)
// {
//     for (int i = 0; i < s.size(); i++)
//     {
//         if (isdigit(s.at(i)) == false)
//             return false;
//     }
//     return true;
// }

void displayMenu1()
{
    cout << "\nWould you like to to initialize an empty repository in the current directory?" << endl;
    cout << "(enter 1 for YES)" << endl;
    cout << "(enter 0 for  NO.)\n"
         << endl;
}

void displayMenu2()
{
    cout << "\nTo add a file, enter 1." << endl;
    cout << "To remove a file, enter 2." << endl;
    cout << "To commit, enter 3." << endl;
    cout << "To checkout, enter 4." << endl;
    cout << "To quit, enter 5.\n"
         << endl;
}

int main()
{
    string stringInput;
    int intInput;

    displayMenu1();
    cin >> stringInput;

    // if (isNumber(stringInput))
    // {
    //     intInput = stoi(stringInput);
    // }

    intInput = stoi(stringInput);

    switch (intInput)
    {
    case 0:
        break;
    case 1:
        cout << "\nInitializing a new empty repository in the current directory. \n"
             << endl;
        miniGit *m = new miniGit();
        bool keepGoing = true;
        while (keepGoing == true)
        {
            displayMenu2();
            int in2;
            cin >> in2;
            string fileName;
            string entry = "";
            int commitNumber;
            switch (in2)
            {
            case 1:
                //add file
                cout << "\nAdding a file" << endl;
                m->add();
                break;
            case 2:
                //remove file
                cout << "\nRemoving a file" << endl;
                m->remove();
                break;
            case 3:
                //commit
                break;
            case 4:
                //checkout
                
                break;
            case 5:
                //quit
                keepGoing = false;
                break;
            }
        }
        break;
    }

    cout << "\nGoodbye!" << endl;
}
