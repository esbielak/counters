import <string>

int main() {

    std::string line;
    for (uint64_t i = 1; getline(std::cin, line), ++i) {
        // process line
    }
}