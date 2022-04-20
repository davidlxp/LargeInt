#include <iostream>
#include "LargeInt.h"
using namespace std;

int main() {

//    cout << "please enter the large integer: ";
//    LargeInt largeInt;
//    cin >> largeInt;
//    cin >> largeInt;
//    cout << largeInt;

    LargeInt largeInt;
    LargeInt largeInt2;
    string numStr = "12";
    string numStr2 = "8";
    largeInt = numStr;
    largeInt2 = numStr2;
    LargeInt largeIntX = largeInt + largeInt2;
    cout << largeIntX << endl;

//    LargeInt largeInt;
//    LargeInt largeInt2;
//    string numStr = "-8";
//    string numStr2 = "5";
//    largeInt = numStr;
//    largeInt2 = numStr2;
//    cout << largeInt << " < " << largeInt2 << " == " << (largeInt < largeInt2) << endl;

    return 0;
}
