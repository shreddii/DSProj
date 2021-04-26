#include <iostream>
using namespace std;
#include <filesystem>
#include "miniGit.hpp"

//g++ main.cpp miniGit.cpp -o main -std=c++17

//Leeb's bruh knowledge:
//To make changes to the repo
//make the change
//In terminal
//git add .
//git commit -m "message"
//git push

//always git pull before editing and usually before get push (if get error)

// bool isANumber(string s)
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
    miniGit *m = new miniGit();
    string stringIn;
    int intIn;

    displayMenu1();
    cin >> stringIn;

    while (!m->isNumber(stringIn))
    {
        cout << "please enter a valid number." << endl;
        displayMenu1();
        cin >> stringIn;
    }

    intIn = stoi(stringIn);

    switch (intIn)
    {
    case 0:
        break;
    case 1:
        cout << "\nInitializing a new empty repository in the current directory. \n"
             << endl;
        bool keepGoing = true;

        while (keepGoing == true)
        {
            displayMenu2();
            cin >> stringIn;
            while (!m->isNumber(stringIn))
            {
                cout << "please enter a valid number." << endl;
                displayMenu2();
                cin >> stringIn;
            }
            intIn = stoi(stringIn);

            switch (intIn)
            {
            case 1:
                m->add();
                break;
            case 2:
                m->remove();
                break;
            case 3:
                m->commit();
                break;
            case 4:
                m->checkout();
                break;
            case 5:
                keepGoing = false;
                break;
            }
        }

        break;
    }

    cout << "\nGoodbye!" << endl;
}
