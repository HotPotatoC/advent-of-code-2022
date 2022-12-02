#include <bits/stdc++.h>

struct match {
  char first_col;
  char second_col;

  match(char opp, char p) : first_col(opp), second_col(p) {}
};

auto parse_input() {
  // pipe input file to executable
  // make main && ./main < input.in
  std::vector<match> matches;

  char first_col, second_col;
  while (std::cin >> first_col >> second_col) {
    matches.push_back(match(first_col, second_col));
  }

  return matches;
}

auto part_one(auto matches) {
  const std::array<std::array<int, 3>, 3> rps_chart = {{
      // rock - paper - scissor
      {4, 8, 3},  // rock
      {1, 5, 9},  // paper
      {7, 2, 6},  // scissor
  }};

  int outcome = 0;

  for (auto match : matches) {
    outcome += rps_chart[match.first_col - 'A'][match.second_col - 'X'];
  }

  return outcome;
}

auto part_two(auto matches) {
  const std::array<std::array<int, 3>, 3> rps_chart = {{
      // rock - paper - scissor
      {3, 4, 8},  // rock
      {1, 5, 9},  // paper
      {2, 6, 7},  // scissor
  }};

  int outcome = 0;

  for (auto match : matches) {
    outcome += rps_chart[match.first_col - 'A'][match.second_col - 'X'];
  }

  return outcome;
}

int main() {
  auto matches = parse_input();

  std::cout << "Part one: " << part_one(matches) << std::endl;
  std::cout << "Part two: " << part_two(matches) << std::endl;

  return 0;
}