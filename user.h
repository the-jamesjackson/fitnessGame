#ifndef USER  
#define USER

#include <string>
#include <vector>
#include <fstream>
#include "cardio.h"
#include "strength-training.h"

class User{
private:
    std::string username_;
    int lvl_;
    int totPoints_;
    int totDistance_;
    int numSessions_; 
    int streak_; 
    int basePoints_; 
    std::vector<Exercise*> log_;

    bool hasLvlUp();

public:
    User();
    ~User();
    
    void setUsername(const std::string& name);
    void logEx(Exercise* e);
    void display() const;
    void printLog() const;
    void displayDetailedStats() const;

    int pointsRequired() const;
    void lvlUp();

    void incrementStreak() { streak_++; }
    void resetStreak() { streak_ = 1; }
    int getStreak() const { return streak_; }
    
    bool loadFile(const std::string& filename);
    void saveFile(const std::string& filename) const;

    int getLevel() const { return lvl_; }
    int getTotalPoints() const { return totPoints_; }
};

#endif
