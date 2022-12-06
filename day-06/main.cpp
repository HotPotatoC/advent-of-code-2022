#include <bits/stdc++.h>

auto parse_input() {
  std::string signal;
  std::cin >> signal;
  return signal;
}

auto part_one(std::string input) {
  for (int i = 0; i < input.size() - 4; i++) {
    std::set<char> stream;
    for (int ans = i; ans < i + 4; ans++) {
      stream.insert(input[ans]);

      if (stream.size() == 4) {
        return ans + 1;
      }
    }

    if (stream.size() == 4) {
      break;
    }
  }

  return -1;
}

auto part_two(std::string input) {
  for (int i = 0; i < input.size() - 14; i++) {
    std::set<char> stream;
    for (int ans = i; ans < i + 14; ans++) {
      stream.insert(input[ans]);

      if (stream.size() == 14) {
        return ans + 1;
      }
    }

    if (stream.size() == 14) {
      break;
    }
  }

  return -1;
}

int main() {
  auto input = parse_input();

  std::cout << "Part one: " << part_one(input) << std::endl;
  std::cout << "Part two: " << part_two(input) << std::endl;

  return 0;
}