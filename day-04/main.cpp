#include <bits/stdc++.h>

auto parse_input() {
  std::vector<std::tuple<int, int, int, int>> pairs;

  int a, b, c, d;
  char _1, _2, _3;  // skip symbols
  while (std::cin >> a >> _1 >> b >> _2 >> c >> _3 >> d) {
    pairs.push_back(std::make_tuple(a, b, c, d));
  }

  return pairs;
}

auto part_one(std::vector<std::tuple<int, int, int, int>> pairs) {
  int ans = 0;

  for (auto pair : pairs) {
    int first_start, first_end;
    int second_start, second_end;

    std::tie(first_start, first_end, second_start, second_end) = pair;

    if ((first_start <= second_start && first_end >= second_end) ||
        (first_start >= second_start && first_end <= second_end)) {
      ans++;
    }
  }

  return ans;
}

auto part_two(std::vector<std::tuple<int, int, int, int>> pairs) {
  int ans = 0;

  for (auto pair : pairs) {
    int first_start, first_end;
    int second_start, second_end;

    std::tie(first_start, first_end, second_start, second_end) = pair;

    int combined_start = std::max(first_start, second_start);
    int combined_end = std::min(first_end, second_end);

    if (combined_start <= combined_end) ans++;
  }

  return ans;
}

int main() {
  auto input = parse_input();

  std::cout << "Part one: " << part_one(input) << std::endl;
  std::cout << "Part two: " << part_two(input) << std::endl;

  return 0;
}