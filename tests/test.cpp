#include <iostream>
using std::cout;
using std::endl;

bool init() {
    static bool isInit{false};
    if (!isInit) {
        cout << "Es wird nun initialisiert!" << endl;
        isInit = true;
    }
    else {
        cout << "Es wurde bereits initialisiert!" << endl;    
    }
    return isInit;
}

int main() {
    bool isInit{init()};
    std::cout << "isInit now has the value " << isInit << endl;
    isInit = init();
    std::cout << "isInit now has the value " << isInit << endl;
}