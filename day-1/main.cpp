#include <bits/stdc++.h>

auto parse_input() {
  std::ifstream input;
  std::priority_queue<int> pq_calories;

  input.open("input.in");

  auto current = static_cast<int>(0);

  std::string line;
  while (std::getline(input, line)) {
    if (line.empty()) {
      pq_calories.push(current);
      current = 0;
    } else {
      current += std::stoi(line);
    }
  }

  return pq_calories;
}

auto part_one() {
  std::priority_queue<int> pq_calories = parse_input();

  return pq_calories.top();
}

auto part_two() {
  std::priority_queue<int> pq_calories = parse_input();

  auto ans = static_cast<int>(0);
  auto i = static_cast<int>(0);
  while (!pq_calories.empty() && i < 3) {
    ans += pq_calories.top();
    pq_calories.pop();
    i++;
  }

  return ans;
}

int main() {
  std::cout << "Part one: " << part_one() << std::endl;
  std::cout << "Part two: " << part_two() << std::endl;

  return 0;
}