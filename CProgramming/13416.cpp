#include <iostream>
#include "function.h"
using namespace std;

int main(){
    Implement ht = *(new Implement());
    string command, str;

    while(cin>>command){
        if(command == "add"){
            cin>>str;
            ht.Add(str);
        }else if(command == "delete"){
            cin >> str;
            ht.Delete(str);
        }else if(command == "exist"){
            cin >> str;
            bool is_exist = ht.Exist(str);
            if(is_exist)
                cout<<"exist"<<endl;
            else
                cout<<"not exist"<<endl;
        }else if(command == "print"){
            cout<<ht<<endl;
        }
    }
    return 0;
}