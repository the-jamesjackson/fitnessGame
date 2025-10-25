#ifndef CARDIO 
#define CARDIO

#include "exercise.h"

class Cardio : public Exercise {
protected:
    int distance_;
    std::string cardioType_;
    
public:
    Cardio(const std::string& type, int distance, int pointsPerMile);
    
    int calcPoints() const;
    std::string getType() const;
    std::string getData() const;
    int getDistance() const { return distance_; }
};

Cardio* createCardio(int cardioType, int distance);

#endif
