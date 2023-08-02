/* The following function takes in two integers 
and returns their product: */
#include <iostream> 
using namespace std;
int add(int a, int b) {
    return a + b; 
}
int multiply(int chicken, int burrito) {
    return chicken * burrito;
}

int main() {
    // calling the function
    int product = multiply(5, 7); /* '5' and '7' are arguments. 
    Note that we are setting the function to a variable! */

    int sum = add(10, 20);

    int solution = product - sum ;
    
    cout << "The solution is: "<< solution<< endl; 
    // printing the function to the screen

    return 0;
}