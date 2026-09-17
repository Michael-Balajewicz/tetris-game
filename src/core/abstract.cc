export module Abstract;

import <vector>;
import <algorithm>;

// forward declarations inside same module
export class Subject;
export class Observer;

// observer interface
export class Observer {
public:
    virtual void update(Subject &whoNotified) = 0;
    virtual ~Observer() = default;
};

// subject base
export class Subject {
    std::vector<Observer*> observers; // does not own?
public:
    void attach(Observer *o);
    void detach(Observer *o);
    void notify();
    virtual ~Subject() = default;
};
