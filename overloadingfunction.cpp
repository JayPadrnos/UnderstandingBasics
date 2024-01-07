#include <iostream>

void bakePizza();
void bakePizza(std::string topping1);
void bakePizza(std::string topping1, std::string topping2);

// each functions signature needs to be unique

int main() {

    bakePizza();

    bakePizza("pepperoni");
    
    bakePizza("pepperoni", "jalapeno");

    // because you have setup different functions that allow for more stings or toppings to take the place for the parameters of the function you are able
    // to type in different toppings and have the bakePizza() allow for fill ins on the function

    return 0;
}

void bakePizza(){
    std::cout << "Here is your pizza!\n";
}

// It is valid for functions to share the same name but you need a different set of parameters
// A function name plus its parameters is known as a function signature"

void bakePizza(std::string topping1){
    std::cout << "Here is your " << topping1 << " pizza!\n";
}

void bakePizza(std::string topping1, std::string topping2){
    std::cout << "Here is your " << topping1 << " and " <<  topping2 << " pizza!\n";
}