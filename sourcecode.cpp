#include <iostream>
#include <string>
#include <fstream>
using namespace std;

const int MAX_PATIENTS = 100;

struct Patient {
    int id;
    string name;
    int age;
    string disease;
    string contact;
};

void clearScreen() {
    system("cls"); // For Windows
    // system("clear"); // For Linux/Mac
}

void addPatient(Patient patients[], int& count) {
    if (count >= MAX_PATIENTS) {
        cout << "No space to add more patients.\n";
        return;
    }

    cout << "\nEnter Patient Details:\n";

    // ID input with check for duplicates
    bool idExists;
    do {
        idExists = false;
        cout << "ID: ";
        cin >> patients[count].id;

        for (int i = 0; i < count; i++) {
            if (patients[i].id == patients[count].id) {
                cout << "ID already exists. Please enter a unique ID.\n";
                idExists = true;
                break;
            }
        }
    } while (idExists);

    cin.ignore(); // Clear the input buffer
    cout << "Name: ";
    getline(cin, patients[count].name);

    // Age validation
    do {
        cout << "Age: ";
        cin >> patients[count].age;
        if (patients[count].age <= 0) {
            cout << "Age must be positive. Please try again.\n";
        }
    } while (patients[count].age <= 0);

    cin.ignore();
    cout << "Disease: ";
    getline(cin, patients[count].disease);

    cout << "Contact: ";
    getline(cin, patients[count].contact);

    count++;
    cout << "Patient added successfully!\n";
}

void displayPatients(Patient patients[], int count) {
    if (count == 0) {
        cout << "No patients in the list.\n";
        return;
    }

    cout << "\n--- Patient Details ---\n";
    for (int i = 0; i < count; i++) {
        cout << "ID: " << patients[i].id << "\n";
        cout << "Name: " << patients[i].name << "\n";
        cout << "Age: " << patients[i].age << "\n";
        cout << "Disease: " << patients[i].disease << "\n";
        cout << "Contact: " << patients[i].contact << "\n";
        cout << "----------------------\n";
    }
}

void updatePatient(Patient patients[], int count) {
    if (count == 0) {
        cout << "No patients to update.\n";
        return;
    }

    int id;
    cout << "\nEnter Patient ID to update: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            cout << "\nCurrent Details:\n";
            cout << "1. Name: " << patients[i].name << "\n";
            cout << "2. Age: " << patients[i].age << "\n";
            cout << "3. Disease: " << patients[i].disease << "\n";
            cout << "4. Contact: " << patients[i].contact << "\n";

            int choice;
            cout << "\nEnter field number to update (1-4): ";
            cin >> choice;
            cin.ignore();

            switch (choice) {
            case 1:
                cout << "New Name: ";
                getline(cin, patients[i].name);
                break;
            case 2:
                do {
                    cout << "New Age: ";
                    cin >> patients[i].age;
                } while (patients[i].age <= 0);
                break;
            case 3:
                cout << "New Disease: ";
                getline(cin, patients[i].disease);
                break;
            case 4:
                cout << "New Contact: ";
                getline(cin, patients[i].contact);
                break;
            default:
                cout << "Invalid choice.\n";
                return;
            }

            cout << "Patient details updated successfully!\n";
            return;
        }
    }

    cout << "Patient with ID " << id << " not found.\n";
}

void removePatient(Patient patients[], int& count) {
    if (count == 0) {
        cout << "No patients to remove.\n";
        return;
    }

    int id;
    cout << "\nEnter Patient ID to remove: ";
    cin >> id;

    for (int i = 0; i < count; i++) {
        if (patients[i].id == id) {
            for (int j = i; j < count - 1; j++) {
                patients[j] = patients[j + 1];
            }
            count--;
            cout << "Patient removed successfully!\n";
            return;
        }
    }

    cout << "Patient with ID " << id << " not found.\n";
}

void searchPatient(Patient patients[], int count) {
    if (count == 0) {
        cout << "No patients in the system.\n";
        return;
    }

    string searchTerm;
    cout << "Enter name or ID to search: ";
    cin >> searchTerm;

    bool found = false;
    for (int i = 0; i < count; i++) {
        if (to_string(patients[i].id) == searchTerm ||
            patients[i].name.find(searchTerm) != string::npos) {

            if (!found) {
                cout << "\nSearch Results:\n";
                found = true;
            }

            cout << "ID: " << patients[i].id << "\n";
            cout << "Name: " << patients[i].name << "\n";
            cout << "Age: " << patients[i].age << "\n";
            cout << "Disease: " << patients[i].disease << "\n";
            cout << "Contact: " << patients[i].contact << "\n";
            cout << "----------------------\n";
        }
    }

    if (!found) {
        cout << "No matching patients found.\n";
    }
}

void saveToFile(Patient patients[], int count) {
    ofstream file("patients.dat");
    if (!file) {
        cout << "Error saving data.\n";
        return;
    }

    for (int i = 0; i < count; i++) {
        file << patients[i].id << '\n'
            << patients[i].name << '\n'
            << patients[i].age << '\n'
            << patients[i].disease << '\n'
            << patients[i].contact << '\n';
    }

    cout << "Patient data saved to file successfully!\n";
}

void loadFromFile(Patient patients[], int& count) {
    ifstream file("patients.dat");
    if (!file) {
        cout << "No existing patient data found.\n";
        return;
    }

    count = 0;
    while (file >> patients[count].id) {
        file.ignore();
        getline(file, patients[count].name);
        file >> patients[count].age;
        file.ignore();
        getline(file, patients[count].disease);
        getline(file, patients[count].contact);
        count++;
    }

    cout << "Patient data loaded from file successfully!\n";
}

int main() {
    Patient patients[MAX_PATIENTS];
    int patientCount = 0;
    loadFromFile(patients, patientCount);

    int choice;
    do {
        clearScreen();
        cout << "\n--- Hospital Management System ---\n";
        cout << "1. Add New Patient\n";
        cout << "2. Display All Patients\n";
        cout << "3. Update Patient Details\n";
        cout << "4. Remove Patient\n";
        cout << "5. Search Patient\n";
        cout << "6. Save Data to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addPatient(patients, patientCount); break;
        case 2: displayPatients(patients, patientCount); break;
        case 3: updatePatient(patients, patientCount); break;
        case 4: removePatient(patients, patientCount); break;
        case 5: searchPatient(patients, patientCount); break;
        case 6: saveToFile(patients, patientCount); break;
        case 7:
            saveToFile(patients, patientCount);
            cout << "\n*********************** Thank you! **********************\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    } while (choice != 7);

    return 0;
}