#include <iostream>
#include "LargeInt.h"
using namespace std;

int main() {

//    cout << "please enter the large integer: ";
//    LargeInt largeInt;
//    cin >> largeInt;
//    cin >> largeInt;
//    cout << largeInt;

//    LargeInt largeInt;
//    LargeInt largeInt2;
//    string numStr = "20";
//    string numStr2 = "7989";
//    largeInt = numStr;
//    largeInt = numStr2;
//    cout << largeInt << endl;

    LargeInt largeInt;
    LargeInt largeInt2;
    string numStr = "-9";
    string numStr2 = "7";
    largeInt = numStr;
    largeInt2 = numStr2;
    cout << (largeInt < largeInt2) << endl;


    return 0;
}
