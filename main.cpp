#include "lib.hpp"
#include <iostream>
#include <exception>

int main() {
    unsigned sz, choice = 1;
    int key, value;

    std::cout << "How many entries do you wish to have?: ";
    std::cin >> sz;

    HashMap Numbers(sz);

    try {
        while(choice) {
            std::cout << '\n';
            std::cout << "0)Exit.\n";
            std::cout << "1)Print table.\n";
            std::cout << "2)Insert an element to the table.\n";
            std::cout << "3)Remove an element by it's key.\n";
            std::cout << "4)Remove an element by it's value.\n";
            std::cout << "5)Search for an element by it's key.\n";
            std::cout << "6)Search for an element by it's value.\n";
            std::cout << "7)Size of the current hash table.\n";

            std::cout << "Pick an option:\n";
            std::cin >> choice;
            std::cout << '\n';

            switch (choice) {
            case 0:
                return 0;
            case 1: {
                std::cout << Numbers;
                break;
            }
            case 2: {
                std::cout << "Key: ";
                std::cin >> key;
                std::cout << "Value: ";
                std::cin >> value;
                Numbers[key] = value;
                break;
            }
            case 3: {
                std::cout << "Key: ";
                std::cin >> key;
                Numbers.removeKey(key);
                break;
            }
            case 4: {
                std::cout << "Value: ";
                std::cin >> value;
                Numbers.removeValue(value);
                break;
            }
            case 5: {
                std::cout << "Key: ";
                std::cin >> key;
                std::cout << Numbers[key] << '\n';
                break;
            }
            case 6: {
                std::cout << Numbers.size() << '\n';
                break;
            }
            case 7: {
                std::cout << Numbers << '\n';
                break;
            }
            default:
                std::cout << "Invalid choice.\n";
                break;
            }
        }
    }
    catch (std::exception & e) {
        std::cout << "An error occured: " << e.what() << '\n';
    }

    return 0;
}


