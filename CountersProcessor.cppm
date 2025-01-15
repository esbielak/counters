export module CountersProcessor;

import <unordered_map>;
import <memory>;
import <cstdint>;
import <string>;
import <regex>;
import <iostream>;

export class CountersProcessor final {
public:
  void process_input(std::string line, uint_64_t line_number) {
    static std::regex create_mod_regex = create_line_regex("M", 3);
    static std::regex create_fib_regex = create_line_regex("F", 2);
    static std::regex create_geo_regex = create_line_regex("G", 2);
    static std::regex delete_regex = create_line_regex("D", 1);
    static std::regex counter_info_regex = create_line_regex("P", 1);
    static std::regex send_signals_regex = create_line_regex("A", 1);

    // match against some regexes
    // print error if input is invalid
  }

private:
  using counter_map_t =
      std::unordered_map<int, std::unique_ptr<GenericCounter>>;

  counter_map_t counters;

  // create a regex to match commands of the format specified in the assignment:
  // a match is a line starting with command_id followed by cnt numbers
  // note: it does not check if the numbers can fit in a uint_64_t
  static std::regex create_line_regex(std::string command_id, int cnt) {
    std::string pattern = "^(" + command_id + ")";

    for (int i = 0; i < cnt; ++i) {
      pattern += " (\\d+)";
    }

    pattern += "$";

    return std::regex(pattern);
  }
}