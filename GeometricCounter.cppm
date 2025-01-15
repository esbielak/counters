import GenericCounter;
import <cmath>;
import <vector>;
import <queue>;
import <limits>;


export module GeometricCouter;
// cmath
export class GeometricCouter : GenericCounter {

using eventQueue_t = std::priority_queue<Event, std::vector<Event>, std::greater<Event>>;

private:
    uint64_t power = 0; // max = 13
    // counter, baseDivisor, baseCounter, id
public:
    GeometricCouter(uint64_t id, uint64_t base);
    void signal(uint64_t signals, std::priority_queue<>) override;

};

GeometricCouter::GeometricCouter(uint64_t id, uint64_t base) : 
    GenericCounter(id, base) { }

void GeometricCouter::signal(uint64_t signals, eventQueue_t& prioQueue) override {
    int64_t actualSignals;
    int64_t INTMAX = std::numeric_limits<uint64_t>::max();
    signalConversion(signals, actualSignals, baseCounter);
    
    if (actualSignals < (uint64_t)pow(10, power) - counter) {
        counter += actualSignals;
        return;
    }
    uint64_t delta = (uint64_t)pow(10, power) - counter; // time of first ev
    prioQueue.push(Event(delta * (baseDivisor + 1 ), id));
    uint64_t signalsLeft = actualSignals - delta;
    for (; signalsLeft > (uint64_t)pow(10, power); power = (power + 1) % 14) {
        signalsLeft -= (uint64_t)pow(10, power);
        delta += (uint64_t)pow(10, power);
        prioQueue.push(Event(delta * (baseDivisor + 1), id));
        
    }
    counter = signalsLeft;
     
}
