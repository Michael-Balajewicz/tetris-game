module Abstract;

void Subject::attach(Observer *o) {
    observers.push_back(o);
}
// OLD
// void Subject::detach(Observer *o) {
//     observers.erase(
//         std::remove(observers.begin(), observers.end(), o),
//         observers.end()
//     );
// }

// MIKE NEW
void Subject::detach(Observer* o) {
    for (auto it = observers.begin(); it != observers.end();) {
        if (*it == o) {
            it = observers.erase(it);  // returns the iterator to next in tthe vector
        } else {
            ++it;
        }
    }
}

void Subject::notify() {
    for (auto *o : observers) {
        if (o) o->update(*this);
    }
}
