import <string>;
import <iostream>;
import <unordered_map>;
import CountersProcessor;

int main() {
    CountersProcessor processor;

    std::string line;
    for (uint64_t i = 1; getline(std::cin, line); ++i) {
        processor.process_input(line, i);
    }
}
