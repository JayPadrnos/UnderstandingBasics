#include<iostream>

// This is a "Linear Search Algorithm"

int searchArray(int array[], int size, int element);

int main() {

    int numbers[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // comments will dictate change if they were strings foods[]
    int size = sizeof(numbers)/sizeof(numbers[0]);
    int index;
    int myNum; // your element that would change if you were using an array of strings (myFood)

    std::cout << "Enter element to search for: " << '\n';
    std::cin >> myNum; // this would be written as std::getline(std::cin, myFood)

    index = searchArray(numbers, size, myNum);

    if(index != -1){
        std::cout << myNum << " is at index " << index;
    }
    else{
        std::cout << myNum << "is not in the array";
    }

    return 0;
}

int searchArray(int array[], int size, int element){ // instead of int it would be std::string array[], int size, std::string element

    for(int i = 0; i < size; i++){
        if(array[i] == element){
            return i;
        }
    }
    return -1;
}