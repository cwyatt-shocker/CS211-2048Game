/*
Luhn Checksum Validation
*/

#include <iostream>
#include <cstddef>
#include <cstring>

const std::size_t CARD_LENGTH = 16;
const std::size_t BUFFER_SIZE = 256;

enum FormatResult {
    FORMAT_OK,
    FORMAT_EMPTY,
    FORMAT_INTERNAL_SPACE,
    FORMAT_NON_DIGIT,
    FORMAT_WRONG_LENGTH
};


bool isSpaceChar(char c) {
    return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

bool isDigitChar(char c) {
    return c >= '0' && c <= '9';
}


int transformDigit(int digit, bool doubled) {
    if (!doubled) return digit;
    int value = digit * 2;
    if (value > 9) value -= 9;
    return value;
}

void toDigits(const char* text, int digits[], std::size_t length) {
    for (std::size_t i = 0; i < length; i++) {
        digits[i] = text[i] - '0';
    }
}


FormatResult validateFormat(const char* text, std::size_t length) {
    if (length == 0) return FORMAT_EMPTY;

    bool hasSpace = false;
    bool hasNonDigit = false;
    for (std::size_t i = 0; i < length; i++) {
        if (isSpaceChar(text[i])) {
            hasSpace = true;
        } else if (!isDigitChar(text[i])) {
            hasNonDigit = true;
        }
    }

    if (hasSpace) return FORMAT_INTERNAL_SPACE;
    if (hasNonDigit) return FORMAT_NON_DIGIT;
    if (length != CARD_LENGTH) return FORMAT_WRONG_LENGTH;
    return FORMAT_OK;
}

void printFormatError(FormatResult result) {
    switch (result) {
        case FORMAT_EMPTY:
            std::cout << "Input error: nothing was entered.\n";
            break;
        case FORMAT_INTERNAL_SPACE:
            std::cout << "Input error: the number must not contain spaces.\n";
            break;
        case FORMAT_NON_DIGIT:
            std::cout << "Input error: only the digits 0-9 are allowed "
                         "(no letters or punctuation).\n";
            break;
        case FORMAT_WRONG_LENGTH:
            std::cout << "Input error: the number must be exactly "
                      << CARD_LENGTH << " digits long.\n";
            break;
        default:
            break;
    }
}


bool checkLuhn(const int digits[], std::size_t length, int* sumOut = nullptr) {
    int sum = 0;
    bool doubled = false;

    for (std::size_t i = length; i-- > 0;) {
        sum += transformDigit(digits[i], doubled);
        doubled = !doubled;
    }

    if (sumOut != nullptr) *sumOut = sum;
    return sum % 10 == 0;
}


int main() {
    char buffer[BUFFER_SIZE];

    std::cout << "Luhn checksum validator\n";
    std::cout << "Note: a passing checksum does not prove a card exists "
                 "or is authorized for payment.\n";

    while (true) {
        std::cout << "\nEnter a " << CARD_LENGTH
                  << "-digit number (or Q to quit): ";

        std::cin.getline(buffer, BUFFER_SIZE);

        if (std::cin.eof() && std::cin.gcount() == 0) {
            std::cout << "\nEnd of input. Goodbye.\n";
            break;
        }

        if (std::cin.fail() && !std::cin.eof()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Input error: the number must be exactly "
                      << CARD_LENGTH << " digits long.\n";
            continue;
        }

        std::size_t start = 0;
        std::size_t end = std::strlen(buffer);
        while (start < end && isSpaceChar(buffer[start])) start++;
        while (end > start && isSpaceChar(buffer[end - 1])) end--;
        std::size_t length = end - start;
        const char* text = buffer + start;

        if (length == 1 && (text[0] == 'q' || text[0] == 'Q')) {
            std::cout << "Goodbye.\n";
            break;
        }

        FormatResult format = validateFormat(text, length);
        if (format != FORMAT_OK) {
            printFormatError(format);
            continue;
        }

        int digits[CARD_LENGTH];
        toDigits(text, digits, CARD_LENGTH);

        int sum = 0;
        if (checkLuhn(digits, CARD_LENGTH, &sum)) {
            std::cout << "Correct format. Checksum PASSES" << std::endl;
        } else {
            std::cout << "Correct format. Checksum FAILS" << std::endl;
        }
    }

    return 0;
}