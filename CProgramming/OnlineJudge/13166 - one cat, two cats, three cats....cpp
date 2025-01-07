#include<iostream>
#include<string>
#include<cmath>
#include "function.h"
//#include "13166.h"

using namespace std;

int len = 0;

big_number::big_number(string num){
    this->num = num;
    len = this->num.size();
}
bool big_number::multiple_of_two(){
    if((this->num[len-1] - '0') % 2 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_three(){
    int sum = 0;
    for(int i = 0 ; i < len ; i++) sum += (this->num[i] - '0');
    if(sum % 3 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_four(){
    int sum = 10 * (this->num[len-2] - '0') + (this->num[len-1] - '0');
    if(sum % 4 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_five(){
    if((this->num[len-1] - '0') % 5 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_six(){
    if(this->big_number::multiple_of_two() && this->big_number::multiple_of_three()) return 1;
    else return 0;
}
bool big_number::multiple_of_eight(){
    int sum = 100 * (this->num[len-3] - '0') + 10 * (this->num[len-2] - '0') + (this->num[len-1] - '0');
    if(sum % 8 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_nine(){
    int sum = 0;
    for(int i = 0 ; i < len ; i++) sum += (this->num[i] - '0');
    if(sum % 9 == 0) return 1;
    else return 0;
}
bool big_number::multiple_of_ten(){
    if(this->num[len-1] == '0') return 1;
    else return 0;
}
bool big_number::multiple_of_eleven(){
    int sum = 0;
    for(int i = 0 ; i < len ; i++){
        if(i % 2 == 0) sum += (this->num[i] - '0');
        else sum -= (this->num[i] - '0');
    }
    if(sum % 11 == 0) return 1;
    else return 0;
}