import GenericCounter;

export module ModuloCounter;

export class ModuloCounter : GenericCounter {
private:
    uint64_t modulo;

public:
    ModuloCounter(uint64_t id, uint64_t mod);
    void signal(uint64_t signals, void* prioQueue) override;

};

ModuloCounter::ModuloCounter(uint64_t id, uint64_t mod) : GenericCounter(id), modulo(mod) { }

void ModuloCounter::signal(uint64_t signals, void* prioQueue) override {

}
