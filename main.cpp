#include <iostream>
#include "LargeInt.h"
using namespace std;

int main() {

//    cout << "please enter the 1st large integer: ";
//    LargeInt largeInt;
//    cin >> largeInt;
//    cout << "please enter the 2nd large integer: ";
//    LargeInt largeInt2;
//    cin >> largeInt2;
//    LargeInt largeIntX = largeInt - largeInt2;
//    cout << largeIntX;

    LargeInt x;
    x = -1;
    LargeInt largeInt("-10");
    LargeInt largeInt2("2");
    LargeInt largeIntX = largeInt % x;
    cout << largeIntX << endl;
    cout << (largeInt != x) << endl;

//    LargeInt largeInt;
//    LargeInt largeInt2;
//    string numStr = "-8";
//    string numStr2 = "5";
//    largeInt = numStr;
//    largeInt2 = numStr2;
//    cout << largeInt << " != " << largeInt2 << " == " << (largeInt != largeInt2) << endl;




    return 0;
}
