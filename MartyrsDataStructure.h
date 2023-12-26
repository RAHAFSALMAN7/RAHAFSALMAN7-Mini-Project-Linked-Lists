#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>
 


class MartyrsDataStructure {
private:
    Node* head;

public:
    MartyrsDataStructure() : head(nullptr) {}

    void insertLocation(const std::string& locName) {
        Node* newNode = new Node(locName);
        if (!head) {
            head = newNode;
            head->next = head;
            head->prev = head;
        }
        else {
            Node* lastNode = head->prev;
            lastNode->next = newNode;
            newNode->prev = lastNode;
            newNode->next = head;
            head->prev = newNode;
        }
    }
    void updateLocation(const std::string& locName) {
        Node* locationNode = searchLocation(locName);
        if (locationNode) {
            std::string newLocName;
            std::cout << "Enter the new name for the location: ";
            std::cin >> newLocName;

            locationNode->data.locationName = newLocName;

            std::cout << "Location updated.\n";
        }
        else {
            std::cout << "Location not found.\n";
        }
    }

    void deleteLocation(const std::string& locName) {
        Node* locationNode = searchLocation(locName);
        if (locationNode) {
            if (locationNode->prev) {
                locationNode->prev->next = locationNode->next;
                locationNode->next->prev = locationNode->prev;
                if (head == locationNode) {
                    head = locationNode->next;
                }
            }
            else {
                // Handle the case where the node to be deleted is the head
                head = locationNode->next;
                if (head == locationNode) {
                    head = nullptr; // List becomes empty
                }
            }

            delete locationNode; // Free memory

            std::cout << "Location deleted.\n";
        }
        else {
            std::cout << "Location not found.\n";
        }
    }

