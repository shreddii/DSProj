#include <iostream>
#include "miniGit.hpp"
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
using namespace std;


int main(){
    fs::create_directory(".minigit");
    ofstream of;
    //create file for me
    // ./ is anything in current directory

    //puts new file into minigit directory using path
    of.open("./.minigit/file.txt");

    //writes text to file
    of<<"lskdfj;";

    //closes file
    of.close();
    
    //removes file
    // fs::remove("./.minigit/file.txt");

    //checks if the file exists in the directory
    // cout<<fs::exists("./.minigit/file.txt");

    //traverses and gets paths
    // for(auto& p: fs::directory_iterator(".minigit")){
    //     cout<<p.path()<<endl;
    // }

    return 0;
}

