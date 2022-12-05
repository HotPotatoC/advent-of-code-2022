#include <bits/stdc++.h>

int main() {
  std::ifstream input;
  input.open("input.in");
  //   input.open("input.sample.in");

  std::string line;

  std::vector<std::vector<char>> crates(9);

  while (std::getline(input, line) && line[1] != '1') {
    for (int i = 0; i < crates.size(); i++) {
      int char_idx = i * 4 + 1;
      if (std::isalpha(line[char_idx])) {
        crates[i].push_back(line[char_idx]);
      }
    }
  }

  // skip 1 line
  std::getline(input, line);
  while (std::getline(input, line)) {
    std::istringstream iss(line);
    std::vector<std::string> ops;

    std::string word;
    while (std::getline(iss, word, ' ')) {
      ops.push_back(word);
    }

    int amount = std::stoi(ops[1]);
    int from = std::stoi(ops[3]);
    int to = std::stoi(ops[5]);

    crates[to - 1].insert(crates[to - 1].begin(), crates[from - 1].begin(),
                          crates[from - 1].begin() + amount);

    crates[from - 1].erase(crates[from - 1].begin(),
                           crates[from - 1].begin() + amount);
  }

  for (int i = 0; i < crates.size(); i++) {
    std::cout << crates[i][0];
  }
  std::cout << std::endl;

  return 0;
}