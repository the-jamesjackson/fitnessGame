#include <iostream>
#include "user.h"
#include "exercise.h"

using namespace std;

void displayMainMenu(const string& username);
void manageStreak(User& u);

int main() {
    cout << "\n=======================================" << endl;
    cout << "       WELCOME TO FITNESS GAME!         " << endl;
    cout << "   Track exercises * Level up * Win!    " << endl;
    cout << "=======================================\n" << endl;
    
    int choice = getValidInt("1. New user\n2. Returning user\nChoice: ", 1, 2);
    
    string uname;
    cout << "\nEnter your username: ";
    getline(cin, uname);

    User u;
    u.setUsername(uname);

    if (choice == 2) {
        bool loaded = u.loadFile(uname + ".txt");
        if (loaded) {
            cout << "\nWelcome back, " << uname << "!" << endl;
        }
        else {
            cout << "\nCreated new profile for " << uname << "!" << endl;
        }
    } else {
        cout << "\nCreated new profile for " << uname << "!" << endl;
    }

    choice = 0;
    while (choice != 6) {
        displayMainMenu(uname);
        choice = getValidInt("Your choice: ", 1, 6);

        if (choice == 1) {
            // Log exercise
            Exercise* e = createExercise();
            if (e != nullptr) {
                u.logEx(e);
                cout << "\n✓ Exercise logged successfully!" << endl;
                cout << "You earned " << e->calcPoints() << " points!" << endl;
            } else {
                cout << "\n✗ Failed to log exercise." << endl;
            }
        } else if (choice == 2) {
            // View stats
            u.display();
            cout << "Press enter to continue...";
            cin.get();
        } else if (choice == 3) {
            // View detailed stats
            u.displayDetailedStats();
            cout << "Press enter to continue...";
            cin.get();
        } else if (choice == 4) {
            // View log
            u.printLog();
            cout << "Press enter to continue...";
            cin.get();
        } else if (choice == 5) {
            // Manage streak
            manageStreak(u);
        } else if (choice == 6) {
            // Logout
            cout << "\nLogging out..." << endl;
        }
    }

    char saveChoice = 'Y';
    cout << "\nSave your progress? (Y/N): ";
    cin >> saveChoice;
    
    if (saveChoice == 'Y' || saveChoice == 'y') {
        u.saveFile(uname + ".txt");
        cout << "Progress saved successfully!" << endl;
    } else {
        cout << "Progress not saved." << endl;
    }
    
    cout << "\n Thanks for playing! Keep exercising!" << endl;
    return 0;
}

void displayMainMenu(const string& username) {
    cout << "\n========================================" << endl;
    cout << "           FITNESS GAME MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. Log exercise" << endl;
    cout << "2. View stats for " << username << endl;
    cout << "3. View detailed stats" << endl;
    cout << "4. View exercise log" << endl;
    cout << "5. Manage streak" << endl;
    cout << "6. Logout & Save" << endl;
    cout << "========================================" << endl;
}

void manageStreak(User& u) {
    cout << "\n--- STREAK MANAGEMENT ---" << endl;
    cout << "Current streak: " << u.getStreak() << " session(s)" << endl;
    cout << "\n1. Increment streak (+1)" << endl;
    cout << "2. Reset streak to 1" << endl;
    cout << "3. Go back" << endl;
    
    int choice = getValidInt("Choice: ", 1, 3);
    
    if (choice == 1) {
        u.incrementStreak();
        cout << "Streak increased! New streak: " << u.getStreak() << endl;
    } else if (choice == 2) {
        u.resetStreak();
        cout << "Streak reset to 1." << endl;
    }
}