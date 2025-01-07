#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    string name, school;
    cin >> n;
    
    set<pair<string, string>> data;
    data.insert(make_pair("Wa", "Waninoko"));
    data.insert(make_pair("Mi", "Milotic"));
    data.insert(make_pair("Ma", "Magikarp"));
    data.insert(make_pair("Va", "Vaporeon"));
    data.insert(make_pair("Sh", "Sharpedo"));
    data.insert(make_pair("Tapu", "Tapu Fini"));
    data.insert(make_pair("Em", "Empoleon"));
    data.insert(make_pair("La", "Lapras"));
    data.insert(make_pair("Pi", "Pikachu"));
    data.insert(make_pair("Pe", "Pikachu"));
    data.insert(make_pair("Me", "Mega Gyarados"));

    while(n--){
        cin >> name >> school;
        string sub = name.substr(0,2);  //substr(pos num)
        if(sub == "Ta") sub = name.substr(0,4);
        for(auto PAIR : data){
            if(sub == PAIR.first){
                cout << name << " the " << school << " " << PAIR.second << endl;
                break;
            }
            if(PAIR == *data.rbegin()){
                cout << name << " is looking for a Chinese tutor, too!" << endl;
            }
        }
    }
}