#include<iostream>
using namespace std;
int main(){
    string first_name, last_name, nick_name;

    cout<<"Enter your first name : ";
    getline (cin, first_name) ;
    cout<<"Enter your last name : ";
    getline (cin, last_name) ;
    cout<<"Enter your nickname :";
    getline (cin, nick_name) ;

     cout<<"Your Full Name is "<<first_name<<" "<<last_name<< " Your nickname is " <<nick_name ;
    // cout<<first_name+last_name+nick_name<<" That is a wonderful name" ;
    return 0;
}