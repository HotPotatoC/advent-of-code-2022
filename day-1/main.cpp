#include <bits/stdc++.h>

auto part_one() {
  std::ifstream input;

  input.open("input.in");

  std::vector<int> total_calories;

  int current = 0;
  std::string line;
  while (std::getline(input, line)) {
    if (line == "") {
      total_calories.push_back(current);
      current = 0;
    } else {
      current += std::stoi(line);
    }
  }

  auto highest_calorie =
      *std::max_element(total_calories.begin(), total_calories.end());

  return highest_calorie;
}

auto part_two() {
  std::ifstream input;

  input.open("input.in");

  std::vector<int> total_calories;

  int current = 0;
  std::string line;
  while (std::getline(input, line)) {
    if (line == "") {
      total_calories.push_back(current);
      current = 0;
    } else {
      current += std::stoi(line);
    }
  }

  std::partial_sort(total_calories.begin(), total_calories.begin() + 3,
                    total_calories.end(), std::greater<int>());

  return std::accumulate(total_calories.begin(), total_calories.begin() + 3, 0);
}

auto main() -> int {
  std::cout << "Part one: " << part_one() << std::endl;
  std::cout << "Part two: " << part_two() << std::endl;

  return 0;
}