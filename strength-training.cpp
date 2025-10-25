#include <iostream>
#include "strength-training.h"

using namespace std;

StrengthTraining::StrengthTraining(const string& type, int totalTime, int restTime, int pointsPerMinute) 
    : totalTime_(totalTime), restTime_(restTime), strengthType_(type) {
    points_ = pointsPerMinute;
}

string StrengthTraining::getType() const { 
    return strengthType_; 
}

string StrengthTraining::getData() const { 
    return to_string(totalTime_) + " " + to_string(restTime_); 
}

int StrengthTraining::calcPoints() const { 
    return (totalTime_ - restTime_) * points_; 
}

StrengthTraining* createStrength(int strengthType, int totalTime, int restTime) {
    if (strengthType == 1) {
        return new StrengthTraining("Calisthenics", totalTime, restTime, 10);
    }
    else if (strengthType == 2) {
        return new StrengthTraining("Weightlifting", totalTime, restTime, 12);
    }
    else {
        return nullptr;
    }
}