    void readDataFromFile(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            std::cerr << "Error opening file " << fileName << std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::vector<std::string> tokens;
            std::string token;
            while (std::getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            if (tokens.size() == 5) {
                Martyr newMartyr(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
                Node* locationNode = searchLocation(tokens[2]);
                if (locationNode) {
                    locationNode->data.martyrsByName.push_back(newMartyr);
                    locationNode->data.martyrsByDate.push_back(newMartyr);
                }
                else {
                    insertLocation(tokens[2]);
                    Node* newLocation = searchLocation(tokens[2]);
                    newLocation->data.martyrsByName.push_back(newMartyr);
                    newLocation->data.martyrsByDate.push_back(newMartyr);
                }
            }
        }
        file.close();
    }

    void displayLocations() {
        if (!head) {
            std::cout << "No locations found." << std::endl;
            return;
        }

        Node* current = head;
        do {
            std::cout << "Location: " << current->data.locationName << std::endl;
            current = current->next;
        } while (current != head);
    }

    Node* searchLocation(const std::string& locName) {
        if (!head) {
            return nullptr;
        }

        Node* current = head;
        do {
            if (current->data.locationName == locName) {
                return current;
            }
            current = current->next;
        } while (current != head);

        return nullptr;
    }

    void handleLocationsMenu() {
        int choice = -1;
        std::string locName;

        do {
            std::cout << "\nLocation Menu:\n";
            std::cout << "1. Insert new location record\n";
            std::cout << "2. Update an existing location\n";
            std::cout << "3. Delete an existing location\n";
            std::cout << "4. Search for a location record\n";
            std::cout << "0. Exit\n";
            std::cout << "Enter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                std::cout << "Enter location name: ";
                std::cin >> locName;
                insertLocation(locName);
                std::cout << "Location record inserted.\n";
                break;
            case 2:
                std::cout << "Enter the name of the location to update: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, locName);
                updateLocation(locName);
                break;
            case 3:
                std::cout << "Enter the name of the location to delete: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, locName);
                deleteLocation(locName);
                break;
            case 4:
                std::cout << "Enter the name of the location: ";
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::getline(std::cin, locName);
                searchAndPrintLocation(locName);
                break;
            case 0:
                std::cout << "Exiting the Location Menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }

    void searchAndPrintLocation(const std::string& locName) {
        Node* selectedLocation = searchLocation(locName);
        if (selectedLocation) {
            std::cout << "Location found: " << selectedLocation->data.locationName << std::endl;

            char martyrsMenuChoice;
            do {
                std::cout << "\na. Martyrs  Menu\n";
                std::cout << "b. Statistics Report\n";
                std::cout << "Enter your choice: ";
                std::cin >> martyrsMenuChoice;

                switch (martyrsMenuChoice) {
                case 'a':
                    handleMartyrsMenu(selectedLocation);
                    break;
                case 'b':
                    generateAndDisplayStatistics(selectedLocation);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            } while (martyrsMenuChoice != 'a' && martyrsMenuChoice != 'b');
        }
        else {
            std::cout << "Location not found.\n";
        }
    }

    void handleMartyrsMenu(Node* selectedLocation) {
        int martyrChoice = -1;
        do {
            std::cout << "\nMartyrs Menu:\n";
            std::cout << "1. Insert a new martyr record\n";
            std::cout << "2. Update a martyr record\n";
            std::cout << "3. Delete a martyr record\n";
            std::cout << "4. Search for a martyr by name\n";
            std::cout << "0. Back to Location Menu\n";
            std::cout << "Enter your choice: ";
            std::cin >> martyrChoice;

            switch (martyrChoice) {
            case 1:
                insertMartyrRecord(selectedLocation);
                break;
            case 2:
                updateMartyrRecord(selectedLocation);
                break;
            case 3:
                deleteMartyrRecord(selectedLocation);
                break;
            case 4:
                searchMartyrByName(selectedLocation);
                break;
            case 0:
                std::cout << "Back to Location Menu.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            }
        } while (martyrChoice != 0);
    }

    void insertMartyrRecord(Node* selectedLocation) {
        std::string martyrName, martyrAge, martyrDate, martyrGender;

        std::cout << "Enter martyr's name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, martyrName);
        std::cout << "Enter martyr's age: ";
        std::cin >> martyrAge;
        std::cout << "Enter martyr's date of death: ";
        std::cin >> martyrDate;
        std::cout << "Enter martyr's gender: ";
        std::cin >> martyrGender;

        Martyr newMartyr(martyrName, martyrAge, selectedLocation->data.locationName, martyrDate, martyrGender);
        selectedLocation->data.martyrsByName.push_back(newMartyr);
        selectedLocation->data.martyrsByDate.push_back(newMartyr);

        std::cout << "Martyr record inserted.\n";
    }
    void deleteMartyrRecord(Node* selectedLocation) {
        std::string martyrName;
        std::cout << "Enter the name of the martyr to delete: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, martyrName);

        auto& martyrsByName = selectedLocation->data.martyrsByName;
        auto it = std::find_if(martyrsByName.begin(), martyrsByName.end(),
            [&martyrName](const Martyr& martyr) { return martyr.name == martyrName; });

        if (it != martyrsByName.end()) {
            // Implement the delete logic for the martyr
            // You can delete the martyr from the vector here
            martyrsByName.erase(it);
            std::cout << "Martyr record deleted.\n";
        }
        else {
            std::cout << "Martyr not found.\n";
        }
    }

    void updateMartyrRecord(Node* selectedLocation) {
        std::string martyrName;
        std::cout << "Enter the name of the martyr to update: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, martyrName);

        auto& martyrsByName = selectedLocation->data.martyrsByName;
        auto it = std::find_if(martyrsByName.begin(), martyrsByName.end(),
            [&martyrName](const Martyr& martyr) { return martyr.name == martyrName; });

        if (it != martyrsByName.end()) {
            // Implement the update logic for the martyr
            // You can modify the martyr's properties here
            std::cout << "Enter the new age for the martyr: ";
            std::cin >> it->age;
            std::cout << "Enter the new event location for the martyr: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, it->eventLocation);
            std::cout << "Enter the new date of death for the martyr: ";
            std::cin >> it->dateOfDeath;
            std::cout << "Enter the new gender for the martyr: ";
            std::cin >> it->gender;

            std::cout << "Martyr record updated.\n";
        }
        else {
            std::cout << "Martyr not found.\n";
        }
    }


    void searchMartyrByName(Node* selectedLocation) {
        std::string martyrName;
        std::cout << "Enter the name of the martyr to search: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, martyrName);

        auto& martyrsByName = selectedLocation->data.martyrsByName;
        auto it = std::find_if(martyrsByName.begin(), martyrsByName.end(),
            [&martyrName](const Martyr& martyr) { return martyr.name == martyrName; });

        if (it != martyrsByName.end()) {
            // Implement the display logic for the found martyr
            std::cout << "Martyr found:\n";
            std::cout << "Name: " << it->name << ", Age: " << it->age << ", Event Location: "
                << it->eventLocation << ", Date of Death: " << it->dateOfDeath << ", Gender: "
                << it->gender << "\n";
        }
        else {
            std::cout << "Martyr not found.\n";
        }
    }


    void generateAndDisplayStatistics(Node* selectedLocation) {
        std::cout << "\nStatistics Report for " << selectedLocation->data.locationName << ":\n";
        std::cout << "a. The number of martyrs in the selected location: " << selectedLocation->data.martyrsByName.size() << "\n";
        std::cout << "b. Martyrs' full information:\n";
        printMartyrsInformation(selectedLocation->data.martyrsByName);

        // Sort martyrsByDate in descending order based on the date of death
        std::sort(selectedLocation->data.martyrsByDate.rbegin(), selectedLocation->data.martyrsByDate.rend(),
            [](const Martyr& a, const Martyr& b) {
                return a.dateOfDeath > b.dateOfDeath;
            });

        std::cout << "c. Martyrs' full information (Latest to Earliest):\n";
        printMartyrsInformation(selectedLocation->data.martyrsByDate);

        std::cout << "d. Date with the minimum number of martyrs: " << findDateWithMinimumMartyrs(selectedLocation) << "\n";

        char saveChoice;
        std::cout << "\nDo you want to save the changes to the file?\n";
        std::cout << "a. Yes\n";
        std::cout << "b. No\n";
        std::cout << "Enter your choice: ";
        std::cin >> saveChoice;

        if (saveChoice == 'a') {
            saveChangesToFile();
        }

        std::cout << "Exiting the program.\n";
    }


    void printMartyrsInformation(const std::vector<Martyr>& martyrs) {
        for (const auto& martyr : martyrs) {
            std::cout << "Name: " << martyr.name << ", Age: " << martyr.age << ", Event Location: "
                << martyr.eventLocation << ", Date of Death: " << martyr.dateOfDeath << ", Gender: "
                << martyr.gender << "\n";
        }
    }
    void printMartyrsInformationReverse(const std::vector<Martyr>& martyrs) {
        // Create a copy of martyrs to avoid modifying the original vector
        std::vector<Martyr> sortedMartyrs = martyrs;

        // Sort the martyrs in reverse order (latest to earliest)
        std::sort(sortedMartyrs.rbegin(), sortedMartyrs.rend(),
            [](const Martyr& a, const Martyr& b) {
                // Convert date strings to a format suitable for comparison
                std::tm tmA = {};
                std::tm tmB = {};
                std::istringstream ssA(a.dateOfDeath);
                std::istringstream ssB(b.dateOfDeath);
                ssA >> std::get_time(&tmA, "%d-%m-%Y");
                ssB >> std::get_time(&tmB, "%d-%m-%Y");

                // Compare the dates
                return std::mktime(&tmA) > std::mktime(&tmB);
            });

        // Print the sorted martyrs
        for (const auto& martyr : sortedMartyrs) {
            std::cout << "Name: " << martyr.name << ", Age: " << martyr.age << ", Event Location: "
                << martyr.eventLocation << ", Date of Death: " << martyr.dateOfDeath << ", Gender: "
                << martyr.gender << "\n";
        }
    }

    std::string findDateWithMinimumMartyrs(Node* selectedLocation) {
        std::string minDate;
        size_t minMartyrs = std::numeric_limits<size_t>::max();

        for (const auto& martyr : selectedLocation->data.martyrsByDate) {
            size_t numMartyrsOnDate = std::count_if(
                selectedLocation->data.martyrsByDate.begin(),
                selectedLocation->data.martyrsByDate.end(),
                [&martyr](const Martyr& m) { return m.dateOfDeath == martyr.dateOfDeath; }
            );

            if (numMartyrsOnDate < minMartyrs) {
                minMartyrs = numMartyrsOnDate;
                minDate = martyr.dateOfDeath;
            }
        }

        return minDate;
    }

    void saveChangesToFile() {
        std::string folderPath, fileName;

        std::cout << "Enter the folder path to save the file: ";
        std::cin >> folderPath;
        std::cout << "Enter the file name: ";
        std::cin >> fileName;

        std::ofstream outputFile(folderPath + "\\" + fileName);
        if (!outputFile.is_open()) {
            std::cerr << "Error opening file for writing.\n";
            return;
        }

        // Save the updated data structures back to the file
        Node* current = head;
        do {
            for (const auto& martyr : current->data.martyrsByName) {
                outputFile << martyr.name << "," << martyr.age << ","
                    << martyr.eventLocation << "," << martyr.dateOfDeath << "," << martyr.gender << "\n";
            }
            current = current->next;
        } while (current != head);

        outputFile.close();
        std::cout << "Changes saved successfully.\n";
    }

    ~MartyrsDataStructure() {
        // Destructor to free allocated memory
        if (head) {
            Node* current = head;
            Node* nextNode;
            do {
                nextNode = current->next;
                delete current;
                current = nextNode;
            } while (current != head);
        }
    }
};
