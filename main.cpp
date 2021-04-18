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

bool isNumber(string s){
    for(int i = 0; i < s.size(); i++){
        if(isdigit(s.at(i))==false)
            return false;
    }
    return true;
}

int main(){
    int flag = 1;
    int in1;
    while(flag == 1){
        cout << "Would you like to to initialize an empty repository in the current directory?" << endl;
        cout << "(enter 1 for YES)" << endl;
        cout << "(enter 0 for  NO.)" << endl;
        cin>>in1;
        switch(in1){
            case 0:
                break;
            case 1:
                cout<<"initializing a new empty repository in the current directory."<<endl;
                //initialize new repo
                bool keepGoing = true;
                while(keepGoing == true){
                    int in2;
                    cout<<"To add a file, enter 1."<<endl;
                    cout<<"To remove a file, enter 2."<<endl;
                    cout<<"To commit, enter 3."<<endl;
                    cout<<"To checkout, enter 4."<<endl;
                    cout<<"To quit, enter 5."<<endl;
                    cin>>in2;
                    string fileName;
                    string entry = "";
                    int commitNumber;
                    switch(in2){
                        case 1:                       
                            cout << "Please enter file name."<<endl;
                            cin>>fileName;
                            break;
                        case 2:                       
                            cout << "Please enter file name."<<endl;
                            cin>>fileName;
                            break;
                        case 3:
                            break;
                        case 4:
                            while(true){
                                cout << "Please enter a commit number." << endl;
                                cin>>entry;
                                if(isNumber(entry)){
                                    commitNumber = stoi(entry);
                                }else{
                                    cout<<"Entry was not a valid number."<<endl;
                                    continue;
                                }
                                break;
                            }
                            break;
                        case 5:
                            keepGoing = false;
                            in1 = 0;
                            break;
                    }
                }
        }
        cout << "press  1 to continue, press 0 to quit." << endl;
        cin>>flag;
    }  
}

