#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <string>

int main() {
  HashTable ht;
  std::ifstream file("unique_words.csv");

  if (!file.is_open()) {
    std::cerr << "Failed to open unique_words.csv\n";
    return 1;
  }

  std::string word;
  int count = 0;

  while (std::getline(file, word)) {
    if (!word.empty()) {
      ht.insert(word, count);
      count++;
    }
  }

  file.close();

  std::cout << "Inserted " << count << " unique words.\n";

  if (auto first = ht.get_first()) {
    std::cout << "First inserted/updated: " << first->first << " = "
              << first->second << "\n";
  }

  if (auto last = ht.get_last()) {
    std::cout << "Last inserted/updated: " << last->first << " = "
              << last->second << "\n";
  }

  // Lookup test
  for (const std::string &test_word :
       {"edition", "swamp", "library", "nonexistent"}) {
    auto result = ht.get(test_word);
    if (result) {
      std::cout << "Found '" << test_word << "' with value: " << *result
                << "\n";
    } else {
      std::cout << "Did not find '" << test_word << "'\n";
    }
  }

  std::cout << "Maximum probe count during insertion: " << ht.get_max_probe()
            << "\n";

  return 0;
}
