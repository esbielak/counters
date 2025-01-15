export module ModuloCounter;

import GenericCounter;
import <iostream>;
import <queue>;
import <limits>;
import <cstdint>;
import Event;
export class ModuloCounter : public GenericCounter {

using eventQueue_t = std::priority_queue<Event, std::vector<Event>, 
        std::greater<Event>>;
private:
    uint64_t modulo;
    // counter, baseDivisor, baseCounter, id
public:
    ModuloCounter(uint64_t id, uint64_t base, uint64_t mod);
    void signal(uint64_t signals, eventQueue_t& prioQueue) override;

};

ModuloCounter::ModuloCounter(uint64_t id, uint64_t base, uint64_t mod) : 
    GenericCounter(id, base), modulo(mod) { }

void ModuloCounter::signal(uint64_t signals, eventQueue_t& prioQueue)  {
    uint64_t actualSignals;
    uint64_t baseDelta;
    uint64_t INTMAX = std::numeric_limits<uint64_t>::max();
    signalConversion(signals, actualSignals, baseCounter, baseDelta);
    if (actualSignals <= modulo - counter) {
        counter += actualSignals;
    } else {
        // time of the first event - doesn't count ignored impulses
        if (modulo == INTMAX) {
            if (counter > INTMAX - actualSignals) {
                prioQueue.push(Event((INTMAX - counter) * (baseDivisor + 1) + baseDelta, id));
            }
            counter += actualSignals; // overflow acts as expected
            return;
        }

        uint64_t time = modulo - counter;
        prioQueue.push(Event(time * (baseDivisor + 1) + baseDelta, id));
        for (; time <= actualSignals - modulo - 1; time += (modulo+1))
            prioQueue.push(Event(time * (baseDivisor + 1) + baseDelta, id));
        counter = actualSignals - time;
        
    }
}
