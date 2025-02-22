export module GenericCounter;

import <iostream>;
import <queue>;
import <limits>;
import <cstdint>;
import <vector>;
import <functional>;
import Event;

using eventQueue_t = std::priority_queue<Event, std::vector<Event>, 
        std::greater<Event>>;

export class GenericCounter {

protected:
    uint64_t counter, id, baseDivisor, baseCounter;
    
    void signalConversion(uint64_t signals, uint64_t& actualCount, uint64_t& newBaseCounter, uint64_t& baseDelta);

public:
    GenericCounter(uint64_t id, uint64_t base);
    GenericCounter() : counter(0), id(0), baseDivisor(0), baseCounter(0) {}
    virtual ~GenericCounter() {}
    virtual void signal(uint64_t signals, eventQueue_t& prioQueue) = 0;
    void print();


};

GenericCounter::GenericCounter(uint64_t id, uint64_t base) : counter(0), id(id), baseDivisor(base), baseCounter(0) { }

void GenericCounter::print() {
	std::cout << "C " << this->id << " " << this->counter << "\n";
}

// Calculates the amount of unignored signals and new currently-ignored-signals count.
void GenericCounter::signalConversion(uint64_t signals, uint64_t& actualSignals, uint64_t& newBaseCounter, uint64_t& baseDelta) {
    baseDelta = baseDivisor - baseCounter + 1;
    const uint64_t INTMAX = std::numeric_limits<uint64_t>::max();
    if (baseDivisor == INTMAX) {
        actualSignals = (baseCounter > INTMAX - signals ? 1 : 0);
        newBaseCounter += signals;
    } else {
        uint64_t baseOverflow = 0;
        if (signals % (baseDivisor + 1) > INTMAX - baseCounter) {
            baseOverflow = 1;
            newBaseCounter = signals % (baseDivisor + 1) - (INTMAX - baseCounter);
        } else {
            newBaseCounter = signals % (baseDivisor + 1) + baseCounter;
        }
        actualSignals = signals / (baseDivisor + 1) + baseCounter / (baseDivisor + 1)
                 + baseOverflow * INTMAX / (baseDivisor + 1);
        newBaseCounter %= (baseDivisor + 1);
    }
}
