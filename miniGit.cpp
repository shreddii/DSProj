#include <iostream>
#include "miniGit.hpp"
#include <fstream>

using namespace std;

miniGit::miniGit(){
    commitsHead = new doublyNode();
}

void miniGit::add(){
    string fileName;
    cout<<"Enter a file name"<<endl;
    cin>>fileName;

    // while(!inDirectory(fileName)){
    //     cout<<"Not in directory. Enter a valid file name"<<endl;
    //     cin>>fileName;
    // }

}

bool miniGit::inSLL(string fileName){
    singlyNode* tempFile = currCommit->head;
    while(tempFile != NULL){
        if(tempFile -> fileName == fileName){
             return true;
        }
        tempFile = tempFile->next;
    }
    return false;
}

bool miniGit::inDLL(string fileName){
    if(fileName == ""){
        return false;
    }
    doublyNode* tempCommit = commitsHead;
    while(tempCommit != NULL){
        singlyNode* tempFile = tempCommit->head;
        while(tempFile != NULL){
            if(tempFile -> fileName == fileName){
                return true;
            }
            tempFile = tempFile->next;
        }
        tempCommit = tempCommit->next;
    }
    return false;
}







