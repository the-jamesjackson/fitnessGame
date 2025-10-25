#ifndef STRENGTH
#define STRENGTH

#include "exercise.h"

class StrengthTraining : public Exercise {
protected:
    int totalTime_;
    int restTime_;
    std::string strengthType_;
    
public:
    StrengthTraining(const std::string& type, int totalTime, int restTime, int pointsPerMinute);
    
    int calcPoints() const;
    std::string getType() const;
    std::string getData() const;
    int getActiveTime() const { return totalTime_ - restTime_; }
};

StrengthTraining* createStrength(int strengthType, int totalTime, int restTime);

#endif
