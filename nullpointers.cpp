#include <iostream>

int main() {

    // Null value = a special value that means something has no value.
    //              When a pointer is holding a null value,
    //              that pointer is not pointing at anything (null pointer)

    // nullptr = keyword represents a null pointer literal

    // nullptrs are helpful when determining if an address
    // was successfully assigned to a pointer

    // when usingn pointers, be careful that your code isn't 
    // dereferencing (*) null or pointing to free memory
    // this will cause undefined behavior



        int *pointer = nullptr;
        int x = 123;

        pointer = &x;
        // *pointer; // undefined behavior

        if(pointer == nullptr){
            std::cout << "address was not assigned";
        }
        else{
            std::cout << "address was assigned";
            // std::cout << *pointer;
        }
    return 0;
}