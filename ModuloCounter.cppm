import GenericCounter;

export module ModuloCounter;

export class ModuloCounter : GenericCounter {

using event_t = std::pair<uint64_t, uint64_t>;
using eventQueue_t = std::priority_queue<event_t, std::vector<event_t>, std::greater>;

private:
    uint64_t modulo;
    // counter, baseDivisor, baseCounter, id
public:
    ModuloCounter(uint64_t id, uint64_t base, uint64_t mod);
    void signal(uint64_t signals, std::priority_queue<>) override;

};

ModuloCounter::ModuloCounter(uint64_t id, uint64_t base, uint64_t mod) : 
    GenericCounter(id, base), modulo(mod) { }

void ModuloCounter::signal(uint64_t signals, eventQueue_t& prioQueue) override {
    int64_t actualSignals;
    int64_t INTMAX = std::numeric_limits<uint64_t>::max();
    signalConversion(signals, actualSignals, baseCounter);
    if (actualSignals <= modulo - counter) {
        counter += actualSignals;
    } else {
        // another edge-case
        if (modulo == INTMAX) {

            return;
        }
        // time of the first event - doesn't count ignored impulses
        uint64_t time = (modulo - counter + 1);
        event_t event(time * (baseDivisor + 1), id);
        prioQueue.push(event);
        for (; time < actualSignals; time += (modulo+1))
        
    }
}
