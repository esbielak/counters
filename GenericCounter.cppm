import <iostream>;
import <queue>;
import <vector>;
import <utility>;
import <functional>;
import <limits>;

// import export Event;

using eventQueue_t = std::priority_queue<Event>;

/*import iostream;

export module GenericCounter;
// functional, vector, queue - need to precompile
export*/ class GenericCounter {

private:
    uint64_t count, id, baseDivisor, baseCounter;
    
    void signalConversion(uint64_t signals, uint64_t& actualCount, uint64_t& newBaseCounter);

public:
    GenericCounter(uint64_t id, uint64_t base);

    virtual void signal(uint64_t signals, eventQueue_t& prioQueue); // we put all events in the prioQueue passed as arg
    void print();


};

GenericCounter::GenericCounter(uint64_t id, uint64_t base) : count(0), id(id), baseDivisor(base), baseCounter(0) { }

void GenericCounter::print() {
	std::cout << "C " << this->id << " " << this->count << "\n";
}

// calculates the amount of unignored signals and new currently-ignored-signals count
void GenericCounter::signalConversion(uint64_t signals, uint64_t& actualSignals, uint64_t& newBaseCounter) {
    const uint64_t INTMAX = std::numeric_limits<uint64_t>::max();
    if (baseDivisor == INTMAX) {
        actualSignals = (baseCounter > INTMAX - signals ? 1 : 0);
        newBaseCounter += signals; // here the overflow is fine
    } else {
        uint64_t baseOverflow = 0;
        uint64_t carry = 0;
        if (signals % (baseDivisor + 1) > INTMAX - baseCounter) {
            baseOverflow = 1; // temp int64_t overflow
            newBaseCounter = signals % (baseDivisor + 1) - (INTMAX - baseCounter);
        } else {
            newBaseCounter = signals % (baseDivisor + 1) + baseCounter;
        }
        actualSignals = signals / (baseDivisor + 1) + baseCounter / (baseDivisor + 1)
                 + baseOverflow * INTMAX / (baseDivisor + 1); // mby check after
        newBaseCounter %= (baseDivisor + 1);
    }
}
