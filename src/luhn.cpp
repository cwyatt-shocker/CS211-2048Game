/*
Luhn Checksum Validation
*/

#include <iostream>

using namespace std;

int main(){
    string cardNumber;
    cout << "Enter your card number: ";
    cin >> cardNumber;

    int sum = 0;
    bool doubleDigit = false;
    for (int i = cardNumber.length() - 1; i >= 0; --i) {
        int digit = cardNumber[i] - '0';
        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        doubleDigit = !doubleDigit;
    }

    if (sum % 10 == 0) {
        cout << "Card number is valid." << endl;
    } else {
        cout << "Card number is invalid." << endl;
    }
    
    return 0;
}