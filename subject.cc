#include "subject.h"
#include <memory>
using namespace std;

void Subject::attach(shared_ptr<Observer> o) {
    observers.push_back(o);
}

void Subject::detach(shared_ptr<Observer> o){
    for (auto it = observers.begin(); it != observers.end(); ++it) {
        if (*it == o) {
            observers.erase(it);
            return;
        }
    }
}

void Subject::notifyObservers() {
  for (auto ob : observers) ob->notify();
}
