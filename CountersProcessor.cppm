export module CountersProcessor;

import <unordered_map>;
import <memory>;
import <cstdint>;
import <string>;
import <regex>;
import <iostream>;
import <stdexcept>;
import <functional>;
import <queue>;

import CounterModules;

// TODO: we need a cleaner way, we shouldn't redefine it in every file
using eventQueue_t = std::priority_queue<Event, std::vector<Event>, 
        std::greater<Event>>;

export class CountersProcessor final {
public:
  void process_input(std::string& line, uint_64_t line_number) {
    static std::regex create_mod_regex = create_line_regex("M", 3);
    static std::regex create_fib_regex = create_line_regex("F", 2);
    static std::regex create_geo_regex = create_line_regex("G", 2);
    static std::regex delete_regex = create_line_regex("D", 1);
    static std::regex counter_info_regex = create_line_regex("P", 1);
    static std::regex send_signals_regex = create_line_regex("A", 1);

    // TODO: maybe there is cleaner way
    std::smatch match;
    try {
      if (std::regex_match(line, match, create_mod_regex)) {
        uint_64_t c = std::stoull(match[2]);
        if (counters.contains(c)) {
          print_error(line_number);
          return;
        }
        uint_64_t p = std::stoull(match[3]);
        uint_64_t m = std::stoull(match[4]);

        counters[c] = std::make_unique<ModuloCounter>(c, p, m);
      } else if (std::regex_match(line, match, create_fib_regex)) {
        uint_64_t c = std::stoull(match[2]);
        if (counters.contains(c)) {
          print_error(line_number);
          return;
        }
        uint_64_t p = std::stoull(match[3]);

        counters[c] = std::make_unique<FibonacciCounter>(c, p);
      } else if (std::regex_match(line, match, create_geo_regex)) {
        uint_64_t c = std::stoull(match[2]);
        if (counters.contains(c)) {
          print_error(line_number);
          return;
        }
        uint_64_t p = std::stoull(match[3]);

        counters[c] = std::make_unique<GeodecimalCounter>(c, p);
      } else if (std::regex_match(line, match, delete_regex)) {
        uint_64_t c = std::stoull(match[2]);
        if (counters.clear(c) == 0) {
          print_error(line_number);
          return;
        }
      } else if (std::regex_match(line, match, counter_info_regex)) {
        uint_64_t c = std::stoull(match[2]);
        if (!counters.contains(c)) {
          print_error(line_number);
          return;
        }

        counters[c]->print();
      } else if (std::regex_match(line, match, send_signals_regex)) {
        uint_64_t c = std::stoull(match[2]);

        send_impulses(c);
      } else {
        print_error(line_number);
      }
    } catch (std::out_of_range a) {
      print_error(line_number);
    }
  }

private:
  using counter_map_t =
      std::unordered_map<unint_64_t, std::unique_ptr<GenericCounter>>;

  counter_map_t counters;

  void print_error(uint_64_t line_number) {
    std::cerr << "ERROR " << line_number << "\n";
  }

  void send_impulses(uint_64_t impulses) {
    eventQueue_t queue;

    for (auto& counter : counters) {
      counter.second.signal(impulses, queue);
    }

    while (!queue.empty()) {
      queue.top().print();
      queue.pop();
    }
  }

  // create a regex to match commands of the format specified in the assignment:
  // a match is a line starting with command_id followed by cnt numbers
  // note: it does not check if the numbers can fit in a uint_64_t
  static std::regex create_line_regex(std::string command_id, int cnt) {
    std::string pattern = "^(" + command_id + ")";

    // TODO: do we accept leading zeros?
    for (int i = 0; i < cnt; ++i) {
      pattern += " ((0|[1-9]\\d*))";
    }

    pattern += "$";

    return std::regex(pattern);
  }
}