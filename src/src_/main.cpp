#include <iostream>
#include "../include/StreamingService.h"

#include <string>

using namespace std;

int main() {
    string userAnswer = " ";

    while (true) {

        cout << "Welcome to the Streaming Service Content Rating App!!!" << endl;
        cout << "--Type anything to enter the streaming service rating App" << endl;
        cout << "--Type 1 to exit the program" << endl;
        cin >> userAnswer;

        if(userAnswer == "1") break;

        StreamingService App = StreamingService();

        App.initApp();

    }
    cout << "We appreciate your reviews, come back soon!!!" << endl;

    return 0;
}