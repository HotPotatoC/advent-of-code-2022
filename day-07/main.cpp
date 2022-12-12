#include <bits/stdc++.h>

std::vector<std::string> split_by_space(std::string s) {
  std::istringstream iss(s);

  std::vector<std::string> words;
  std::string word;
  while (std::getline(iss, word, ' ')) {
    words.push_back(word);
  }

  return words;
}

struct File {
  std::string name;
  long long size;
};

struct Directory {
  Directory *parent;
  std::string name;
  std::vector<std::unique_ptr<Directory>> children;
  std::vector<std::unique_ptr<File>> files;
  long long size;
};

long long update_sizes(Directory *root) {
  for (const auto &dir : root->children) {
    root->size += update_sizes(dir.get());
  }

  for (const auto &file : root->files) {
    root->size += file->size;
  }

  return root->size;
}

auto parse_input() {
  std::ifstream input;

  input.open("input.in");
  //   input.open("input.sample.in");

  std::string line;

  auto fs = std::make_unique<Directory>();
  fs->name = "/";
  fs->size = 0;

  auto cwd = fs.get();
  bool stop_ls = false;
  while (stop_ls || std::getline(input, line)) {
    stop_ls = false;
    if (line[0] != '$') continue;
    auto cmd_and_arg = split_by_space(line);

    std::string cmd = cmd_and_arg[1];

    if (cmd == "cd") {
      std::string arg = cmd_and_arg[2];
      if (arg == "..") {
        cwd = cwd->parent;
        continue;
      }

      if (arg == "/") {
        cwd = fs.get();
        continue;
      }

      bool exists = false;
      for (const auto &dir : cwd->children) {
        if (dir->name == arg) {
          cwd = dir.get();
          exists = true;
          break;
        }
      }

      if (exists) continue;

      cwd->children.push_back(std::make_unique<Directory>());
      cwd->children.back()->name = arg;
      cwd->children.back()->parent = cwd;
      cwd = cwd->children.back().get();
    } else if (cmd == "ls") {
      while (std::getline(input, line)) {
        auto content = split_by_space(line);
        if (content[0] == "$") {
          stop_ls = true;
          break;
        };

        bool exists = false;
        if (content[0] == "dir") {
          for (const auto &dir : cwd->children) {
            if (dir->name == content[0]) {
              exists = true;
            }
          }

          if (exists) continue;

          cwd->children.push_back(std::make_unique<Directory>());
          cwd->children.back()->name = content[1];
          cwd->children.back()->parent = cwd;
        } else {
          cwd->files.push_back(std::make_unique<File>());
          cwd->files.back()->name = content[1];
          cwd->files.back()->size = std::stoll(content[0]);
        }
      }
    }

    if (stop_ls) continue;
  }

  update_sizes(fs.get());

  return fs;
}

void fs_tree_display(Directory *root, int level, bool dir_only) {
  if (level == 1) {
    std::cout << "- " << root->name << " (dir, size=" << root->size << ")"
              << std::endl;
  }

  for (const auto &dir : root->children) {
    for (int space = 0; space < level * 2; space++) {
      std::cout << " ";
    }

    std::cout << "- " << dir->name << " (dir, size=" << dir->size << ")"
              << std::endl;

    fs_tree_display(dir.get(), level + 1, dir_only);
  }

  if (!dir_only) {
    for (const auto &file : root->files) {
      for (int space = 0; space < level * 2; space++) {
        std::cout << " ";
      }

      std::cout << "- " << file->name << " (file, size=" << file->size << ")"
                << std::endl;
    }
  }
}

long long fs_total_size(Directory *root, int level) {
  long long total = 0;

  for (const auto &dir : root->children) {
    total += fs_total_size(dir.get(), level + 1);
  }

  return total + root->size;
}

auto part_one() {
  auto fs = parse_input();

  constexpr long long dir_size_threshold = 100000;

  std::function<long long(Directory *, long long)> total_under_threshold;

  total_under_threshold = [&fs, &total_under_threshold](
                              Directory *root,
                              long long threshold) -> long long {
    int total = 0;

    for (const auto &dir : root->children) {
      if (dir->size <= threshold) {
        total += dir->size;
      }

      total += total_under_threshold(dir.get(), threshold);
    }

    return total;
  };

  return total_under_threshold(fs.get(), dir_size_threshold);
}

auto part_two() {
  auto fs = parse_input();

  constexpr long long available_space = 70000000;
  constexpr long long min_unused_space = 30000000;

  std::pair<long long, long long> ans = std::make_pair(0, INT_MAX);

  std::function<long long(Directory *, long long, long long, long long)>
      exclude_dir;

  exclude_dir = [&fs, &ans, &exclude_dir](
                    Directory *root, long long total_size,
                    long long min_unused_space,
                    long long available_space) -> long long {
    long long current_unused_space = available_space - total_size;
    for (const auto &dir : root->children) {
      long long diff = total_size - dir->size;
      long long unused = available_space - diff;
      if (unused >= min_unused_space && unused < ans.second) {
        ans = std::make_pair(dir->size, unused);
      }
      exclude_dir(dir.get(), total_size, min_unused_space, available_space);
    }

    return ans.first;
  };

  return exclude_dir(fs.get(), fs.get()->size, min_unused_space,
                     available_space);
}

int main() {
  std::cout << "Part one: " << part_one() << std::endl;
  std::cout << "Part two: " << part_two() << std::endl;

  return 0;
}