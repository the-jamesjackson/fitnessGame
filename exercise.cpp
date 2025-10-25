#include <iostream>
#include "cardio.h"
#include "strength-training.h"

using namespace std;

int getValidInt(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number." << endl;
        } else if (value < min || value > max) {
            cout << "Please enter a value between " << min << " and " << max << "." << endl;
        } else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

Exercise* createExercise() {
    cout << "\n--- LOG NEW EXERCISE ---" << endl;
    int exType = getValidInt("Choose type:\n1. Cardio\n2. Strength Training\nChoice: ", 1, 2);
    
    if (exType == 1) {
        // Cardio
        int distance = getValidInt("Enter distance (in miles): ", 1, 500);
        
        cout << "\nChoose cardio type:" << endl;
        cout << "1. Walking (5 pts/mile)" << endl;
        cout << "2. Running (15 pts/mile)" << endl;
        cout << "3. Cycling (10 pts/mile)" << endl;
        cout << "4. Swimming (20 pts/mile)" << endl;
        
        int cardioType = getValidInt("Choice: ", 1, 4);
        return createCardio(cardioType, distance);
        
    } else {
        // Strength Training
        int totalTime = getValidInt("Enter total session time (in minutes): ", 1, 300);
        int restTime = getValidInt("Enter average rest time between sets (in minutes): ", 0, totalTime);
        
        if (restTime >= totalTime) {
            cout << "Rest time must be less than total time!" << endl;
            return nullptr;
        }
        
        cout << "\nChoose strength type:" << endl;
        cout << "1. Calisthenics (10 pts/active min)" << endl;
        cout << "2. Weightlifting (12 pts/active min)" << endl;
        
        int strengthType = getValidInt("Choice: ", 1, 2);
        return createStrength(strengthType, totalTime, restTime);
    }
}