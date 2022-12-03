#include <bits/stdc++.h>

auto parse_input() {
  std::ifstream input;

  input.open("input.in");
  // input.open("input.sample.in");

  std::vector<std::string> rucksack;

  std::string item;
  while (std::getline(input, item)) {
    rucksack.push_back(item);
  }

  return rucksack;
}

auto part_one() {
  auto rucksack = parse_input();

  int ans = 0;
  for (auto item : rucksack) {
    std::string first_compartment = item.substr(0, item.size() / 2);
    std::string second_compartment =
        item.substr(item.size() / 2, item.size() / 2);

    std::sort(first_compartment.begin(), first_compartment.end());
    std::sort(second_compartment.begin(), second_compartment.end());

    std::string intersect;
    std::set_intersection(first_compartment.begin(), first_compartment.end(),
                          second_compartment.begin(), second_compartment.end(),
                          std::back_inserter(intersect));

    const char intersect_char = intersect[0];
    if (intersect_char && std::islower(intersect_char)) {
      ans += intersect_char - 'a' + 1;
    } else if (intersect_char && std::isupper(intersect_char)) {
      ans += intersect_char - 'A' + 27;
    }
  }

  return ans;
}

auto part_two() {
  auto rucksack = parse_input();

  int ans = 0;
  int curr = 1;
  for (auto item : rucksack) {
    if (curr % 3 == 0) {
      std::string s1 = rucksack[curr - 1];
      std::string s2 = rucksack[curr - 2];
      std::string s3 = rucksack[curr - 3];

      std::sort(s1.begin(), s1.end());
      std::sort(s2.begin(), s2.end());
      std::sort(s3.begin(), s3.end());

      std::string intersect1;
      std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
                            std::back_inserter(intersect1));

      std::string intersect2;
      std::set_intersection(intersect1.begin(), intersect1.end(), s3.begin(),
                            s3.end(), std::back_inserter(intersect2));

      const char intersect_char = intersect2[0];
      if (intersect_char && std::islower(intersect_char)) {
        ans += intersect_char - 'a' + 1;
      } else if (intersect_char && std::isupper(intersect_char)) {
        ans += intersect_char - 'A' + 27;
      }
    }
    curr++;
  }

  return ans;
}

int main() {
  std::cout << "Part one: " << part_one() << std::endl;
  std::cout << "Part two: " << part_two() << std::endl;

  return 0;
}