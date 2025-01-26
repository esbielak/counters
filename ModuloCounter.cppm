export module ModuloCounter;

import GenericCounter;
import <iostream>;
import <queue>;
import <limits>;
import <cstdint>;
import <vector>;
import <functional>;
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
    GenericCounter(id, base), modulo(mod) { std::cout << id << "," << base << "," << mod << std::endl;}

void ModuloCounter::signal(uint64_t signals, eventQueue_t& prioQueue)  {
    std::cout << "============ signal" << signals << std::endl;
    uint64_t actualSignals;
    uint64_t baseDelta;
    uint64_t INTMAX = std::numeric_limits<uint64_t>::max();
    signalConversion(signals, actualSignals, baseCounter, baseDelta);
    std::cout << "as" << actualSignals << "baseC" << baseCounter << "bD" << baseDelta << std::endl;
    if (actualSignals <= modulo - counter) {
        counter += actualSignals;
    } else {
        if (modulo == INTMAX) {
            if (counter > INTMAX - actualSignals) {
                prioQueue.push(Event((INTMAX - counter) * (baseDivisor + 1) + baseDelta, id));
            }
            counter += actualSignals;
            return;
        }

        uint64_t time = modulo - counter;
        //prioQueue.push(Event(time * (baseDivisor + 1) + baseDelta, id));
        std::cout << actualSignals << " time first value" << time << std::endl;
        for (; time <= actualSignals; time += (modulo+1)) {
            std::cout << "currtime: " << time <<std::endl;
            prioQueue.push(Event(time * (baseDivisor + 1) + baseDelta, id));
        }
        // only if the for loop body was executed at least once
        counter = actualSignals - (time - modulo - 1);
        
    }
}
