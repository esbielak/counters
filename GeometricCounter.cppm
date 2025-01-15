export module GeometricCounter;

import GenericCounter;
import Event;
import <queue>;
import <limits>;
import <cstdint>;

// cmath
export class GeometricCounter : GenericCounter {

using eventQueue_t = std::priority_queue<Event>;

private:
    uint64_t power = 0; // max = 13
    // counter, baseDivisor, baseCounter, id
    uint64_t pow(uint64_t base, uint64_t exp) {
        uint64_t result = 1;
        for (uint64_t i = 0; i < exp; i++)
            result *= base;
        return result;
    }
public:
    GeometricCounter(uint64_t id, uint64_t base);
    void signal(uint64_t signals, eventQueue_t&) override;

};

GeometricCounter::GeometricCounter(uint64_t id, uint64_t base) : 
    GenericCounter(id, base) { }

void GeometricCounter::signal(uint64_t signals, eventQueue_t& prioQueue) {
    uint64_t actualSignals;
    uint64_t baseDelta;
    signalConversion(signals, actualSignals, baseCounter, baseDelta);
    
    if (actualSignals < (uint64_t)pow(10, power) - counter) {
        counter += actualSignals;
        return;
    }
    uint64_t delta = (uint64_t)pow(10, power) - counter - 1; // time of first ev
    prioQueue.push(Event(delta * (baseDivisor + 1 ) + baseDelta, id));
    uint64_t signalsLeft = actualSignals - delta;
    for (; signalsLeft > (uint64_t)pow(10, power); power = (power + 1) % 14) {
        signalsLeft -= (uint64_t)pow(10, power);
        delta += (uint64_t)pow(10, power);
        prioQueue.push(Event(delta * (baseDivisor + 1) + baseDelta, id));
        
    }
    counter = signalsLeft;
     
}
