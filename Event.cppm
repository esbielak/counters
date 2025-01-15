export module Event;

import <compare>;
import <cstdint>;
import <iostream>;

export class Event {
public:
  Event() noexcept : val(0), counter_id(0) {}
  Event(uint64_t val, uint64_t counter_id) noexcept
      : val(val), counter_id(counter_id) {}

  auto operator<=>(const Event &other) const noexcept {
    auto cmp = val <=> other.val;
    if (cmp != 0) {
      return cmp;
    }
    return counter_id <=> other.counter_id;
  }

  void print() const { std::cout << "E " << counter_id << " " << val << "\n"; }

private:
  uint64_t val;
  uint64_t counter_id;
};