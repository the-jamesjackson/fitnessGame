#include <iostream>
#include "cardio.h"

using namespace std;

Cardio::Cardio(const string& type, int distance, int pointsPerMile) 
    : distance_(distance), cardioType_(type) {
    points_ = pointsPerMile;
}

string Cardio::getType() const { 
    return cardioType_; 
}

string Cardio::getData() const { 
    return to_string(distance_); 
}

int Cardio::calcPoints() const { 
    return distance_ * points_; 
}

Cardio* createCardio(int cardioType, int distance) {
    if (cardioType == 1) {
        return new Cardio("Walking", distance, 5);
    }
    else if (cardioType == 2) {
        return new Cardio("Running", distance, 10);
    }
    else if (cardioType == 3) {
        return new Cardio("Cycling", distance, 15);
    }
    else if (cardioType == 4) {
        return new Cardio("Swimming", distance, 20);
    }
    else {
        return nullptr;
    }
}