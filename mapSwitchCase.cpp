//
// Created by archtao on 4/27/21.
//
#include <iostream>
#include <string>
#include <map>
using namespace std;

enum StringValue {
    stringValue0 = 1,
    stringValue1,
    stringValue2
};
static map<string, StringValue>mapSwitchCase;

static void InitializeMap()
{
    mapSwitchCase["000"] = stringValue0;
    mapSwitchCase["111"] = stringValue1;
    mapSwitchCase["222"] = stringValue2;
}

int main()
{
    string str;

    InitializeMap();
    cout << "------String MENU------" << endl
    << "111,222,000 to exit:";
    cin >> str;
    while (str != "000") {
        switch (mapSwitchCase[str]) {
            case stringValue0:
                cout << "You choose 000" << endl;
                return 0;
            case stringValue1:
                cout << "You choose 111" << endl;
                break;
            case stringValue2:
                cout << "You choose 222" << endl;
                break;
            default:
                cout << "You choose nothing." << endl;
                break;
        }
        cout << "Input string:";
        cin >> str;
    }

    return 0;
}

