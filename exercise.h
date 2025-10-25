#ifndef EXERCISE 
#define EXERCISE

#include <iostream>
#include <string>

class Exercise{
protected:
    int points_;
public:
    Exercise() : points_(0){}
    virtual ~Exercise(){}

    virtual int calcPoints() const = 0;
    virtual std::string getType() const = 0;
    virtual std::string getData() const = 0;
};

int getValidInt(const std::string& prompt, int min, int max);

Exercise* createExercise();

#endif
