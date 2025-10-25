#include <iostream>
#include <iomanip>
#include <sstream>
#include "user.h"

using namespace std;

User::User() : lvl_(1), totPoints_(0), totDistance_(0), numSessions_(0), streak_(0), basePoints_(100) {}

User::~User() {
    for (Exercise* e : log_) {
        delete e;
    }
}

void User::display() const {
    cout << "\n========================================" << endl;
    cout << "       STATS FOR: " << username_ << endl;
    cout << "========================================" << endl;

    int currentLevelPoints = totPoints_ % pointsRequired();
    int needed = pointsRequired();
    int barWidth = 30;
    int progress = (currentLevelPoints * barWidth) / needed;

    cout << "Progress: [";
    for (int i = 0; i < barWidth; i++) {
        if (i < progress) cout << "=";
        else cout << "-";
    }
    cout << "]" << (currentLevelPoints * 100 / needed) << "%" << endl;
    cout << "Points to Level " << (lvl_ + 1) << ": " << (needed - currentLevelPoints) << endl;

    cout << "\nCurrent Streak: " << streak_ << " session(s)" << endl;
    cout << "Total Sessions: " << numSessions_ << endl;
    cout << "Total Distance: " << totDistance_ << " miles" << endl;
    cout << "========================================\n" << endl;
}

void User::displayDetailedStats() const {
    display();
    
    if (numSessions_ == 0) {
        cout << "No exercises logged yet!" << endl << endl;
        return;
    }
    
    cout << "DETAILED STATISTICS:" << endl;
    cout << "Average points per session: " << (totPoints_ / numSessions_) << endl;
    
    int cardioCount = 0, strengthCount = 0;
    for (const Exercise* e : log_) {
        string type = e->getType();
        if (type == "Walking" || type == "Running" || 
            type == "Cycling" || type == "Swimming") {
            cardioCount++;
        } else {
            strengthCount++;
        }
    }
    
    cout << "Cardio sessions: " << cardioCount << endl;
    cout << "Strength sessions: " << strengthCount << endl;
    cout << endl;
}

void User::setUsername(const string& name){
    username_ = name;
}

void User::logEx(Exercise* e){
    log_.push_back(e);
    totPoints_ += e->calcPoints();
    numSessions_++;

    string type = e->getType();
    if(type == "Walking" || type == "Running" || type == "Cycling" || type == "Swimming"){
        totDistance_ += stoi(e->getData());
    }

    lvlUp();
}

void User::printLog() const {
    if (log_.empty()) {
        cout << "Exercise log is empty" << endl << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "       EXERCISE LOG (Most Recent First)" << endl;
    cout << "========================================" << endl;

    for (int i = log_.size() - 1; i >= 0; i--) {
        string type = log_[i]->getType();
        string data = log_[i]->getData();
        
        cout << (log_.size() - i) << ". " << type << " - ";
        
        if (type == "Walking" || type == "Running" || 
            type == "Cycling" || type == "Swimming") {
            cout << data << " miles";
        } else if (type == "Calisthenics" || type == "Weightlifting") {
            cout << data << " minutes (total/rest)";
        } else {
            cout << data;
        }
        
        cout << " (+" << log_[i]->calcPoints() << " pts)" << endl;
    }
    cout << "========================================\n" << endl;
}

int User::pointsRequired() const{
    return basePoints_ * lvl_;
}

bool User::hasLvlUp(){
    return totPoints_ >= lvl_ * pointsRequired();
}

void User::lvlUp(){
    while(hasLvlUp()){
        lvl_++;
        cout << "LEVEL UP! You are now level " << lvl_ << "!" << endl;
    }
}

bool User::loadFile(const string& filename) {
    ifstream ifile(filename);
    if (!ifile.is_open()) {
        cout << "No save file found. Starting fresh!" << endl;
        return false;
    }

    getline(ifile, username_);
    ifile >> lvl_;
    ifile >> totPoints_;
    ifile >> totDistance_;
    ifile >> numSessions_;
    ifile >> streak_;
    
    int logSize;
    ifile >> logSize;
    ifile.ignore();

    for (int i = 0; i < logSize; i++) {
        Exercise* e = nullptr;
        string line;
        getline(ifile, line);

        if (line.find("EXERCISE") == 0) {
            stringstream ss(line);
            string eLine, type;
            ss >> eLine >> type;

            if (type == "Walking" || type == "Running" || 
                type == "Cycling" || type == "Swimming") {
                int dist;
                ss >> dist;
                
                if (type == "Walking") e = new Cardio("Walking", dist, 5);
                else if (type == "Running") e = new Cardio("Running", dist, 15);
                else if (type == "Cycling") e = new Cardio("Cycling", dist, 10);
                else if (type == "Swimming") e = new Cardio("Swimming", dist, 20);
                
            } else if (type == "Calisthenics" || type == "Weightlifting") {
                int tTime, rTime;
                ss >> tTime >> rTime;
                
                if (type == "Calisthenics") 
                    e = new StrengthTraining("Calisthenics", tTime, rTime, 10);
                else if (type == "Weightlifting") 
                    e = new StrengthTraining("Weightlifting", tTime, rTime, 12);
            }
            
            if (e != nullptr) {
                log_.push_back(e);
            }
        }
    }
    
    ifile.close();
    cout << "Loaded " << log_.size() << " exercises from save file." << endl;
    return true;
}

void User::saveFile(const string& filename) const {
    ofstream ofile(filename);
    if (!ofile.is_open()) {
        cout << "Failed to create save file!" << endl;
        return;
    }

    ofile << username_ << endl;
    ofile << lvl_ << endl;
    ofile << totPoints_ << endl;
    ofile << totDistance_ << endl;
    ofile << numSessions_ << endl;
    ofile << streak_ << endl;
    ofile << log_.size() << endl;
    
    for (size_t i = 0; i < log_.size(); i++) {
        ofile << "EXERCISE " << log_[i]->getType() << " " 
              << log_[i]->getData() << endl;
    }
    
    ofile.close();
}
