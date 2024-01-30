#include <iostream>

namespace first{
    int x = 1;
}

namespace second{
    int x = 2;
}
int main() {


    std::cout << first::x;

    std::cout << second::x;

    using namespace first;
    std::cout << x; // would be used from the namespace created

    using std::string;
    using std::cout;

    // better alternatives to 
    using namespace std;


    // Namespace = provides a solution for preventing name conflicts
    //             in large projects. Each entity needs a unique name.
    //             A namespace allows for identically named entities
    //             as long as the namespaces are different.

    return 0;
}