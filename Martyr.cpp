#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
#include "Martyr.h"
#include"MartyrsDataStructure.h"

int main() {
    MartyrsDataStructure martyrsData;

    std::cout << "Welcome to the Martyrs Management System!\n";
    martyrsData.readDataFromFile("btselem1.csv");

    int choice;
    do {
        std::cout << "\nMain Menu:\n";
        std::cout << "1. Location Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            martyrsData.handleLocationsMenu();
            break;
        case 0:
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}