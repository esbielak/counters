export module FibonacciCounter;

import GenericCounter;
import Event;
import <queue>;
import <limits>;
import <cstdint>;
import <vector>;
import <functional>;

export class FibonacciCounter : public GenericCounter {

using eventQueue_t = std::priority_queue<Event, std::vector<Event>, 
        std::greater<Event>>;
private:
    uint64_t fibSmall, fibBig;
    bool stopped;
    // counter, baseDivisor, baseCounter, id
public:
    FibonacciCounter(uint64_t id, uint64_t base);
    void signal(uint64_t signals, eventQueue_t&) override;

};

FibonacciCounter::FibonacciCounter(uint64_t id, uint64_t base) : 
    GenericCounter(id, base), fibSmall(0), fibBig(1), stopped(false)  { }

void FibonacciCounter::signal(uint64_t signals, eventQueue_t& prioQueue) {
    if (!stopped) {
        uint64_t actualSignals;
        uint64_t baseDelta;
        uint64_t INTMAX = std::numeric_limits<uint64_t>::max();
        signalConversion(signals, actualSignals, baseCounter, baseDelta);
    
        if (fibSmall > INTMAX - fibBig) {
            if (counter > INTMAX - actualSignals) {
                counter = INTMAX;
                stopped = true;
            } else {
                counter += actualSignals;
            }
            return;
        }

        uint64_t delta = fibSmall + fibBig - counter; // time of first event
        if (delta > actualSignals) {
            counter += actualSignals;
            return;
        }
        prioQueue.push(Event(delta * (baseDivisor + 1) + baseDelta, id));
        uint64_t signalsLeft = actualSignals - delta;
        for (; fibSmall <= INTMAX - fibBig && signalsLeft >= fibSmall + fibBig + 1; signalsLeft -= (fibSmall + fibBig + 1)) {
            prioQueue.push(Event((fibSmall + fibBig + 1 + delta) * (baseDivisor + 1) + baseDelta, id));
            delta += fibSmall + fibBig + 1;
            uint64_t help = fibBig;
            fibBig += fibSmall;
            fibSmall = help;
        }
        
        if (fibSmall > INTMAX - fibBig && counter > INTMAX - signalsLeft) {
            counter = INTMAX;
            stopped = true;
        } else {
            counter = signalsLeft;
        }
        
    }
}
