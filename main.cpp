#include <iostream>
#include "LargeInt.h"
using namespace std;

int main() {

//    cout << "please enter the large integer: ";
//    LargeInt largeInt;
//    cin >> largeInt;
//    cout << largeInt;

    LargeInt largeInt;
    LargeInt largeInt2;
    string numStr = "-778";
    string numStr2 = "778";
    largeInt = numStr;
    largeInt2 = numStr2;
    cout << largeInt << endl;
    cout << largeInt2 << endl;
    cout << (largeInt2 == largeInt) << endl;


    return 0;
}
