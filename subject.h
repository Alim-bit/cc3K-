#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include <memory>
#include "observer.h"
using namespace std;

class Observer;

class Subject {
    vector<shared_ptr<Observer>> observers;

public:
    void attach(shared_ptr<Observer> o);
    void detach(shared_ptr<Observer> o);
    void notifyObservers();
    virtual ~Subject() = default;
};

#endif
