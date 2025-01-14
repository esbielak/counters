import iostream;

export module GenericCounter;

export class GenericCounter {
private:
    uint64_t count, id;


public:
    GenericCounter(uint64_t id);

    virtual void signal(uint64_t signals, void* prioQueue); // we put all events in the prioQueue passed as arg
    void print();


};

GenericCounter::GenericCounter(uint64_t id) : count(0), id(id) { }

void GenericCounter::print() {
	std::cout << "C " << this->id << " " << this->count << "\n";
}

