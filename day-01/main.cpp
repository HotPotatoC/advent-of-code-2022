#include <bits/stdc++.h>

auto parse_input() {
  std::ifstream input;
  std::priority_queue<int> parts;

  input.open("input.in");

  std::string line;
  auto current = 0;
  while (std::getline(input, line)) {
    if (line.empty()) {
      parts.push(current);
      current = 0;
    } else {
      current += std::stoi(line);
    }
  }

  return parts;
}

auto part_one() { return parse_input().top(); }

auto part_two() {
  auto parts = parse_input();

  auto ans = 0;
  auto i = 0;
  while (!parts.empty() && i < 3) {
    ans += parts.top();
    parts.pop();
    i++;
  }

  return ans;
}

int main() {
  std::cout << "Part one: " << part_one() << std::endl;
  std::cout << "Part two: " << part_two() << std::endl;

  return 0;
}