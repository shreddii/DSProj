#include <iostream>
using namespace std;
//Leeb's bruh knowledge:
//To make changes to the repo
//make the change
//In terminal
//git add .
//git commit -m "message"
//git push

//always git pull before editing and usually before get push (if get error)

int main(){
    int flag = 1;
    int in;
    while(flag == 1){
        cout << "Would you like to to initialize an empty repository in the current directory?" << endl;
        cout << "(enter 1 for YES)" << endl;
        cout << "(enter 0 for  NO.)" << endl;
        cin>>in;
        switch(in){
            case 0:
                break;
            case 1:
                cout<<"initializing a new empty repository in the current directory."<<endl;
                break;
            default:
                cout<<"please enter a different number."<<endl;
                continue;
        }
        cout << "press  1 to continue, press 0 to quit." << endl;
        cin>>flag;
    }  
}

