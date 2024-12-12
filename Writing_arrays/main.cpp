#include <iostream>
#include <cstring>
#include <fstream>

#define MAX_RECORDS 20

using namespace std;

struct Contact {
    char firstName[11];
    char lastName[21];
    char phoneNumber[13];
};

Contact phoneBook[MAX_RECORDS];
int recordCount = 0;

bool isUniquePhoneNumber(const char* phoneNumber) {
    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].phoneNumber, phoneNumber) == 0) {
            return false;
        }
    }
    return true;
}

void addContact() {
    if (recordCount >= MAX_RECORDS) {
        cout << "Phone book is full.\n";
        return;
    }

    Contact newContact;
    cout << "Enter first name: ";
    cin >> newContact.firstName;
    cout << "Enter last name: ";
    cin >> newContact.lastName;
    cout << "Enter phone number: ";
    cin >> newContact.phoneNumber;

    if (!isUniquePhoneNumber(newContact.phoneNumber)) {
        cout << "Phone number must be unique.\n";
        return;
    }

    phoneBook[recordCount++] = newContact;
    cout << "Contact added.\n";
}

void deleteContact() {
    char phoneNumber[13];
    cout << "Enter phone number to delete: ";
    cin >> phoneNumber;

    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].phoneNumber, phoneNumber) == 0) {
            for (int j = i; j < recordCount - 1; ++j) {
                phoneBook[j] = phoneBook[j + 1];
            }
            --recordCount;
            cout << "Contact deleted.\n";
            return;
        }
    }
    cout << "Phone number not found.\n";
}

void findContact() {
    char lastName[21];
    cout << "Enter last name to search: ";
    cin >> lastName;

    for (int i = 0; i < recordCount; ++i) {
        if (strcmp(phoneBook[i].lastName, lastName) == 0) {
            cout << "First name: " << phoneBook[i].firstName
                << ", Last name: " << phoneBook[i].lastName
                << ", Phone number: " << phoneBook[i].phoneNumber << "\n";
            return;
        }
    }
    cout << "Contact not found.\n";
}

void showAllContacts() {
    if (recordCount == 0) {
        cout << "Phone book is empty.\n";
        return;
    }

    for (int i = 0; i < recordCount; ++i) {
        cout << i + 1 << ". " << phoneBook[i].firstName << " "
            << phoneBook[i].lastName << " " << phoneBook[i].phoneNumber << "\n";
    }
}

void saveContactsToFile() {
    ofstream file("phone.dat", ios::binary);
    if (!file) {
        cout << "Error saving to file.\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    file.write(reinterpret_cast<char*>(phoneBook), sizeof(Contact) * recordCount);
    file.close();
    cout << "Contacts saved.\n";
}

void loadContactsFromFile() {
    ifstream file("phone.dat", ios::binary);
    if (!file) {
        cout << "Error loading from file.\n";
        return;
    }

    file.read(reinterpret_cast<char*>(&recordCount), sizeof(recordCount));
    file.read(reinterpret_cast<char*>(phoneBook), sizeof(Contact) * recordCount);
    file.close();
    cout << "Contacts loaded.\n";
}

int main() {
    int choice;
    do {
        cout << "\n1. Add contact\n2. Delete contact\n3. Find contact\n";
        cout << "4. Show all contacts\n5. Save contacts to file\n";
        cout << "6. Load contacts from file\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            findContact();
            break;
        case 4:
            showAllContacts();
            break;
        case 5:
            saveContactsToFile();
            break;
        case 6:
            loadContactsFromFile();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}
